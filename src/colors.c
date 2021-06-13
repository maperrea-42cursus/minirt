/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:41:47 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 07:04:09 by maperrea         ###   ########.fr       */
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

int	color_add(int a, int b)
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

int	get_light_color(t_lights *lights, t_fvec3 intersection, double angle)
{
	int		color;
	double	distance;
	double	factor;

	distance = fvec3_length(fvec3_sub(intersection,
				lights->get_pos(lights->light)));
	factor = (distance / g_light_factor) + 1;
	factor = 1 / pow(factor, 2);
	color = color_multiply(
			color_multiply(lights->get_luminosity(lights->light),
				((M_PI_2 - angle) / M_PI_2)),
			factor);
	return (color);
}

int	get_illumination(t_fvec3 intersection, void *object,
		t_line3 normal, t_lights *lights)
{
	t_fvec3		closest_intersection;
	t_objects	*closest;
	t_line3		line;

	line = line_from_points(intersection, lights->get_pos(lights->light));
	closest = get_closest_obj(line, &closest_intersection, object, NULL);
	if (!closest
		|| !is_closer(fvec3_sub(closest_intersection, intersection),
			fvec3_sub(lights->get_pos(lights->light), intersection)))
		return (get_light_color(lights,
				intersection, fvec3_angle(normal.dest, line.dest)));
	return (0);
}
