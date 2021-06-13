/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 19:52:18 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 17:46:41 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	comment(char *line)
{
	(void)line;
	printf("\ncomment\n");
	return (1);
}

static t_lookup_table	*get_lookup_table(void)
{
	static t_lookup_table	table[] = {
		{"sp", &parse_sp},
		{"pl", &parse_pl},
		{"cy", &parse_cy},
		{"R", &parse_r},
		{"A", &parse_a},
		{"F", &parse_f},
		{"c", &parse_c},
		{"l", &parse_l},
		{"#", &comment},
		{NULL, NULL}
	};

	return (table);
}

char	**read_file(char *filename)
{
	char	*file;
	char	buf[513];
	int		ret;
	int		fd;

	ret = 1;
	file = "";
	fd = open(filename, O_RDONLY);
	while (ret > 0)
	{
		ret = read(fd, buf, 512);
		buf[ret] = 0;
		file = ft_strjoin(file, buf);
	}
	return (ft_split(file, '\n'));
}

void	parse_map(char *filename)
{
	char			**file;
	t_lookup_table	*lookup_table;

	g_light_factor = 1;
	file = read_file(filename);
	check_map(file);
	while (*file)
	{
		lookup_table = get_lookup_table();
		while (ft_isspace(**file))
			(*file)++;
		if (!**file)
		{
			file++;
			continue ;
		}
		while (lookup_table->key
			&& ft_strncmp(*file, lookup_table->key,
				ft_strlen(lookup_table->key)))
			lookup_table++;
		(*((t_parse *)lookup_table->value))(*file);
		file++;
	}
}
