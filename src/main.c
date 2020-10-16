/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 19:46:51 by maperrea          #+#    #+#             */
/*   Updated: 2020/10/17 01:07:28 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_objects	*get_closest_obj(t_line3 ray)
{
	t_objects	*objs;
	t_objects	*closest_obj;
	t_fvec3		*intersection;
	t_fvec3		*closest_intersection;

	objs = g_objects;
	closest_obj = NULL;
	while (objs)
	{
		intersection = objs->get_intersection(ray, objs->object);
		if (intersection)
		if (intersection && (!closest_obj ||
				fvec3_length(fvec3_sub(*intersection, ray.orig)) <
				fvec3_length(fvec3_sub(*closest_intersection, ray.orig))))
		{
			closest_obj = objs;
			closest_intersection = intersection;
		}
		objs = objs->next;
	}
	return (closest_obj);
}

void		cast_rays(t_mlx_image *img, t_grid grid, t_camera *cam)
{
	t_fvec3		pos;
	t_vec2		grid_pos;
	t_objects	*closest;

	pos = grid.start;
	grid_pos = (t_vec2){0, 0};
	//TODO start can be > end
	while(pos.y <= grid.end.y)
	{
		while (pos.x <= grid.end.x)
		{
			closest = get_closest_obj((t_line3){cam->pos, fvec3_normalize(fvec3_sub(pos, cam->pos))});
			if (!closest)
				img->image_data[grid_pos.y * img->ppl + grid_pos.x] = 0x00000000;
			else
				img->image_data[grid_pos.y * img->ppl + grid_pos.x] = closest->color;
			grid_pos.x++;
			pos = fvec3_add(pos, fvec3_scalar_mult(grid.i, grid.step));
		}	
		grid_pos.y++;
		grid_pos.x = 0;
		pos = fvec3_add(grid.start, fvec3_scalar_mult(grid.j, grid_pos.y * grid.step));
	}
}

void	get_image(t_mlx_image *img, t_camera *cam)
{	
	t_grid	grid;

	grid.step = (tan(cam->fov / 2.)) / ((double)g_resolution.x / 2);
	grid.i = fvec3_product((t_fvec3){0., 1., 0.}, cam->orientation);
	grid.j = fvec3_product(cam->orientation, grid.i);
	grid.start = fvec3_add(
					fvec3_sub(
						fvec3_sub(
							fvec3_add(cam->pos, cam->orientation),
							fvec3_scalar_mult(grid.i, grid.step * (g_resolution.x / 2))),
						fvec3_scalar_mult(grid.j, grid.step * (g_resolution.y / 2))),
					fvec3_scalar_mult(fvec3_add(grid.i, grid.j), grid.step / 2));
	grid.end = fvec3_sub(
					fvec3_add(
						fvec3_add(
							fvec3_add(cam->pos, cam->orientation),
							fvec3_scalar_mult(grid.i, grid.step * (g_resolution.x / 2))),
						fvec3_scalar_mult(grid.j, grid.step * (g_resolution.y / 2))),
					fvec3_scalar_mult(fvec3_add(grid.i, grid.j), grid.step / 2));

	printf("grid step: %.2g\ngrid i: %.2f %.2f %.2f\ngrid j:%.2f %.2f %.2f\ngrid start: %.2f,%.2f,%.2f\ngrid end:%.2f,%.2f,%.2f\n", grid.step, grid.i.x, grid.i.y, grid.i.z, grid.j.x, grid.j.y, grid.j.z, grid.start.x, grid.start.y, grid.start.z, grid.end.x, grid.end.y, grid.end.z);
	cast_rays(img, grid, cam);
}

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
	parse_map(argv[1]);
	if (!(mlx_ptr = mlx_init()))
		return (0);
	if (!(win_ptr = mlx_new_window(mlx_ptr, g_resolution.x, g_resolution.y, "oui")))
		return (0);
	img.image = mlx_new_image(mlx_ptr, g_resolution.x, g_resolution.y);
	img.image_data = (int *)mlx_get_data_addr(img.image, &img.bpp, &img.size_line, &img.endian);
	img.ppl = img.size_line / (img.bpp / 8);
	if (g_cameras && g_cameras->camera)
	{
		get_image(&img, g_cameras->camera);
		mlx_put_image_to_window(mlx_ptr, win_ptr, (char *)img.image, 0, 0);
		printf("done\n");
	}
	mlx_loop(mlx_ptr);
	free_list();
	return (0);
}
