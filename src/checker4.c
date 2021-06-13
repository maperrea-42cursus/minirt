/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 17:50:39 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 17:55:40 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_int(char **str, void *range)
{
	int	value;

	if (!ft_isdigit(**str) && **str != '-' && **str != '+')
		return (0);
	if (range)
	{
		value = ft_atoi(*str);
		if (value < ((int *)range)[0] || value > ((int *)range)[1])
			return (0);
	}
	if (**str == '-' || **str == '+')
		(*str)++;
	if (!ft_isdigit(**str))
		return (0);
	while (ft_isdigit(**str))
		(*str)++;
	return (1);
}

int	check_float(char **str, void *args)
{
	(void)args;
	if (!check_int(str, NULL))
		return (0);
	if (**str == '.')
	{
		(*str)++;
		if (!ft_isdigit(**str))
			return (0);
		if (!check_int(str, NULL))
			return (0);
	}
	return (1);
}

int	check_vec3(char **str, void *args)
{
	(void)args;
	if (!check_int(str, NULL))
		return (0);
	if (**str != ',')
		return (0);
	(*str)++;
	if (!check_int(str, NULL))
		return (0);
	if (**str != ',')
		return (0);
	(*str)++;
	if (!check_int(str, NULL))
		return (0);
	return (1);
}

int	check_fvec3(char **str, void *args)
{
	(void)args;
	if (!check_float(str, NULL))
		return (0);
	if (**str != ',')
		return (0);
	(*str)++;
	if (!check_float(str, NULL))
		return (0);
	if (**str != ',')
		return (0);
	(*str)++;
	if (!check_float(str, NULL))
		return (0);
	return (1);
}

int	check_color(char **str, void *args)
{
	static int	range[2] = {0, 255};

	(void)args;
	if (!check_int(str, range))
		return (0);
	if (**str != ',')
		return (0);
	(*str)++;
	if (!check_int(str, range))
		return (0);
	if (**str != ',')
		return (0);
	(*str)++;
	if (!check_int(str, range))
		return (0);
	return (1);
}
