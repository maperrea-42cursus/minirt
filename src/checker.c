/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 11:33:50 by maperrea          #+#    #+#             */
/*   Updated: 2021/07/14 15:49:26 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

static int	skip_beginning(char **file, int *i, int *j)
{
	while (ft_isspace(file[*i][*j]))
		(*j)++;
	if (!file[*i][*j])
	{
		(*i)++;
		return (1);
	}
	return (0);
}

void	check_map(char **file)
{
	int				i;
	int				j;
	t_lookup_table	*lookup_table;

	i = 0;
	if (!file)
		error_exit("Error\nfile could not be properly read");
	while (file[i])
	{
		j = 0;
		lookup_table = get_lookup_table();
		if (skip_beginning(file, &i, &j))
			continue ;
		while (lookup_table->key
			&& ft_strncmp(&(file[i][j]), lookup_table->key,
			ft_strlen(lookup_table->key)))
			lookup_table++;
		if (!lookup_table->key)
			error_exit("Error\nunknown identifier");
		(*((t_check *)lookup_table->value))(&(file[i][j]), i + 1);
		i++;
	}
	if (!required_params(0, 0, 0))
		error_exit("Error\nmissing parameter");
}
