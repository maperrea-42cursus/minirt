/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 15:19:21 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 07:04:59 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	spherical_light_luminosity(void *light)
{
	t_spherical_light	*l;

	l = (t_spherical_light *)light;
	return (color_multiply(l->color, l->power));
}

t_fvec3	spherical_light_pos(void *light)
{
	t_spherical_light	*l;

	l = (t_spherical_light *)light;
	return (l->pos);
}
