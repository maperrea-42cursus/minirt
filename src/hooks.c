/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 19:50:34 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 07:04:28 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_hook(int keycode, t_mlx_data *mlx)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 123)
	{
		g_cameras = g_cameras->previous;
		init_cam(mlx);
	}
	else if (keycode == 124)
	{
		g_cameras = g_cameras->next;
		init_cam(mlx);
	}
	return (0);
}

int	exit_hook(void)
{
	exit(0);
	return (0);
}
