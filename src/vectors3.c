/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 09:43:40 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 09:44:00 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_line3	line_from_points(t_fvec3 orig, t_fvec3 dest)
{
	return ((t_line3){orig, fvec3_normalize(fvec3_sub(dest, orig))});
}

t_fvec3	*line_intersection(t_line3 a, t_line3 b)
{
	double	p;
	double	q;
	t_fvec3	*intersection;

	p = ((b.dest.y * (b.orig.x - a.orig.x))
			+ (b.dest.x * (a.orig.y - b.orig.y)))
		/ ((b.dest.y * a.dest.x) - (b.dest.x * a.dest.y));
	q = ((a.dest.x * (a.orig.y - b.orig.y))
			+ (a.dest.y * (b.orig.x - a.orig.x)))
		/ ((b.dest.y * a.dest.x) - (b.dest.x * a.dest.y));
	intersection = malloc(sizeof(t_fvec3));
	if (!intersection)
		return (NULL);
	intersection->x = a.orig.x + p * a.dest.x;
	intersection->y = a.orig.y + p * a.dest.y;
	intersection->z = a.orig.z + p * a.dest.z;
	return (intersection);
}

double	fvec3_angle(t_fvec3 a, t_fvec3 b)
{
	return (acos(fvec3_dot_product(fvec3_normalize(a), fvec3_normalize(b))));
}
