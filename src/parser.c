/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 19:52:18 by maperrea          #+#    #+#             */
/*   Updated: 2020/10/14 22:34:46 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_object(void *object)
{
	t_objects	*list;
	t_objects	*new;

	if (!(new = malloc(sizeof(t_objects))))
		return;
	new->object = object;
	if (!g_objects)
	{
		g_objects = new;
		return;
	}
	list = g_objects;
	while (list->next)
		list = list->next;
	list->next = new;
}

int		parse_r(char *line)
{
	static char done;

	if (done)
		return (0);									//TODO error message
	while(!ft_isdigit(*line))
		line++;
	g_resolution.x = ft_atoi(line);
	while(ft_isdigit(*line))
		line++;
	while(!ft_isdigit(*line))
		line++;
	g_resolution.y = ft_atoi(line);
	printf("resolution: %dx%d\n", g_resolution.x, g_resolution.y);
	done = 1;
	return (1);
}

int		parse_a(char *line)
{
	static char done;

	if (done)
		return (0);									//TODO error message
	printf("%s\n", line);

	done = 1;
	return (1);
}

int		parse_c(char *line)
{
	t_camera	*new;

	printf("%s\n", line);
	if (!(new = malloc(sizeof(t_camera))))
		return (0);
	return (1);
}

int		parse_l(char *line)
{
	printf("%s\n", line);
	return (1);
}

int		parse_sp(char *line)
{
	printf("%s\n", line);
	return (1);
}

int		parse_pl(char *line)
{
	printf("%s\n", line);
	return (1);
}

int		parse_sq(char *line)
{
	printf("%s\n", line);
	return (1);
}

int		parse_cy(char *line)
{
	printf("%s\n", line);
	return (1);
}

int		parse_tr(char *line)
{
	printf("%s\n", line);
	return (1);
}

t_parse	**init_dispatch_table(void)
{
	t_parse	**table;

	if (!(table = malloc(sizeof(t_parse *) * TYPE_COUNT)))
		return (NULL);
	table[RESOLUTION] = &parse_r;
	table[AMBIENT_LIGHT] = &parse_a;
	table[CAMERA] = &parse_c;
	table[LIGHT] = &parse_l;
	table[SPHERE] = &parse_sp;
	table[PLANE] = &parse_pl;
	table[SQUARE] = &parse_sq;
	table[CYLINDER] = &parse_cy;
	table[TRIANGLE] = &parse_tr;
	return (table);
}

char	**init_lookup_table(void)
{
	char **table;

	if (!(table = malloc_list(sizeof(char *) * TYPE_COUNT)))
		return (NULL);
	table[RESOLUTION] = "R";
	table[AMBIENT_LIGHT] = "A";
	table[CAMERA] = "c";
	table[LIGHT] = "l";
	table[SPHERE] = "sp";
	table[PLANE] = "pl";
	table[SQUARE] = "sq";
	table[CYLINDER] = "cy";
	table[TRIANGLE] = "tr";
	return (table);
}

int		get_parse_type(char *line)
{
	static char **lookup_table;
	int i;

	if (!lookup_table)
		lookup_table = init_lookup_table();
	while(ft_isspace(*line))
		line++;
	if (!*line)
		return (NONE);
	i = 0;
	while (i < TYPE_COUNT &&
			ft_strncmp(line, lookup_table[i], ft_strlen(lookup_table[i])))
		i++;
	if (i == TYPE_COUNT)
		i = INVALID;
	return (i);
}

int		parse_map(char *filename)
{
	char	*line;
	t_parse	**dispatch_table;
	int		type;
	int		fd;
	int		ret;

	dispatch_table = init_dispatch_table();
	fd = open(filename, O_RDONLY);
	ret = 1;
	while(ret == 1)
	{
		ret = get_next_line(fd, &line);
		type = get_parse_type(line);
		if (type != NONE)
			if (!(*(dispatch_table[type]))(line))
			{
				write(1, "ERROR\n", 6);						//TODO remove
				return (0);
			}
	}
	return (1);
}
