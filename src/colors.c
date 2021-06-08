/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:41:47 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/08 23:04:13 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	color_multiply(int color, double factor)
{
	unsigned char	*ptr;
	int				i;

	i = 0;
	ptr = (unsigned char *)&color;
	while (i < 4)
	{
		if (ptr[i] * factor > 255)
			ptr[i] = 255;
		else
			ptr[i] *= factor;
		i++;
	}
	return (color);
}

int	color_reflect(int a, int b)
{
	unsigned char	*ptr_a;
	unsigned char	*ptr_b;
	int				i;

	i = 0;
	ptr_a = (unsigned char *)&a;
	ptr_b = (unsigned char *)&b;
	while (i < 4)
	{
		ptr_a[i] = (float)ptr_a[i] * ((float)ptr_b[i] / 255);
		i++;
	}
	return (a);
}

int color_add(int a, int b)
{
	unsigned char	*ptr_a;
	unsigned char	*ptr_b;
	int				i;

	i = 0;
	ptr_a = (unsigned char *)&a;
	ptr_b = (unsigned char *)&b;
	while (i < 4)
	{
		if (ptr_a[i] + ptr_b[i] > 255)
			ptr_a[i] = 255;
		else
			ptr_a[i] += ptr_b[i];
		i++;
	}
	return (a);
}

int add_light_color(int color, t_lights *lights, t_fvec3 intersection, double angle)
{
	double	distance;
	double	factor;

	distance = fvec3_length(fvec3_sub(intersection, lights->get_pos(lights->light)));
	factor = (distance / g_light_factor) + 1;
	factor = 1 / pow(factor, 2);
	color = color_add(color, color_multiply(
color_multiply(lights->get_luminosity(lights->light), ((M_PI_2 - angle) / M_PI_2)),
	factor));
	return (color);
}
