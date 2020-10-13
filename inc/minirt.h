/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 19:45:22 by maperrea          #+#    #+#             */
/*   Updated: 2020/10/13 21:18:00 by maperrea         ###   ########.fr       */
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

typedef struct			s_mlx_image
{
	void		*image;
	char		*image_data;
	int			bpp;
	int			ppl;
	int			size_line;
	int			endian;
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

typedef struct			s_camera
{
	t_fvec3				pos;
	t_fvec3				orientation;
	double				fov;
}						t_camera;

typedef struct			s_cameras
{
	void				*cameras;
	struct s_cameras	*next;
}						t_cameras;

typedef t_fvec3			(t_get_intersection)(t_fvec3 orig, t_fvec3 dir,
															void *object);
typedef struct			s_sphere
{
	t_fvec3				pos;
	double				radius;
	int					color;
	t_get_intersection	*get_intersection;
}						t_sphere;

typedef struct			s_objects
{
	void				*object;
	struct s_objects	*next;
}						t_objects;

typedef double			(t_get_luminosity)(t_fvec3 pos, void* light); 

typedef struct			s_light
{
	t_fvec3				pos;
	double 				power;
	int					color;
	t_get_luminosity	*get_luminosity;
}						t_light;

typedef struct			s_lights
{
	void				*light;
	struct s_lights		*next;
}						t_lights;

t_objects				*g_objects;
t_lights				*g_lights;
t_camera				*cameras
t_vec3					resolution;
t_light					ambient_lightning;

int						parse_map(char *filename);

t_fvec3					fvec3_div(t_fvec3 vec, double div);
double					fvec3_length(t_fvec3 vec);
t_fvec3					fvec3_normalize(t_fvec3 vec);
t_fvec3					fvec3_product(t_fvec3 a, t_fvec3 b);
//t_fvec3					fvec3_rotate(t_fvec3 vec, t_fvec3 axis, double angle);

#endif
