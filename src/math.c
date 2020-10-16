/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 19:15:17 by maperrea          #+#    #+#             */
/*   Updated: 2020/10/17 00:42:20 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** test
*/

double		*resolve_second_degree(double a, double b, double c)
{
	double	*result;
	double	delta;

//	printf("a,b,c: %.2f %.2f %.2f\n", a, b, c);
//	printf("b * b: %.2f\n", b * b);
//	printf("4 * a * c: %.2f\n", 4 * a * c);
	delta = (b * b) - (4 * a * c);
//	printf("delta: %.2f\n", delta);
	if (delta < 0.)
		return (NULL);
	if (!(result = malloc(sizeof(double) * 2)))
		return (NULL);
	result[0] = (-b + sqrt(delta)) / (2 * a);
	result[1] = (-b - sqrt(delta)) / (2 * a);
	return (result);
}
