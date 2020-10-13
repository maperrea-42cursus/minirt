/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:55:18 by maperrea          #+#    #+#             */
/*   Updated: 2020/10/02 16:48:22 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void **ptr, size_t orig_size, size_t new_size)
{
	void	*tmp;

	if (!(tmp = ft_calloc(1, new_size)))
		return (NULL);
	ft_memcpy(tmp, *ptr, orig_size < new_size ? orig_size : new_size);
	free_one(*ptr);
	*ptr = tmp;
	return (tmp);
}
