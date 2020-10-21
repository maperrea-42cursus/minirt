/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:25:51 by maperrea          #+#    #+#             */
/*   Updated: 2020/10/21 22:47:59 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_fvec3		fvec3_div(t_fvec3 vec, double div)
{
	return ((t_fvec3){vec.x / div, vec.y / div, vec.z / div});
}

t_fvec3		fvec3_normalize(t_fvec3 vec)
{
	return (fvec3_div(vec, fvec3_length(vec)));
}

t_fvec3		fvec3_add(t_fvec3 a, t_fvec3 b)
{
	return ((t_fvec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_fvec3		fvec3_sub(t_fvec3 a, t_fvec3 b)
{
	return ((t_fvec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_fvec3		fvec3_product(t_fvec3 a, t_fvec3 b)
{
	return ((t_fvec3){(a.y * b.z) - (a.z * b.y),
						(a.z * b.x) - (a.x * b.z),
						(a.x * b.y) - (a.y * b.x)});
}

double		fvec3_dot_product(t_fvec3 a, t_fvec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_fvec3		fvec3_scalar_mult(t_fvec3 v, double x)
{
	return ((t_fvec3){ v.x * x, v.y * x, v.z * x});
}

int			is_in_front(t_line3 normal, t_fvec3 vec)
{
	return (fvec3_dot_product(normal.dest, fvec3_sub(vec, normal.orig)) >= 0);
}

double		fvec3_length(t_fvec3 vec)
{
	return(sqrt(fvec3_dot_product(vec, vec)));
}
