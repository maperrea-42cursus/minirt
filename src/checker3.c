/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 17:49:08 by maperrea          #+#    #+#             */
/*   Updated: 2021/07/14 15:57:16 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	line_checker(char *line, t_checker **checkers, t_args *args)
{
	int	i;

	i = 0;
	while (checkers[i])
	{
		skip_spaces(&line);
		if (!(*(checkers[i]))(&line, args[i]))
			return (0);
		i++;
	}
	skip_spaces(&line);
	if (*line)
		return (0);
	return (1);
}

int	required_params(int res, int light, int cam)
{
	static int	resolution = 0;
	static int	ambient_light = 0;
	static int	camera = 0;

	if (res == 1)
		resolution = 1;
	else if (light == 1)
		ambient_light = 1;
	else if (cam == 1)
		camera = 1;
	else
		return (resolution && ambient_light && camera);
	return (0);
}

int	check_r(char *line, int line_nbr)
{
	static int			done = 0;
	static t_checker	*checkers[3] = {&check_int, &check_int, NULL};
	static t_args		args[2] = {{1, {.irange = {1, 3200}}},
		{1, {.irange = {1, 1800}}}};

	if (done)
	{
		printf("Error\nline %d: duplicate resolution\n", line_nbr);
		exit(1);
	}
	line++;
	if (!line_checker(line, checkers, args))
	{
		printf("Error\nline %d: wrong format\n", line_nbr);
		exit(1);
	}
	required_params(1, 0, 0);
	done = 1;
	return (1);
}

int	check_a(char *line, int line_nbr)
{
	static int			done = 0;
	static t_checker	*checkers[3] = {&check_float, &check_color, NULL};
	static t_args		args[2] = {{0}, {0}};

	if (done)
	{
		printf("Error\nline %d: duplicate ambient light\n", line_nbr);
		exit(1);
	}
	line++;
	if (!line_checker(line, checkers, args))
	{
		printf("Error\nline %d: wrong format\n", line_nbr);
		exit(1);
	}
	required_params(0, 1, 0);
	done = 1;
	return (1);
}

int	check_f(char *line, int line_nbr)
{
	static int			done = 0;
	static t_checker	*checkers[2] = {&check_int, NULL};
	static t_args		args[1] = {{0}};

	if (done)
	{
		printf("Error\nline %d: duplicate light factor\n", line_nbr);
		exit(1);
	}
	line++;
	if (!line_checker(line, checkers, args))
	{
		printf("Error\nline %d: wrong format\n", line_nbr);
		exit(1);
	}
	done = 1;
	return (1);
}
