/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:14:04 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/08 21:02:55 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_fvec3		*cylinder_intersection(t_line3 ray, void *cylinder, t_extra *extra)
{
	t_cylinder	*cy;
	t_fvec3		w;
	t_fvec3		i;
	t_fvec3		j;
	t_fvec3		*result1;
	t_fvec3		*result2;
	t_line3		line1;
	t_line3		line2;
	double		dist;
	double		cos_alpha;

	cy = (t_cylinder *)cylinder;
	ray.dest = fvec3_normalize(ray.dest);
	//w is weird for nearly parallel vectors
	w = fvec3_product(ray.dest, cy->axis);
//	printf("w: %g %g %g\n", w.x, w.y, w.z);
	w = fvec3_normalize(w);
	//projects both points onto w
	dist = fvec3_dot_product(w, fvec3_sub(ray.orig, cy->pos));
	//printf("cylinder: %f %f %f | %g %g %g\n", cy->pos.x, cy->pos.y, cy->pos.z, cy->axis.x, cy->axis.y, cy->axis.z);
	//printf("ray: %g %g %g\nw: %g %g %g\ndist: %f\n", ray.dest.x, ray.dest.y, ray.dest.z, w.x, w.y, w.z, dist);
	if (dist > cy->radius || dist < -cy->radius)
		return (NULL);
	//printf("dist: %g\n", dist);
	cos_alpha = dist / cy->radius;
	//printf("cos_alpha: %g\n", cos_alpha);
	i = fvec3_add(fvec3_scalar_mult(w, cos_alpha),
fvec3_scalar_mult(fvec3_product(w, cy->axis), sqrt(1 - pow(cos_alpha, 2))));
	j = fvec3_sub(fvec3_scalar_mult(w, cos_alpha),
fvec3_scalar_mult(fvec3_product(w, cy->axis), sqrt(1 - pow(cos_alpha, 2))));
	//printf("i: %f %f %f\nj: %f %f %f\n", i.x, i.y, i.z, j.x, j.y, j.z);
	line1 = (t_line3){fvec3_add(cy->pos, fvec3_scalar_mult(i, cy->radius)), cy->axis};
	result1 = line_intersection(ray, line1);
	line2 = (t_line3){fvec3_add(cy->pos, fvec3_scalar_mult(j, cy->radius)), cy->axis};
	result2 = line_intersection(ray, line2);
	//printf("line1: %f %f %f | %f %f %f\nline2: %f %f %f | %f %f %f\n", line1.orig.x, line1.orig.y, line1.orig.z, line1.dest.x, line1.dest.y, line1.dest.z, line2.orig.x, line2.orig.y, line2.orig.z, line2.dest.x, line2.dest.y, line2.dest.z);
	//printf("ray: %f %f %f | %f %f %f\n", ray.orig.x, ray.orig.y, ray.orig.z, ray.dest.x, ray.dest.y, ray.dest.z);
	//printf("result1: %f %f %f\nresult2: %f %f %f\n", result1->x, result1->y, result1->z, result2->x, result2->y, result2->z);
	if (is_closer(fvec3_sub(*result1, ray.orig), fvec3_sub(*result2, ray.orig))
		&& fvec3_length(fvec3_sub(*result1, line1.orig)) <= cy->height / 2)
	{
		free(result2);
		extra->normal = (t_line3){*result1, i};
//		printf("i chosen\n");
		return (result1);
	}
	else if (fvec3_length(fvec3_sub(*result2, line2.orig)) <= cy->height / 2)
	{
		free(result1);
		extra->normal = (t_line3){*result2, j};
//		printf("j chosen\n");
		return (result2);
	}
	else
	{
		free(result1);
		free(result2);
		return (NULL);
	}
}

int			cylinder_color(t_line3 ray, t_fvec3 intersection,
								void *cylinder, t_extra *extra)
{
	int			color;
	t_objects	*closest;
	t_fvec3		closest_intersection;
	t_lights	*lights;
	t_line3		line;
	t_line3		normal;

	(void)ray;
	(void)intersection;
	normal = extra->normal;
	lights = g_lights;
	color = color_multiply(g_ambient_light.color, g_ambient_light.power);
	while (lights)
	{
		if (is_in_front(normal, lights->get_pos(lights->light)))
		{
			line = line_from_points(intersection, lights->get_pos(lights->light));
			closest = get_closest_obj(line, &closest_intersection, cylinder, NULL);
			if (!closest ||
					!is_closer(fvec3_sub(closest_intersection, intersection),
					fvec3_sub(lights->get_pos(lights->light), intersection)))
			color = add_light_color(color, lights,
						intersection, fvec3_angle(normal.dest, line.dest));
		}
		lights = lights->next;
	}
	color = color_reflect(((t_cylinder *)cylinder)->color, color);
	return (color);
}
