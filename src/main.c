/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 19:46:51 by maperrea          #+#    #+#             */
/*   Updated: 2020/10/23 22:33:45 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//somehow returning the intersection would be nice
//might turn exclude in an array if needed
t_objects	*get_closest_obj(t_line3 ray, t_fvec3 *out_intersection, void *exclude)
{
	t_objects	*objs;
	t_objects	*closest_obj;
	t_fvec3		*intersection;
	t_fvec3		*closest_intersection;

	objs = g_objects;
	closest_obj = NULL;
	while (objs)
	{
		if (objs->object != exclude)
		{
			intersection = objs->get_intersection(ray, objs->object);
			if (intersection && is_in_front(ray, *intersection)
				&& (!closest_obj || is_closer(fvec3_sub(*intersection, ray.orig),
							fvec3_sub(*closest_intersection, ray.orig))))
			{
				closest_obj = objs;
				closest_intersection = intersection;
			}
/*			if (intersection)
				printf("line : %.2f,%.2f,%.2f %.2f,%.2f,%.2f\nintersection: %.2f,%.2f,%.2f\n", ray.orig.x, ray.orig.y, ray.orig.z, ray.dest.x, ray.dest.y, ray.dest.z, intersection->x, intersection->y, intersection->z);
			if (intersection && is_in_front(ray, *intersection))
				printf("in front "); */
		}
		objs = objs->next;
	}
	if (closest_intersection)
		*out_intersection = *closest_intersection;
	return (closest_obj);
}

void		cast_rays(t_mlx_image *img, t_grid grid, t_camera *cam)
{
	t_fvec3		pos;
	t_fvec3		intersection;
	t_vec2		grid_pos;
	t_objects	*closest;
	t_line3		ray;

	pos = grid.start;
	grid_pos = (t_vec2){0, 0};
	while(grid_pos.y < grid.size.y)
	{
		while (grid_pos.x < grid.size.x)
		{
			ray = line_from_points(cam->pos, pos);
			closest = get_closest_obj(ray, &intersection, NULL);
			if (!closest)
				img->image_data[grid_pos.y * img->ppl + grid_pos.x] = 0;
			else
				img->image_data[grid_pos.y * img->ppl + grid_pos.x]
					= closest->get_color(ray, intersection, closest->object);
			grid_pos.x++;
			pos = fvec3_add(pos, fvec3_scalar_mult(grid.i, grid.step));
		}	
		grid_pos.y++;
		grid_pos.x = 0;
		pos = fvec3_add(grid.start,
				fvec3_scalar_mult(grid.j, grid_pos.y * grid.step));
	}
}

void	get_image(t_mlx_image *img, t_camera *cam)
{	
	t_grid	grid;

	grid.step = (tan(cam->fov / 2.)) / ((double)g_resolution.x / 2);
	grid.i = fvec3_normalize(fvec3_product((t_fvec3){0., 1., 0.}, cam->orientation));
	grid.j = fvec3_normalize(fvec3_product(cam->orientation, grid.i));
	grid.start = fvec3_add(
					fvec3_sub(
						fvec3_sub(
							fvec3_add(cam->pos, cam->orientation),
							fvec3_scalar_mult(grid.i,
								grid.step * (g_resolution.x / 2))),
						fvec3_scalar_mult(grid.j, grid.step * (g_resolution.y / 2))),
					fvec3_scalar_mult(fvec3_add(grid.i, grid.j), grid.step / 2));
	grid.end = fvec3_sub(
					fvec3_add(
						fvec3_add(
							fvec3_add(cam->pos, cam->orientation),
							fvec3_scalar_mult(grid.i,
								grid.step * (g_resolution.x / 2))),
						fvec3_scalar_mult(grid.j, grid.step * (g_resolution.y / 2))),
					fvec3_scalar_mult(fvec3_add(grid.i, grid.j), grid.step / 2));
	grid.size = g_resolution;
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
	if (!(win_ptr = mlx_new_window(mlx_ptr, g_resolution.x, g_resolution.y, "minirt")))
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
	mlx_hook(win_ptr, 17, 0, exit_hook, NULL);
	mlx_loop(mlx_ptr);
	free_list();
	return (0);
}
