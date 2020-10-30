/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:14:04 by maperrea          #+#    #+#             */
/*   Updated: 2020/10/30 19:28:07 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_fvec3		*cylinder_intersection(t_line3 ray, void *cylinder)
{
	t_cylinder	*cy;
	t_fvec3		w;
	t_fvec3		i;
	t_fvec3		j;
	t_fvec3		*result1;
	t_fvec3		*result2;
	double		dist;
	double		cos_alpha;

	cy = (t_cylinder *)cylinder;
	w = fvec3_product(ray.dest, cy->axis);
	dist = fvec3_dot_product(w, fvec3_sub(ray.orig, cy->pos));
	if (dist > cy->radius)
		return (NULL);
	cos_alpha = dist / cy->radius;
	i = fvec3_add(fvec3_scalar_mult(w, cos_alpha),
			fvec3_scalar_mult(ray.dest, sqrt(1 - pow(cos_alpha, 2))));
	j = fvec3_sub(fvec3_scalar_mult(w, cos_alpha),
			fvec3_scalar_mult(ray.dest, sqrt(1 - pow(cos_alpha, 2))));
	result1 = line_intersection(ray,
line_from_points(fvec3_add(cy->pos, fvec3_scalar_mult(i, cy->radius)), cy->axis));
	result2 = line_intersection(ray,
line_from_points(fvec3_add(cy->pos, fvec3_scalar_mult(j, cy->radius)), cy->axis));
	if (is_closer(fvec3_sub(*result1, ray.orig), fvec3_sub(*result2, ray.orig)))
		free(result2);
	else
		free(result1);
	if (is_closer(fvec3_sub(*result1, ray.orig), fvec3_sub(*result2, ray.orig)))
		return (result1);
	else
		return (result2);
}

int			cylinder_color(t_line3 ray, t_fvec3 intersection, void *cylinder)
{
	(void)ray;
	(void)intersection;
	return (((t_cylinder *)cylinder)->color);
}
