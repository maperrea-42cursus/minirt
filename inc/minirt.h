/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 19:45:22 by maperrea          #+#    #+#             */
/*   Updated: 2020/10/08 22:44:54 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include "mlx.h"

# define WINW 960
# define WINH 540

typedef struct			s_mlx_image
{
	void		*image;
	char		*image_data;
	int			bpp;
	int			size_line;
	int			endian;
}						t_mlx_image;

typedef struct			s_vec2
{
	int			x;
	int			y;
}						t_vec2;

typedef struct			s_vec3
{
	int 		x;
	int 		y;
	int 		z;
}						t_vec3;

typedef struct			s_fvec2
{
	double		x;
	double		y;
}						t_fvec2;

typedef struct			s_fvec3
{
	double		x;
	double		y;
	double		z;
}						t_fvec3;

typedef struct			s_sphere
{
	t_vec3		pos;
	int			radius;
}						t_sphere;

#endif
