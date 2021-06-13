/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 17:52:19 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 17:55:54 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error_exit(const char *str)
{
	printf("%s\n", str);
	exit(1);
}

int	skip_spaces(char **str)
{
	while (ft_isspace(**str))
		(*str)++;
	return (1);
}
