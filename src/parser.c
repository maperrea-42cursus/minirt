/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 19:52:18 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/08 23:05:02 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_object(void *object,
		t_get_intersection *intersection, t_get_color *color)
{
	t_objects	*list;
	t_objects	*new;

	if (!(new = malloc(sizeof(t_objects))))
		return;
	new->object = object;
	new->get_intersection = intersection;
	new->get_color = color;
	new->next = NULL;
	if (!g_objects)
	{
		g_objects = new;
		return;
	}
	list = g_objects;
	while (list->next)
		list = list->next;
	list->next = new;
}

void	add_light(void *light, t_get_luminosity *luminosity, t_get_pos *pos)
{
	t_lights	*list;
	t_lights	*new;

	if (!(new = malloc(sizeof(t_lights))))
		return;
	new->light = light;
	new->get_luminosity = luminosity;
	new->get_pos = pos;
	new->next = NULL;
	if (!g_lights)
	{
		g_lights = new;
		return;
	}
	list = g_lights;
	while(list->next)
		list = list->next;
	list->next = new;
}

void	to_next_number(char **str)
{
	while (ft_isdigit(**str) || **str == '-')
		(*str)++;
	while (!ft_isdigit(**str) && **str != '-')
		(*str)++;
}

int		next_int(char **str)
{
	to_next_number(str);
	return (ft_atoi(*str));
}

double	next_float(char **str)
{
	double	int_part;
	double	frac_part;
	int		neg;
	int		i;

	i = 0;
	to_next_number(str);
	int_part = (double)ft_atoi(*str);
	neg = (int_part < 0.);
	while (ft_isdigit((*str)[i]) || (*str)[i] == '-')
		i++;
	if ((*str)[i] == '.')
	{
		to_next_number(str);
		frac_part = (double)ft_atoi(*str);
		i = 0;
		while (ft_isdigit((*str)[i]))
			i++;
		frac_part *= pow(10, -i);
		if (neg)
			frac_part = -frac_part;
	}
	else
		frac_part = 0.;
	return (int_part + frac_part);
}
//TODO verify that there is only a , between numbers in vectors
t_vec3	next_vec3(char **str)
{
	t_vec3 vec;

	vec.x = next_int(str);
	vec.y = next_int(str);
	vec.z = next_int(str);
	return (vec);
}

t_fvec3 next_fvec3(char **str)
{
	t_fvec3 vec;

	vec.x = next_float(str);
	vec.y = next_float(str);
	vec.z = next_float(str);
	return(vec);
}

int		next_color(char **str)
{
	int	color;

	color = next_int(str) << 16;
	color += next_int(str) << 8;
	color += next_int(str);
	return (color);
}

int		parse_r(char *line)
{
	static char done;

	if (done)
		return (0);									//TODO error message
	g_resolution.x = next_int(&line);
	g_resolution.y = next_int(&line);
	printf("\nresolution: %dx%d\n", g_resolution.x, g_resolution.y);
	done = 1;
	return (1);
}

int		parse_a(char *line)
{
	static char done;

	if (done)
		return (0);									//TODO error message
	g_ambient_light.pos = (t_fvec3){0.0,0.0,0.0};
	g_ambient_light.power = next_float(&line);
	g_ambient_light.color = next_color(&line);
	printf("\nambient light: %.2f, %#010x\n", g_ambient_light.power, g_ambient_light.color);
	done = 1;
	return (1);
}

int		parse_f(char *line)
{
	g_light_factor = next_float(&line);
	printf("\nlight factor:\t%.2f\n", g_light_factor);
	return (1);
}

int		parse_c(char *line)
{
	t_camera	*camera;
	t_cameras	*new;
	t_cameras	*cam_list;

	if (!(camera = malloc(sizeof(t_camera))))
		return (0);
	if (!(new = malloc(sizeof(t_cameras))))
		return (0);
	camera->pos = next_fvec3(&line);
	camera->orientation = fvec3_normalize(next_fvec3(&line));
	camera->fov = (next_float(&line) / 180.) * M_PI;
	new->camera = camera;
	new->next = NULL;
	cam_list = g_cameras;
	if (!cam_list)
		g_cameras = new;
	else
	{
		while (cam_list->next)
			cam_list = cam_list->next;
		cam_list->next = new;
	}
	printf("\ncamera:\t\tposition: %.2f %.2f %.2f\n\t\torientation: %.2f %.2f %.2f\n\t\tfov: %.2f\n", camera->pos.x, camera->pos.y, camera->pos.z, camera->orientation.x, camera->orientation.y, camera->orientation.z, camera->fov);
	return (1);
}

