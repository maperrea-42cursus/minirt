/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 19:52:18 by maperrea          #+#    #+#             */
/*   Updated: 2020/10/13 21:17:53 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_object(void *object)
{
	t_objects	*list;
	t_object	*new;

	if (!(new = malloc(sizeof(t_object))))
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

int		parse_c(char *file)
{
	t_camera	*new;

	if (!(new = malloc(sizeof(t_camera))))
		return (0);
	return (1);
}

int		parse_sp(char *file)
{
	return (1)
}

char	*read_map(char *filename)
{
	int 	fd;
	int		ret;
	char	*file;
	char	buf[257];

	if (!(fd = open(filename, O_RDONLY)))
	{
			perror(NULL);
			return (NULL);
	}
	file = "";
	ret = 256;
	while (ret == 256)
	{
		ret = read(fd, buf, 256);
		buf[ret] = 0;
		file = ft_strjoin(file, buf);
	}
	return (file);
}

int		parse_map(char *filename)
{
	char	*file;

	if (!(file = read_map(filename)))
		return (0);

}
