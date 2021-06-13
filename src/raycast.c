/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 09:37:55 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 17:38:57 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//might turn exclude in an array if needed

t_objects	*is_closer_intersection(t_line3 ray, t_objects *objs,
		t_fvec3 **closest_intersection, t_extra *extra)
{
	t_fvec3	*intersection;
	t_extra	ex;

	intersection = objs->get_intersection(ray, objs->object, &ex);
	if (intersection && is_in_front(ray, *intersection)
		&& (!*closest_intersection
			|| is_closer(fvec3_sub(*intersection, ray.orig),
				fvec3_sub(**closest_intersection, ray.orig))))
	{
		free(*closest_intersection);
		*closest_intersection = intersection;
		if (extra)
			*extra = ex;
		return (objs);
	}
	free(intersection);
	return (NULL);
}

t_objects	*get_closest_obj(t_line3 ray, t_fvec3 *out_intersection,
					void *exclude, t_extra *extra)
{
	t_objects	*objs;
	t_objects	*closest_obj;
	t_fvec3		*closest_intersection;
	t_objects	*last_obj;

	objs = g_objects;
	closest_obj = NULL;
	closest_intersection = NULL;
	while (objs)
	{
		if (objs->object != exclude)
		{
			last_obj = is_closer_intersection(ray, objs,
					&closest_intersection, extra);
			if (last_obj)
				closest_obj = last_obj;
		}
		objs = objs->next;
	}
	if (closest_intersection)
	{
		ft_memcpy(out_intersection, closest_intersection, sizeof(t_fvec3));
		free(closest_intersection);
	}
	return (closest_obj);
}

void	cast_rays(t_mlx_image *img, t_grid grid, t_camera *cam)
{
	t_fvec3		pos;
	t_fvec3		intersection;
	t_vec2		grid_pos;
	t_objects	*closest;
	t_extra		extra;

	pos = grid.start;
	grid_pos = (t_vec2){-1, -1};
	while (++grid_pos.y < grid.size.y)
	{
		while (++grid_pos.x < grid.size.x)
		{
			closest = get_closest_obj(line_from_points(cam->pos, pos),
					&intersection, NULL, &extra);
			if (!closest)
				img->image_data[grid_pos.y * img->ppl + grid_pos.x] = 0;
			else
				img->image_data[grid_pos.y * img->ppl + grid_pos.x]
					= closest->get_color(intersection, closest->object, &extra);
			pos = fvec3_add(pos, fvec3_scalar_mult(grid.i, grid.step));
		}	
		grid_pos.x = -1;
		pos = fvec3_add(grid.start,
				fvec3_scalar_mult(grid.j, grid_pos.y * grid.step));
	}
}