int		parse_l(char *line)
{
	t_spherical_light	*light;
	
	if (!(light = malloc(sizeof(t_spherical_light))))
		return (0);
	light->pos = next_fvec3(&line);
	light->power = next_float(&line);
	light->color = next_color(&line);
	add_light(light, &spherical_light_luminosity, &spherical_light_pos);
	printf("\nlight:\t\tposition: %.2f %.2f %.2f\n\t\tpower: %.2f\n\t\tcolor: %#010x\n", light->pos.x, light->pos.y, light->pos.z, light->power, light->color);
	return (1);
}

int		parse_sp(char *line)
{
	t_sphere	*sphere;

	if (!(sphere = malloc(sizeof(t_sphere))))
		return (0);
	sphere->pos = next_fvec3(&line);
	sphere->radius = next_float(&line) / 2.;
	sphere->color = next_color(&line);
	add_object(sphere, &sphere_intersection, &sphere_color);
	printf("\nsphere:\t\tposition: %.2f %.2f %.2f\n\t\tradius: %.2f\n\t\tcolor: %#010x\n", sphere->pos.x, sphere->pos.y, sphere->pos.z, sphere->radius, sphere->color);
	return (1);
}

int		parse_pl(char *line)
{
	t_plane		*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (0);
	plane->pos = next_fvec3(&line);
	plane->normal = next_fvec3(&line);
	plane->color = next_color(&line);
	add_object(plane, &plane_intersection, &plane_color);
	printf("\nplane:\t\tposition = %.2f %.2f %.2f\n\t\tnormal: %.2f %.2f %.2f\n\t\tcolor: %#010x\n", plane->pos.x, plane->pos.y, plane->pos.z, plane->normal.x, plane->normal.y, plane->normal.z, plane->color);
	return (1);
}

int		parse_sq(char *line)
{
	printf("%s\n", line);
	return (1);
}

int		parse_cy(char *line)
{
	t_cylinder		*cylinder;

	if (!(cylinder = malloc(sizeof(t_cylinder))))
		return (0);
	cylinder->pos = next_fvec3(&line);
	cylinder->axis = fvec3_normalize(next_fvec3(&line));
	cylinder->radius = next_float(&line) / 2.;
	cylinder->height = next_float(&line);
	cylinder->color = next_color(&line);
	add_object(cylinder, &cylinder_intersection, &cylinder_color);
	printf("\ncylinder:\tposition: %.2f %.2f %.2f\n\t\taxis: %.2f %.2f %.2f\n\t\tdiameter: %.2f\n\t\theight: %.2f\n\t\tcolor: %#010x\n", cylinder->pos.x, cylinder->pos.y, cylinder->pos.z, cylinder->axis.x, cylinder->axis.y, cylinder->axis.z, cylinder->radius, cylinder->height, cylinder->color);
	return (1);
}

int		parse_tr(char *line)
{
	printf("%s\n", line);
	return (1);
}

t_lookup_table	*get_lookup_table(void)
{
	static t_lookup_table table[] = {
		{"sp", &parse_sp},
		{"pl", &parse_pl},
		{"cy", &parse_cy},
		{"sq", &parse_sq},
		{"tr", &parse_tr},
		{"R", &parse_r},
		{"A", &parse_a},
		{"F", &parse_f},
		{"c", &parse_c},
		{"l", &parse_l},
		{NULL, NULL}
	};

	return (table);
}

int		parse_map(char *filename)
{
	char			*line;
	t_lookup_table	*lookup_table;
	int				fd;
	int				ret;

	fd = open(filename, O_RDONLY);
	ret = 1;
	g_light_factor = 1;
	while(ret == 1)
	{
		ret = get_next_line(fd, &line);
		lookup_table = get_lookup_table();
		while(ft_isspace(*line))
			line++;
		if (!*line)
			continue;
		while (lookup_table->key &&
				ft_strncmp(line, lookup_table->key, ft_strlen(lookup_table->key)))
			lookup_table++;
		if (!lookup_table->key)
			write(1, "Error\n", 6);
		else
			(*(lookup_table->value))(line); //TODO error management
	}
	return (1);
}
