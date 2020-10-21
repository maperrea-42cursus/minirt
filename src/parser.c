/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 19:52:18 by maperrea          #+#    #+#             */
/*   Updated: 2020/10/21 19:39:15 by maperrea         ###   ########.fr       */
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
	double int_part;
	double frac_part;
	int		i;

	i = 0;
	to_next_number(str);
	int_part = (double)ft_atoi(*str);
	while (ft_isdigit((*str)[i]))
		i++;
	if ((*str)[i] == '.')
	{
		to_next_number(str);
		frac_part = (double)ft_atoi(*str);
		i = 0;
		while (ft_isdigit((*str)[i]))
			i++;
		frac_part *= pow(10, -i);
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
	printf("resolution: %dx%d\n", g_resolution.x, g_resolution.y);
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
	printf("ambient light: %.2f, %#010x\n", g_ambient_light.power, g_ambient_light.color);
	done = 1;
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
	cam_list = g_cameras;
	if (!cam_list)
		g_cameras = new;
	else
	{
		while (cam_list->next)
			cam_list = cam_list->next;
		cam_list->next = new;
	}
	printf("camera:\tposition: %.2f %.2f %.2f\n\torientation: %.2f %.2f %.2f\n\tfov: %.2f\n", camera->pos.x, camera->pos.y, camera->pos.z, camera->orientation.x, camera->orientation.y, camera->orientation.z, camera->fov);
	return (1);
}

int		parse_l(char *line)
{
	printf("%s\n", line);
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
	printf("sphere:\tposition: %.2f %.2f %.2f\n\tradius: %.2f\n\tcolor: %#010x\n", sphere->pos.x, sphere->pos.y, sphere->pos.z, sphere->radius, sphere->color);
	return (1);
}

int		parse_pl(char *line)
{
	printf("%s\n", line);
	return (1);
}

int		parse_sq(char *line)
{
	printf("%s\n", line);
	return (1);
}

int		parse_cy(char *line)
{
	printf("%s\n", line);
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
		{"R", &parse_r},
		{"A", &parse_a},
		{"c", &parse_c},
		{"l", &parse_l},
		{"sp", &parse_sp},
		{"pl", &parse_pl},
		{"sq", &parse_sq},
		{"cy", &parse_cy},
		{"tr", &parse_tr},
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
	while(ret == 1)
	{
		ret = get_next_line(fd, &line);
		lookup_table = get_lookup_table();
		while(ft_isspace(*line))
			line++;
		if (!*line)
			continue;
		while ((*lookup_table).key &&
				ft_strncmp(line, (*lookup_table).key, ft_strlen((*lookup_table).key)))
			lookup_table++;
		if (!(*lookup_table).key)
			write(1, "Error\n", 6);
		else
			(*((*lookup_table).value))(line); //TODO error management
	}
	return (1);
}
