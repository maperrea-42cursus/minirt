/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 18:59:33 by maperrea          #+#    #+#             */
/*   Updated: 2020/10/22 18:24:16 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_fvec3		substitute_in_line(t_line3 ray, double t)
{
	return ((t_fvec3){
			ray.orig.x + t * (ray.dest.x - ray.orig.x),
			ray.orig.y + t * (ray.dest.y - ray.orig.y),
			ray.orig.z + t * (ray.dest.z - ray.orig.z)
	});
}

/*
** c (params[2]) does not change for a given object -> optimisation to be done;
*/

double		*sphere_intersection_params(t_line3 ray, t_sphere *sphere)
{
	double	*params;

	if (!(params = malloc(sizeof(double) * 3)))
		return (NULL);
	params[0] = pow(fvec3_length(ray.dest), 2);
	params[1] = 2 * fvec3_dot_product(ray.dest, fvec3_sub(ray.orig, sphere->pos));
	params[2] = fvec3_dot_product(fvec3_sub(ray.orig, sphere->pos), fvec3_sub(ray.orig, sphere->pos)) - pow(sphere->radius, 2);
	return (params);
}

/*
** I should really split the return (NULL) if into multiple ones but yeah, norm
** also, I do the same if twice as it is slightly shorter
*/

t_fvec3		*sphere_intersection(t_line3 ray, void *sphere)
{
	t_fvec3		*result1;
	t_fvec3		*result2;
	double		*t;
	double		*params;

	params = sphere_intersection_params(ray, sphere);
	t = resolve_second_degree(params[0], params[1], params[2]);
	//printf("params: %p\n", params);
	free(params);
	result1 = malloc(sizeof(t_fvec3));
	result2 = malloc(sizeof(t_fvec3));
	if (!t || !result1 || !result2)
		return (NULL);
	*result1 = substitute_in_line(ray, t[0]);
	*result2 = substitute_in_line(ray, t[1]);
	//printf("t: %p\n", t);
	free(t);
	//printf("result1: %p\nresult2 :%p\n", result1, result2);
	if (fvec3_length(fvec3_sub(*result1, ray.orig))
			< fvec3_length(fvec3_sub(*result2, ray.orig)))
		free(result2);
	else
		free(result1);
	if (fvec3_length(fvec3_sub(*result1, ray.orig))
			< fvec3_length(fvec3_sub(*result2, ray.orig)))
		return (result1);
	else
		return (result2);
};

int			sphere_color(t_line3 ray, void *sphere)
{
	int			color;
	t_fvec3		*intersection;
	t_objects	*closest;
	t_lights	*lights;
	t_line3		line;

	return (((t_sphere *)sphere)->color);
	lights = g_lights;
	intersection = sphere_intersection(ray, sphere);
	color = 0;
	while (lights)
	{
		line = (t_line3){*intersection, 
fvec3_normalize(fvec3_sub(lights->get_pos(lights->light), *intersection))};
		closest = get_closest_obj(line, sphere);
		if (!closest)
			return (0x00ff0000);
		if (!is_closer(
fvec3_sub(*closest->get_intersection(line, closest->object), *intersection),
fvec3_sub(lights->get_pos(lights->light), *intersection)))
			return (0x0000ff00);
		lights = lights->next;
	}
	if (closest->object != sphere)
		return (0x00000000);
	else
		return (0x00ffffff);
}
