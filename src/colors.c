/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:41:47 by maperrea          #+#    #+#             */
/*   Updated: 2020/10/20 22:43:05 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		color_multiply(int color, double factor)
{
	unsigned char	*ptr;
	int				i;

	i = 0;
	ptr = (unsigned char *)&color;
	while (i < 4)
	{
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
