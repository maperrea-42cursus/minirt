/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 17:42:09 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 17:44:02 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	next_int(char **str)
{
	to_next_number(str);
	return (ft_atoi(*str));
}

double	next_float(char **str)
{
	double	int_part;
	double	frac_part;
	int		neg;
	int		i;

	i = 0;
	to_next_number(str);
	int_part = (double)ft_atoi(*str);
	neg = (int_part < 0.);
	while (ft_isdigit((*str)[i]) || (*str)[i] == '-')
		i++;
	if ((*str)[i] == '.')
	{
		to_next_number(str);
		frac_part = (double)ft_atoi(*str);
		i = 0;
		while (ft_isdigit((*str)[i]))
			i++;
		frac_part *= pow(10, -i);
		if (neg)
			frac_part = -frac_part;
	}
	else
		frac_part = 0.;
	return (int_part + frac_part);
}

t_vec3	next_vec3(char **str)
{
	t_vec3	vec;

	vec.x = next_int(str);
	vec.y = next_int(str);
	vec.z = next_int(str);
	return (vec);
}

t_fvec3	next_fvec3(char **str)
{
	t_fvec3	vec;

	vec.x = next_float(str);
	vec.y = next_float(str);
	vec.z = next_float(str);
	return (vec);
}

int	next_color(char **str)
{
	int	color;

	color = next_int(str) << 16;
	color += next_int(str) << 8;
	color += next_int(str);
	return (color);
}
