/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 11:33:50 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 14:05:38 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error_exit(const char *str)
{
	printf("%s\n", str);
	exit(1);
}

int skip_spaces(char **str)
{
	while (ft_isspace(**str))
		(*str)++;
	return (1);
}

int	check_int(char **str, void *range)
{
	int value;

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

int check_float(char **str, void *args)
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

int check_vec3(char **str, void *args)
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

int check_fvec3(char **str, void *args)
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

int check_color(char **str, void *args)
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

int	line_checker(char *line, t_checker **checkers, void **args)
{
	int i;

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

int	check_r(char *line, int line_nbr)
{
	static t_checker	*checkers[3] = {&check_int, &check_int, NULL};
	static void			*args[2] = {NULL, NULL};

	line++;
	if (!line_checker(line, checkers, args))
	{
		printf("Error: line %d: wrong format\n", line_nbr);
		exit(1);
	}
	return (1);
}

int	check_a(char *line, int line_nbr)
{
	static t_checker	*checkers[3] = {&check_float, &check_color, NULL};
	static void			*args[2] = {NULL, NULL};

	line++;
	if (!line_checker(line, checkers, args))
	{
		printf("Error: line %d: wrong format\n", line_nbr);
		exit(1);
	}
	return (1);
}

int	check_f(char *line, int line_nbr)
{
	static t_checker	*checkers[2] = {&check_int, NULL};
	static void			*args[1] = {NULL};

	line++;
	if (!line_checker(line, checkers, args))
	{
		printf("Error: line %d: wrong format\n", line_nbr);
		exit(1);
	}
	return (1);
}

int	check_c(char *line, int line_nbr)
{
	static t_checker	*checkers[4]
		= {&check_fvec3, &check_fvec3, &check_float, NULL};
	static void			*args[3] = {NULL, NULL, NULL};

	line++;
	if (!line_checker(line, checkers, args))
	{
		printf("Error: line %d: wrong format\n", line_nbr);
		exit(1);
	}
	return (1);
}

int	check_l(char *line, int line_nbr)
{
	static t_checker	*checkers[4]
		= {&check_fvec3, &check_float, &check_color, NULL};
	static void			*args[3] = {NULL, NULL, NULL};

	line++;
	if (!line_checker(line, checkers, args))
	{
		printf("Error: line %d: wrong format\n", line_nbr);
		exit(1);
	}
	return (1);
}

int	check_sp(char *line, int line_nbr)
{
	static t_checker	*checkers[4]
		= {&check_fvec3, &check_float, &check_color, NULL};
	static void			*args[3] = {NULL, NULL, NULL};

	line += 2;
	if (!line_checker(line, checkers, args))
	{
		printf("Error: line %d: wrong format\n", line_nbr);
		exit(1);
	}
	return (1);
}

int	check_pl(char *line, int line_nbr)
{
	static t_checker	*checkers[4]
		= {&check_fvec3, &check_fvec3, &check_color, NULL};
	static void			*args[3] = {NULL, NULL, NULL};

	line += 2;
	if (!line_checker(line, checkers, args))
	{
		printf("Error: line %d: wrong format\n", line_nbr);
		exit(1);
	}
	return (1);
}

int	check_cy(char *line, int line_nbr)
{
	static t_checker	*checkers[6]
		= {&check_fvec3, &check_fvec3, &check_float,
			&check_float, &check_color, NULL};
	static void			*args[5] = {NULL, NULL, NULL, NULL, NULL};

	line += 2;
	if (!line_checker(line, checkers, args))
	{
		printf("Error: line %d: wrong format\n", line_nbr);
		exit(1);
	}
	return (1);
}

static int	comment(char *line, int line_nbr)
{
	(void)line;
	(void)line_nbr;
	return (1);
}

static t_lookup_table	*get_lookup_table(void)
{
	static t_lookup_table	table[] = {
		{"sp", &check_sp},
		{"pl", &check_pl},
		{"cy", &check_cy},
		{"R", &check_r},
		{"A", &check_a},
		{"F", &check_f},
		{"c", &check_c},
		{"l", &check_l},
		{"#", &comment},
		{NULL, NULL}
	};

	return (table);
}

void	check_map(char **file)
{
	int				i;
	int				j;
	t_lookup_table	*lookup_table;

	i = 0;
	if (!file)
		error_exit("Error: file could not be properly read");
	while (file[i])
	{
		j = 0;
		lookup_table = get_lookup_table();
		while (ft_isspace(file[i][j]))
			j++;
		if (!file[i][j])
		{
			i++;
			continue ;
		}
		while (lookup_table->key
			&& ft_strncmp(&(file[i][j]), lookup_table->key,
				ft_strlen(lookup_table->key)))
			lookup_table++;
		if (!lookup_table->key)
			error_exit("Error: unknown identifier");
		(*((t_check *)lookup_table->value))(&(file[i][j]), i + 1);
		i++;
	}
}
