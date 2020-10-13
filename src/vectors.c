/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:25:51 by maperrea          #+#    #+#             */
/*   Updated: 2020/10/13 20:12:25 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_fvec3		fvec3_div(t_fvec3 vec, double div)
{
	return ((t_fvec3){vec.x / div, vec.y / div, vec.z / div});
}

double		fvec3_length(t_fvec3 vec)
{
	return(sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z)));
}

t_fvec3		fvec3_normalize(t_fvec3 vec)
{
	return (fvec3_div(vec, fvec3_length(vec)));
}

t_fvec3		fvec3_product(t_fvec3 a, t_fvec3 b)
{
	return ((t_fvec3){(a.y * b.z) - (a.z * b.y),
						(a.z * b.x) - (a.x * b.z),
						(a.x * b.y) - (a.y * b.x)});
}
