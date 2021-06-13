/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 09:42:01 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 09:44:00 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	fvec3_dot_product(t_fvec3 a, t_fvec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_fvec3	fvec3_scalar_mult(t_fvec3 v, double x)
{
	return ((t_fvec3){v.x * x, v.y * x, v.z * x});
}

int	is_in_front(t_line3 normal, t_fvec3 vec)
{
	return (fvec3_dot_product(normal.dest, fvec3_sub(vec, normal.orig)) >= 0);
}

int	is_closer(t_fvec3 a, t_fvec3 b)
{
	return (fvec3_length(a) <= fvec3_length(b));
}

double	fvec3_length(t_fvec3 vec)
{
	return (sqrt(fvec3_dot_product(vec, vec)));
}
