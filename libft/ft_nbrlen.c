/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 14:37:05 by maperrea          #+#    #+#             */
/*   Updated: 2020/02/13 16:56:09 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbrlen(long long nbr)
{
	int					size;
	unsigned long long	n;

	size = 0;
	if (nbr < 0)
		n = -nbr;
	else
		n = nbr;
	while (n > 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}
