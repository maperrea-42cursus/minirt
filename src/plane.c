/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:59:31 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/04 19:10:10 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_fvec3	*plane_intersection(t_line3 ray, void *plane, t_extra *extra)
{
	t_plane	*pl;
	double	check;
	double	d;
	t_fvec3	*result;

	(void)extra;
	pl = plane;
	check = fvec3_dot_product(ray.dest, pl->normal);
	if (check == 0)
		return (NULL);
	d = fvec3_dot_product(fvec3_sub(pl->pos, ray.orig), pl->normal) / check;
	result = malloc(sizeof(t_fvec3));
	if (!result)
		return (NULL);
	*result = fvec3_add(ray.orig, fvec3_scalar_mult(ray.dest, d));
	return (result);
}

int		plane_color(t_line3 ray, t_fvec3 intersection, void *plane, t_extra *extra)
{
	int 		color;
	t_objects	*closest;
	t_fvec3		closest_intersection;
	t_lights	*lights;
	t_line3		line;
	t_fvec3		normal;
	t_plane		*pl;

	(void)ray;
	(void)extra;
	pl = plane;
	lights = g_lights;
	color = color_multiply(g_ambient_light.color, g_ambient_light.power);
	if (is_in_front(line_from_points(pl->pos, pl->normal), ((t_camera *)g_cameras->camera)->pos))
		normal = pl->normal;
	else
		normal = fvec3_scalar_mult(pl->normal, -1.0);
	while (lights)
	{
//		if (is_in_front(normal, lights->get_pos(lights->light)))
//		{
			line = line_from_points(intersection, lights->get_pos(lights->light));
			closest = get_closest_obj(line, &closest_intersection, plane, NULL);
			if (!closest ||
					!is_closer(fvec3_sub(closest_intersection, intersection),
					fvec3_sub(lights->get_pos(lights->light), intersection)))
			{
				color = color_add(color, 
					color_multiply(lights->get_luminosity(lights->light),
				(M_PI_2 - fvec3_angle(normal, line.dest)) / M_PI_2));
			}
//		}
		lights = lights->next;
	}
	color = color_reflect(pl->color, color);
	return (color);
}
