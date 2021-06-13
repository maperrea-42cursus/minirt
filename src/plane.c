/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:59:31 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 09:02:39 by maperrea         ###   ########.fr       */
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

int	plane_color(t_fvec3 intersection, void *plane, t_extra *extra)
{
	int			color;
	t_lights	*lights;
	t_line3		normal;
	t_plane		*pl;

	(void)extra;
	pl = plane;
	lights = g_lights;
	color = color_multiply(g_ambient_light.color, g_ambient_light.power);
	normal = (t_line3){pl->pos, pl->normal};
	while (lights)
	{
		if (!is_in_front((t_line3){pl->pos, pl->normal},
			lights->get_pos(lights->light)))
			normal.dest = fvec3_scalar_mult(pl->normal, -1.0);
		color = color_add(color, get_illumination(intersection, plane,
					normal, lights));
		lights = lights->next;
	}
	color = color_reflect(pl->color, color);
	return (color);
}
