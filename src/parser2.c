/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 17:39:24 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 17:40:00 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_f(char *line)
{
	g_light_factor = next_float(&line);
	printf("\nlight factor:\t%.2f\n", g_light_factor);
	return (1);
}

int	parse_c(char *line)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	if (!camera)
		return (0);
	camera->pos = next_fvec3(&line);
	camera->orientation = fvec3_normalize(next_fvec3(&line));
	camera->fov = (next_float(&line) / 180.) * M_PI;
	add_camera(camera);
	printf("\ncamera:\t\tposition: %.2f %.2f %.2f",
		camera->pos.x, camera->pos.y, camera->pos.z);
	printf("\n\t\torientation: %.2f %.2f %.2f\n\t\tfov: %.2f\n",
		camera->orientation.x, camera->orientation.y,
		camera->orientation.z, camera->fov);
	return (1);
}

int	parse_l(char *line)
{
	t_spherical_light	*light;

	light = malloc(sizeof(t_spherical_light));
	if (!light)
		return (0);
	light->pos = next_fvec3(&line);
	light->power = next_float(&line);
	light->color = next_color(&line);
	add_light(light, &spherical_light_luminosity, &spherical_light_pos);
	printf("\nlight:\t\tposition: %.2f %.2f %.2f",
		light->pos.x, light->pos.y, light->pos.z);
	printf("\n\t\tpower: %.2f\n\t\tcolor: %#010x\n",
		light->power, light->color);
	return (1);
}

int	parse_sp(char *line)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (0);
	sphere->pos = next_fvec3(&line);
	sphere->radius = next_float(&line) / 2.;
	sphere->color = next_color(&line);
	add_object(sphere, &sphere_intersection, &sphere_color);
	printf("\nsphere:\t\tposition: %.2f %.2f %.2f",
		sphere->pos.x, sphere->pos.y, sphere->pos.z);
	printf("\n\t\tradius: %.2f\n\t\tcolor: %#010x\n",
		sphere->radius, sphere->color);
	return (1);
}

int	parse_pl(char *line)
{
	t_plane		*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (0);
	plane->pos = next_fvec3(&line);
	plane->normal = next_fvec3(&line);
	plane->color = next_color(&line);
	add_object(plane, &plane_intersection, &plane_color);
	printf("\nplane:\t\tposition = %.2f %.2f %.2f",
		plane->pos.x, plane->pos.y, plane->pos.z);
	printf("\n\t\tnormal: %.2f %.2f %.2f\n\t\tcolor: %#010x\n",
		plane->normal.x, plane->normal.y, plane->normal.z, plane->color);
	return (1);
}
