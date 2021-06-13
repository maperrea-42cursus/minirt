/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:14:04 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 17:32:34 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_fvec3	*free_set_return(t_fvec3 *a, t_fvec3 *b, t_fvec3 c, t_extra *extra)
{
	free(a);
	extra->normal = (t_line3){
		* b, c};
	return (b);
}

void	calculate_intsersections(t_line3 ray, t_cylinder *cy, t_cy_data *data)
{
	data->i = fvec3_add(fvec3_scalar_mult(data->w, data->dist / cy->radius),
			fvec3_scalar_mult(fvec3_product(data->w, cy->axis),
				sqrt(1 - pow(data->dist / cy->radius, 2))));
	data->line1 = (t_line3){fvec3_add(cy->pos,
			fvec3_scalar_mult(data->i, cy->radius)), cy->axis};
	data->result1 = line_intersection(ray, data->line1);
	data->j = fvec3_sub(fvec3_scalar_mult(data->w, data->dist / cy->radius),
			fvec3_scalar_mult(fvec3_product(data->w, cy->axis),
				sqrt(1 - pow(data->dist / cy->radius, 2))));
	data->line2 = (t_line3){fvec3_add(cy->pos,
			fvec3_scalar_mult(data->j, cy->radius)), cy->axis};
	data->result2 = line_intersection(ray, data->line2);
}

t_fvec3	*cylinder_intersection(t_line3 ray, void *cylinder, t_extra *extra)
{
	t_cylinder	*cy;
	t_cy_data	data;
	t_fvec3		yes;

	cy = (t_cylinder *)cylinder;
	ray.dest = fvec3_normalize(ray.dest);
	data.w = fvec3_normalize(fvec3_product(ray.dest, cy->axis));
	data.dist = fvec3_dot_product(data.w, yes = fvec3_sub(ray.orig, cy->pos));
	if (data.dist > cy->radius || data.dist < -cy->radius)
		return (NULL);
	calculate_intsersections(ray, cy, &data);
	if ((is_closer(fvec3_sub(*data.result1, ray.orig), fvec3_sub(*data.result2,
					ray.orig)) && is_in_front(ray, *data.result1))
		&& fvec3_length(fvec3_sub(*data.result1,
				data.line1.orig)) <= cy->height / 2)
		return (free_set_return(data.result2, data.result1, data.i, extra));
	else if (fvec3_length(fvec3_sub(*data.result2, data.line2.orig))
		<= cy->height / 2)
		return (free_set_return(data.result1, data.result2, data.j, extra));
	free(data.result1);
	free(data.result2);
	return (NULL);
}

int	cylinder_color(t_fvec3 intersection,
								void *cylinder, t_extra *extra)
{
	int			color;
	t_lights	*lights;
	t_line3		normal;

	normal = extra->normal;
	lights = g_lights;
	color = color_multiply(g_ambient_light.color, g_ambient_light.power);
	while (lights)
	{
		if (is_in_front(normal, lights->get_pos(lights->light)))
			color = color_add(color, get_illumination(intersection, cylinder,
						normal, lights));
		lights = lights->next;
	}
	color = color_reflect(((t_cylinder *)cylinder)->color, color);
	return (color);
}
