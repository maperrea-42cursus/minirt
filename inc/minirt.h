/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 19:45:22 by maperrea          #+#    #+#             */
/*   Updated: 2020/12/01 18:35:43 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

typedef int				(t_parse)(char *line);

typedef struct			s_lookup_table
{
	char				*key;
	t_parse				*value;
}						t_lookup_table;

typedef struct			s_mlx_image
{
	void				*image;
	int					*image_data;
	int					bpp;
	int					ppl;
	int					size_line;
	int					endian;
}						t_mlx_image;

typedef struct			s_vec2
{
	int					x;
	int					y;
}						t_vec2;

typedef struct			s_vec3
{
	int 				x;
	int 				y;
	int 				z;
}						t_vec3;

typedef struct			s_fvec2
{
	double				x;
	double				y;
}						t_fvec2;

typedef struct			s_fvec3
{
	double				x;
	double				y;
	double				z;
}						t_fvec3;

typedef struct			s_line3
{
	t_fvec3				orig;
	t_fvec3				dest;
}						t_line3;

typedef struct			s_grid
{
	double				step;
	t_fvec3				start;
	t_fvec3				end;
	t_fvec3				i;
	t_fvec3				j;
	t_vec2				size;
}						t_grid;

typedef struct			s_camera
{
	t_fvec3				pos;
	t_fvec3				orientation;
	double				fov;
}						t_camera;

typedef struct			s_cameras
{
	void				*camera;
	struct s_cameras	*next;
}						t_cameras;

typedef t_fvec3			*(t_get_intersection)(t_line3 ray, void *object);
typedef int				(t_get_color)(t_line3 ray,
							t_fvec3 intersection, void *object);

typedef struct			s_sphere
{
	t_fvec3				pos;
	double				radius;
	int					color;
}						t_sphere;

typedef struct			s_cylinder
{
	t_fvec3				pos;
	t_fvec3				axis;
	double				radius;
	double				height;
	int					color;
}						t_cylinder;

typedef struct			s_objects
{
	void				*object;
	t_get_intersection	*get_intersection;
	t_get_color			*get_color;
	struct s_objects	*next;
}						t_objects;

typedef int				(t_get_luminosity)(void* light); 
typedef t_fvec3			(t_get_pos)(void *light);

typedef struct			s_spherical_light
{
	t_fvec3				pos;
	double 				power;
	int					color;
}						t_spherical_light;

typedef struct			s_lights
{
	void				*light;
	t_get_luminosity	*get_luminosity;
	t_get_pos			*get_pos;
	struct s_lights		*next;
}						t_lights;

t_objects				*g_objects;
t_lights				*g_lights;
t_cameras				*g_cameras;
t_vec2					g_resolution;
t_spherical_light		g_ambient_light;
//should really make a new ambient light type

int						parse_map(char *filename);

t_objects				*get_closest_obj(t_line3 ray,
							t_fvec3 *out_intersection, void *exclude);

t_fvec3					fvec3_add(t_fvec3 a, t_fvec3 b);
t_fvec3					fvec3_sub(t_fvec3 a, t_fvec3 b);
t_fvec3					fvec3_div(t_fvec3 vec, double div);
double					fvec3_length(t_fvec3 vec);
t_fvec3					fvec3_normalize(t_fvec3 vec);
t_fvec3					fvec3_product(t_fvec3 a, t_fvec3 b);
t_fvec3					fvec3_scalar_mult(t_fvec3 v, double x);
double					fvec3_dot_product(t_fvec3 a, t_fvec3 b);
double					fvec3_angle(t_fvec3 a, t_fvec3 b);
int						is_in_front(t_line3 normal, t_fvec3 vec);
int						is_closer(t_fvec3 a, t_fvec3 b);
t_line3					line_from_points(t_fvec3 a, t_fvec3 b);
t_fvec3					*line_intersection(t_line3 a, t_line3 b);
//t_fvec3					fvec3_rotate(t_fvec3 vec, t_fvec3 axis, double angle);

int						color_multiply(int color, double factor);
int						color_reflect(int a, int b);
int						color_add(int a, int b);

double					*resolve_second_degree(double a, double b, double c);

t_fvec3					*sphere_intersection(t_line3 ray, void *sphere);
int						sphere_color(t_line3 ray,
							t_fvec3 intersection, void *sphere);

t_fvec3					*cylinder_intersection(t_line3 ray, void *cylinder);
int						cylinder_color(t_line3 ray,
							t_fvec3 intersection, void *cylinder);

int						spherical_light_luminosity(void *light);
t_fvec3					spherical_light_pos(void *light);

int						exit_hook();

#endif
