/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:25:57 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 03:20:28 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_find_fd(t_list *list, int fd)
{
	while (list)
	{
		if (list->content->fd == fd)
			return (list);
		list = list->next;
	}
	return (NULL);
}

int	ft_find_nl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_read_line(int fd, int *flag, char *line)
{
	char	*buf;

	while (*flag > 0 && !ft_find_nl(line))
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return (NULL);
		*flag = read(fd, buf, BUFFER_SIZE);
		buf[*flag] = 0;
		ft_strrcat(&line, buf);
	}
	if (*line && ft_find_nl(line))
		*flag = 1;
	return (line);
}

int	get_next_line(int fd, char **line)
{
	static t_list	*file_list;
	t_list			*file;
	char			*tmp[2];
	int				flag;

	flag = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	file = ft_find_fd(file_list, fd);
	if (file)
		ft_minisplit(ft_read_line(fd, &flag, file->content->str), tmp);
	else
		ft_minisplit(ft_read_line(fd, &flag, NULL), tmp);
	ft_lstadd(&file_list, fd, tmp[1]);
	*line = tmp[0];
	if (!tmp[1] || !*(tmp[1]))
		ft_remove_list_fd(&file_list, fd);
	return (flag);
}
