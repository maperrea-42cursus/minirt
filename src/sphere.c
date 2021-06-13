/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 18:59:33 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 09:02:39 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_fvec3	substitute_in_line(t_line3 ray, double t)
{
	return ((t_fvec3){
		ray.orig.x + t * ray.dest.x,
		ray.orig.y + t * ray.dest.y,
		ray.orig.z + t * ray.dest.z
	});
}

/*
** c (params[2]) does not change for a given object -> optimisation to be done;
*/

double	*sphere_intersection_params(t_line3 ray, t_sphere *sphere)
{
	double	*params;

	params = malloc(sizeof(double) * 3);
	if (!params)
		return (NULL);
	params[0] = pow(fvec3_length(ray.dest), 2);
	params[1] = 2 * fvec3_dot_product(ray.dest,
			fvec3_sub(ray.orig, sphere->pos));
	params[2] = fvec3_dot_product(fvec3_sub(ray.orig, sphere->pos),
			fvec3_sub(ray.orig, sphere->pos)) - pow(sphere->radius, 2);
	return (params);
}

t_fvec3	*free_return(t_fvec3 *a, t_fvec3 *b)
{
	free(a);
	return (b);
}

t_fvec3	*sphere_intersection(t_line3 ray, void *sphere, t_extra *extra)
{
	t_fvec3		*result1;
	t_fvec3		*result2;
	double		*t;
	double		*params;

	(void)extra;
	params = sphere_intersection_params(ray, sphere);
	t = resolve_second_degree(params[0], params[1], params[2]);
	free(params);
	if (!t)
		return (NULL);
	result1 = malloc(sizeof(t_fvec3));
	result2 = malloc(sizeof(t_fvec3));
	if (!result1 || !result2)
		return (NULL);
	*result1 = substitute_in_line(ray, t[0]);
	*result2 = substitute_in_line(ray, t[1]);
	free(t);
	if (is_closer(fvec3_sub(*result1, ray.orig),
			fvec3_sub(*result2, ray.orig)))
		return (free_return(result2, result1));
	else
		return (free_return(result1, result2));
}

int	sphere_color(t_fvec3 intersection,
					void *sphere, t_extra *extra)
{
	int			color;
	t_lights	*lights;
	t_line3		normal;

	(void)extra;
	lights = g_lights;
	color = color_multiply(g_ambient_light.color, g_ambient_light.power);
	normal = line_from_points(((t_sphere *)sphere)->pos, intersection);
	normal.orig = fvec3_add(normal.orig,
			fvec3_scalar_mult(normal.dest, ((t_sphere *)sphere)->radius));
	while (lights)
	{
		if (is_in_front(normal, lights->get_pos(lights->light)))
			color = color_add(color, get_illumination(intersection, sphere,
						normal, lights));
		lights = lights->next;
	}
	color = color_reflect(((t_sphere *)sphere)->color, color);
	return (color);
}
