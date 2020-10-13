/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 13:36:16 by maperrea          #+#    #+#             */
/*   Updated: 2020/10/02 16:46:47 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dup;

	if (!(dup = malloc_list(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	(void)ft_strlcpy(dup, str, ft_strlen(str) + 1);
	return (dup);
}
