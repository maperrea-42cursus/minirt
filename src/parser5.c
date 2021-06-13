/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 17:44:10 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 17:45:50 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_object(void *object,
		t_get_intersection *intersection, t_get_color *color)
{
	t_objects	*list;
	t_objects	*new;

	new = malloc(sizeof(t_objects));
	if (!new)
		return ;
	new->object = object;
	new->get_intersection = intersection;
	new->get_color = color;
	new->next = NULL;
	if (!g_objects)
	{
		g_objects = new;
		return ;
	}
	list = g_objects;
	while (list->next)
		list = list->next;
	list->next = new;
}

void	add_light(void *light, t_get_luminosity *luminosity, t_get_pos *pos)
{
	t_lights	*list;
	t_lights	*new;

	new = malloc(sizeof(t_lights));
	if (!new)
		return ;
	new->light = light;
	new->get_luminosity = luminosity;
	new->get_pos = pos;
	new->next = NULL;
	if (!g_lights)
	{
		g_lights = new;
		return ;
	}
	list = g_lights;
	while (list->next)
		list = list->next;
	list->next = new;
}

void	add_camera(void *camera)
{
	t_cameras	*new;
	t_cameras	*cam_list;

	new = malloc(sizeof(t_cameras));
	if (!new)
		return ;
	new->camera = camera;
	new->next = new;
	new->previous = new;
	new->img = NULL;
	cam_list = g_cameras;
	if (!cam_list)
		g_cameras = new;
	else
	{
		while (cam_list->next != g_cameras)
			cam_list = cam_list->next;
		cam_list->next = new;
		new->previous = cam_list;
		g_cameras->previous = new;
		new->next = g_cameras;
	}
}

void	to_next_number(char **str)
{
	while (ft_isdigit(**str) || **str == '-')
		(*str)++;
	while (!ft_isdigit(**str) && **str != '-')
		(*str)++;
}
