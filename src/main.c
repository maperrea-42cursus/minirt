/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 19:46:51 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/30 10:30:52 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_image(t_mlx_image *img, t_camera *cam)
{	
	t_grid	grid;

	grid.step = (tan(cam->fov / 2.)) / ((double)g_resolution.x / 2);
	grid.i = fvec3_normalize(fvec3_product((t_fvec3){0., 1., 0.},
				cam->orientation));
	if (cam->orientation.x == 0 && cam->orientation.z == 0)
		grid.i = (t_fvec3){1., 0., 0.};
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

int	check_file(char *str)
{
	if (ft_strlen(str) < 3)
		return (0);
	if (ft_strncmp(&(str[ft_strlen(str) - 3]), ".rt", 3))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_mlx_data		mlx;

	if (argc < 2)
		error_exit("Error\nNo input");
	if (!check_file(argv[1]))
		error_exit("Error\nIncorrect file name");
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
