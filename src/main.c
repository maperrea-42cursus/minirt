/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 19:46:51 by maperrea          #+#    #+#             */
/*   Updated: 2020/10/15 06:08:31 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		main(int argc, char **argv)
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_mlx_image		img;

	if (argc < 2)
	{
		write(1, "Error\nNo input\n", 15);
		return (0);
	}
	else
		parse_map(argv[1]);
	if (!(mlx_ptr = mlx_init()))
		return (0);
	if (!(win_ptr = mlx_new_window(mlx_ptr, g_resolution.x, g_resolution.y, "oui")))
		return (0);
	img.image = mlx_new_image(mlx_ptr, 300, 300);
	img.image_data = mlx_get_data_addr(img.image, &img.bpp, &img.size_line, &img.endian);
	img.ppl = img.size_line / (img.bpp / 8);
	for (int x = 0; x < 300; x++)
		for (int y = 0; y < 300; y++)
			((int *)img.image_data)[x * img.ppl + y] = 0x00ff00ff;
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.image, 100, 100);
	mlx_loop(mlx_ptr);
	free_list();
	return (0);
}
