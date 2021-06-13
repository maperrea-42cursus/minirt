/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 19:46:51 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 12:04:14 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_image(t_mlx_image *img, t_camera *cam)
{	
	t_grid	grid;

	grid.step = (tan(cam->fov / 2.)) / ((double)g_resolution.x / 2);
	grid.i = fvec3_normalize(fvec3_product((t_fvec3){0., 1., 0.},
				cam->orientation));
	grid.j = fvec3_normalize(fvec3_product(grid.i, cam->orientation));
	grid.start = fvec3_add(fvec3_sub(fvec3_sub(
					fvec3_add(cam->pos, cam->orientation),
					fvec3_scalar_mult(grid.i,
						grid.step * (g_resolution.x / 2))),
				fvec3_scalar_mult(grid.j, grid.step * (g_resolution.y / 2))),
			fvec3_scalar_mult(fvec3_add(grid.i, grid.j), grid.step / 2));
	grid.end = fvec3_sub(fvec3_add(fvec3_add(
					fvec3_add(cam->pos, cam->orientation),
					fvec3_scalar_mult(grid.i,
						grid.step * (g_resolution.x / 2))),
				fvec3_scalar_mult(grid.j, grid.step * (g_resolution.y / 2))),
			fvec3_scalar_mult(fvec3_add(grid.i, grid.j), grid.step / 2));
	grid.size = g_resolution;
	cast_rays(img, grid, cam);
}

void	init_cam(t_mlx_data *mlx)
{
	t_mlx_image		*img;

	if (g_cameras && g_cameras->camera)
	{
		if (!g_cameras->img)
		{
			img = malloc(sizeof(t_mlx_image));
			if (!img)
				return ;
			img->image = mlx_new_image(mlx->mlx_ptr,
					g_resolution.x, g_resolution.y);
			img->image_data = (int *)mlx_get_data_addr(img->image,
					&img->bpp, &img->size_line, &img->endian);
			img->ppl = img->size_line / (img->bpp / 8);
			get_image(img, g_cameras->camera);
			g_cameras->img = img;
		}
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
			(char *)g_cameras->img->image, 0, 0);
		free_list();
		printf("done\n");
	}
}

int	main(int argc, char **argv)
{
	t_mlx_data		mlx;

	if (argc < 2)
	{
		write(1, "Error\nNo input\n", 15);
		return (0);
	}
	parse_map(argv[1]);
	mlx.mlx_ptr = mlx_init();
	if (!mlx.mlx_ptr)
		return (0);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr,
			g_resolution.x, g_resolution.y, "minirt");
	if (!mlx.win_ptr)
		return (0);
	init_cam(&mlx);
	mlx_hook(mlx.win_ptr, 17, 0, exit_hook, NULL);
	mlx_hook(mlx.win_ptr, 2, 1L << 0, key_hook, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
