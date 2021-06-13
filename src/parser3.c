/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 17:40:56 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 17:47:04 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_r(char *line)
{
	static char	done;

	if (done)
		return (0);
	g_resolution.x = next_int(&line);
	g_resolution.y = next_int(&line);
	printf("\nresolution: %dx%d\n", g_resolution.x, g_resolution.y);
	done = 1;
	return (1);
}

int	parse_a(char *line)
{
	static char	done;

	if (done)
		return (0);
	g_ambient_light.pos = (t_fvec3){0.0, 0.0, 0.0};
	g_ambient_light.power = next_float(&line);
	g_ambient_light.color = next_color(&line);
	printf("\nambient light: %.2f, %#010x\n",
		g_ambient_light.power, g_ambient_light.color);
	done = 1;
	return (1);
}

int	parse_cy(char *line)
{
	t_cylinder		*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (0);
	cylinder->pos = next_fvec3(&line);
	cylinder->axis = fvec3_normalize(next_fvec3(&line));
	cylinder->radius = next_float(&line) / 2.;
	cylinder->height = next_float(&line);
	cylinder->color = next_color(&line);
	add_object(cylinder, &cylinder_intersection, &cylinder_color);
	printf("\ncylinder:\tposition: %.2f %.2f %.2f\n\t\taxis: %.2f %.2f %.2f",
		cylinder->pos.x, cylinder->pos.y, cylinder->pos.z,
		cylinder->axis.x, cylinder->axis.y, cylinder->axis.z);
	printf("\n\t\tdiameter: %.2f\n\t\theight: %.2f\n\t\tcolor: %#010x\n",
		cylinder->radius, cylinder->height, cylinder->color);
	return (1);
}
