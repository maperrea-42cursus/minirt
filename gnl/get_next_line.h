/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:40 by maperrea          #+#    #+#             */
/*   Updated: 2020/10/14 18:33:21 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct	s_list
{
	struct s_file	*content;
	struct s_list	*next;
}				t_list;

typedef struct	s_file
{
	int		fd;
	char	*str;
}				t_file;

t_list			*ft_find_fd(t_list *list, int fd);
int				ft_find_nl(char *str);
char			*ft_read_line(int fd, int *flag, char *line);
int				get_next_line(int fd, char **line);

char			**ft_minisplit(char *str, char **strs);
char			*ft_strrcat(char **str1, char *str2);
void			ft_str_resize(char **str, size_t size);
void			ft_lstadd(t_list **list, int fd, char *str);
void			ft_remove_list_fd(t_list **list, int fd);

#endif
