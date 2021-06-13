/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 19:15:17 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 07:02:30 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** test
*/

double	*resolve_second_degree(double a, double b, double c)
{
	double	*result;
	double	delta;

	delta = (b * b) - (4 * a * c);
	if (delta < 0.)
		return (NULL);
	result = malloc(sizeof(double) * 2);
	if (!result)
		return (NULL);
	result[0] = (-b + sqrt(delta)) / (2 * a);
	result[1] = (-b - sqrt(delta)) / (2 * a);
	return (result);
}
