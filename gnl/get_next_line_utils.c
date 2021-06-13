/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:26:05 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 03:22:36 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	**ft_minisplit(char *str, char **strs)
{
	int		l[2];
	int		i;
	int		j;

	i = -1;
	j = 0;
	l[0] = 0;
	l[1] = 0;
	while (str[++i])
		 l[j + (str[i] == '\n' && j == 0 && j++)]++;
	if (
		!(strs[0] = malloc(l[0])) || !(strs[1] = malloc(l[1] + 1)))
		return (NULL);
	i = -1;
	while (str[++i] != '\n' && str[i])
		strs[0][i] = str[i];
	strs[0][i] = 0;
	i += (str[i] == '\n');
	j = 0;
	while (str[i])
		strs[1][j++] = str[i++];
	strs[1][j] = 0;
	free(str);
	return (strs);
}

char	*ft_strrcat(char **str1, char *str2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*str1 && (*str1)[i])
		i++;
	while (str2[j])
		j++;
	ft_str_resize(str1, i + j + 1);
	j = 0;
	while (str2[j])
		(*str1)[i++] = str2[j++];
	(*str1)[i] = 0;
	free(str2);
	return (*str1);
}

void	ft_str_resize(char **str, size_t size)
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = malloc(sizeof(char) * (size + 1));
	if (!tmp)
		return ;
	while (*str && (*str)[i] && i < size)
	{
		tmp[i] = (*str)[i];
		i++;
	}
	tmp[i] = 0;
	free(*str);
	*str = tmp;
}

void	ft_lstadd(t_list **file_list, int fd, char *str)
{
	t_list	*list;

	list = ft_find_fd(*file_list, fd);
	if (!list)
	{
		if (
			!(list = malloc(sizeof(t_list)))
			|| !(list->content = malloc(sizeof(t_file))))
			return ;
		list->content->fd = fd;
		list->content->str = str;
		list->next = NULL;
		if (!(*file_list))
			(*file_list) = list;
		else
		{
			while ((*file_list)->next)
				file_list = &((*file_list)->next);
			(*file_list)->next = list;
		}
	}
	else
		list->content->str = str;
}

void	ft_remove_list_fd(t_list **list, int fd)
{
	t_list	*next;

	if ((*list)->content->fd == fd)
	{
		next = (*list)->next;
		free((*list)->content->str);
		free((*list)->content);
		free(*list);
		*list = next;
	}
	else
	{
		while ((*list)->next && (*list)->next->content->fd != fd)
			list = &((*list)->next);
		if (!(*list)->next)
			return ;
		next = (*list)->next->next;
		free((*list)->next->content->str);
		free((*list)->next->content);
		free((*list)->next);
		(*list)->next = next;
	}
}
