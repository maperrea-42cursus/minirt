/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 19:45:22 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/30 10:32:03 by maperrea         ###   ########.fr       */
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

typedef					int (t_parse)(char *line);
typedef					int (t_check)(char *line, int line_nbr);

typedef struct s_lookup_table
{
	char				*key;
	void				*value;
}						t_lookup_table;

typedef struct s_mlx_data
{
	void				*mlx_ptr;
	void				*win_ptr;
}						t_mlx_data;

typedef struct s_mlx_image
{
	void				*image;
	int					*image_data;
	int					bpp;
	int					ppl;
	int					size_line;
	int					endian;
}						t_mlx_image;

typedef struct s_vec2
{
	int					x;
	int					y;
}						t_vec2;

typedef struct s_vec3
{
	int					x;
	int					y;
	int					z;
}						t_vec3;

typedef struct s_fvec2
{
	double				x;
	double				y;
}						t_fvec2;

typedef struct s_fvec3
{
	double				x;
	double				y;
	double				z;
}						t_fvec3;

typedef struct s_line3
{
	t_fvec3				orig;
	t_fvec3				dest;
}						t_line3;

typedef struct s_range
{
	int					min;
	int					max;
}						t_range;

typedef struct s_frange
{
	double				min;
	double				max;
}						t_frange;

typedef struct s_vec3_range
{
	t_vec3				min;
	t_vec3				max;
}						t_vec3_range;

typedef struct s_fvec3_range
{
	t_fvec3				min;
	t_fvec3				max;
}						t_fvec3_range;

typedef union u_args_data
{
	t_range				irange;
	t_frange			frange;
	t_vec3_range		vrange;
	t_fvec3_range		fvrange;
}						t_args_data;

typedef struct s_args
{
	int					flag;
	t_args_data			data;
}						t_args;

typedef					int (t_checker)(char **line, t_args args);

typedef struct s_grid
{
	double				step;
	t_fvec3				start;
	t_fvec3				end;
	t_fvec3				i;
	t_fvec3				j;
	t_vec2				size;
}						t_grid;

typedef struct s_camera
{
	t_fvec3				pos;
	t_fvec3				orientation;
	double				fov;
}						t_camera;

typedef struct s_cameras
{
	void				*camera;
	t_mlx_image			*img;
	struct s_cameras	*next;
	struct s_cameras	*previous;
}						t_cameras;

typedef union u_extra
{
	t_line3				normal;
}						t_extra;

typedef					t_fvec3 *(t_get_intersection)(t_line3 ray,
							void *object, t_extra *extra);
typedef					int (t_get_color)(t_fvec3 intersection,
							void *object, t_extra *extra);

typedef struct s_sphere
{
	t_fvec3				pos;
	double				radius;
	int					color;
}						t_sphere;

typedef struct s_cylinder
{
	t_fvec3				pos;
	t_fvec3				axis;
	double				radius;
	double				height;
	int					color;
}						t_cylinder;

typedef struct s_cy_data
{
	t_fvec3		w;
	double		dist;
	t_fvec3		i;
	t_fvec3		j;
	t_fvec3		*result1;
	t_fvec3		*result2;
	t_line3		line1;
	t_line3		line2;
}						t_cy_data;

typedef struct s_plane
{
	t_fvec3				pos;
	t_fvec3				normal;
	int					color;
}						t_plane;

typedef struct s_objects
{
	void				*object;
	t_get_intersection	*get_intersection;
	t_get_color			*get_color;
	struct s_objects	*next;
}						t_objects;

typedef					int (t_get_luminosity)(void* light);
typedef					t_fvec3 (t_get_pos)(void *light);

typedef struct s_spherical_light
{
	t_fvec3				pos;
	double				power;
	int					color;
}						t_spherical_light;

typedef struct s_lights
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
double					g_light_factor;

t_objects				*is_closer_intersection(t_line3 ray, t_objects *objs,
							t_fvec3 **closest_intersection, t_extra *extra);
t_objects				*get_closest_obj(t_line3 ray,
							t_fvec3 *out_intersection,
							void *exclude, t_extra *extra);
void					cast_rays(t_mlx_image *img, t_grid grid, t_camera *cam);

void					get_image(t_mlx_image *img, t_camera *cam);
void					init_cam(t_mlx_data *mlx);

void					add_object(void *object,
							t_get_intersection *intersection,
							t_get_color *color);
void					add_light(void *light, t_get_luminosity *luminosity,
							t_get_pos *pos);
void					add_camera(void *camera);
void					to_next_number(char **str);
int						next_int(char **str);
double					next_float(char **str);
t_vec3					next_vec3(char **str);
t_fvec3					next_fvec3(char **str);
int						next_color(char **str);
int						parse_f(char *line);
int						parse_c(char *line);
int						parse_l(char *line);
int						parse_sp(char *line);
int						parse_pl(char *line);
int						parse_r(char *line);
int						parse_a(char *line);
int						parse_cy(char *line);
void					parse_map(char *filename);

void					error_exit(const char *str);
int						skip_spaces(char **str);
int						check_int(char **str, t_args range);
int						check_float(char **str, t_args data);
int						check_vec3(char **str, t_args data);
int						check_fvec3(char **str, t_args data);
int						check_color(char **str, t_args data);
int						line_checker(char *line, t_checker **checkers,
							t_args *args);
int						required_params(int res, int light, int cam);
int						check_r(char *line, int line_nbr);
int						check_a(char *line, int line_nbr);
int						check_f(char *line, int line_nbr);
int						check_c(char *line, int line_nbr);
int						check_l(char *line, int line_nbr);
int						check_sp(char *line, int line_nbr);
int						check_pl(char *line, int line_nbr);
int						check_cy(char *line, int line_nbr);
void					check_map(char **file);

t_objects				*get_closest_obj(t_line3 ray,
							t_fvec3 *out_intersection,
							void *exclude, t_extra *extra);

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

int						color_multiply(int color, double factor);
int						color_reflect(int a, int b);
int						color_add(int a, int b);
int						get_light_color(t_lights *lights,
							t_fvec3 intersection, double angle);
int						get_illumination(t_fvec3 intersection, void *object,
							t_line3 normal, t_lights *lights);

double					*resolve_second_degree(double a, double b, double c);

t_fvec3					*sphere_intersection(t_line3 ray, void *sphere,
							t_extra *extra);
int						sphere_color(t_fvec3 intersection,
							void *sphere, t_extra *extra);

t_fvec3					*cylinder_intersection(t_line3 ray, void *cylinder,
							t_extra *extra);
int						cylinder_color(t_fvec3 intersection,
							void *cylinder, t_extra *extra);

t_fvec3					*plane_intersection(t_line3 ray, void *plane,
							t_extra *extra);
int						plane_color(t_fvec3 intersection,
							void *plane, t_extra *extra);

int						spherical_light_luminosity(void *light);
t_fvec3					spherical_light_pos(void *light);

int						exit_hook(void);
int						key_hook(int keycode, t_mlx_data *mlx);

#endif
