/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 17:50:39 by maperrea          #+#    #+#             */
/*   Updated: 2021/07/14 16:02:55 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_int(char **str, t_args args)
{
	int	value;

	if (!ft_isdigit(**str) && **str != '-' && **str != '+')
		return (0);
	if (args.flag)
	{
		value = ft_atoi(*str);
		if (value < args.data.irange.min || value > args.data.irange.max)
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

//no args check but ok

int	check_float(char **str, t_args args)
{
	(void)args;
	if (!check_int(str, (t_args){0}))
		return (0);
	if (**str == '.')
	{
		(*str)++;
		if (!ft_isdigit(**str))
			return (0);
		if (!check_int(str, (t_args){0}))
			return (0);
	}
	return (1);
}

int	check_vec3(char **str, t_args args)
{
	t_args	new;

	new = (t_args){args.flag,
	{.irange = {args.data.vrange.min.x, args.data.vrange.max.x}}};
	if (!check_int(str, new))
		return (0);
	if (**str != ',')
		return (0);
	(*str)++;
	new = (t_args){args.flag,
	{.irange = {args.data.vrange.min.y, args.data.vrange.max.y}}};
	if (!check_int(str, new))
		return (0);
	if (**str != ',')
		return (0);
	(*str)++;
	new = (t_args){args.flag,
	{.irange = {args.data.vrange.min.z, args.data.vrange.max.z}}};
	if (!check_int(str, new))
		return (0);
	return (1);
}

int	check_fvec3(char **str, t_args args)
{
	t_args	new;

	new = (t_args){args.flag,
	{.frange = {args.data.fvrange.min.x, args.data.fvrange.max.x}}};
	if (!check_float(str, new))
		return (0);
	if (**str != ',')
		return (0);
	(*str)++;
	new = (t_args){args.flag,
	{.frange = {args.data.fvrange.min.y, args.data.fvrange.max.y}}};
	if (!check_float(str, new))
		return (0);
	if (**str != ',')
		return (0);
	(*str)++;
	new = (t_args){args.flag,
	{.frange = {args.data.fvrange.min.z, args.data.fvrange.max.z}}};
	if (!check_float(str, new))
		return (0);
	return (1);
}

int	check_color(char **str, t_args args)
{
	static t_args	defaults = {1, {.vrange = {{0, 0, 0}, {255, 255, 255}}}};

	if (args.flag)
		return (check_vec3(str, args));
	else
		return (check_vec3(str, defaults));
}
