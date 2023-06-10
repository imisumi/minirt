/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/09 18:13:16 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../lib/MLX42/include/MLX42/MLX42.h"

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_rgb
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} t_rgb;

typedef struct s_rgba
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} t_rgba;


typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec4;

typedef struct s_quat
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_quat;

typedef struct s_ray
{
	t_vec3 a;
	t_vec3 b;
} t_ray;

typedef struct s_mat4
{
	float	m[4][4];
}	t_mat4;

typedef struct s_camera
{
	t_mat4 projection;
	t_mat4 view;
	t_mat4 inv_projection;
	t_mat4 inv_view;
	
	float vertical_fov;
	float near_clip;
	float far_clip;

	float rotation_speed;
	
	t_vec3 pos;
	t_vec3 for_dir;
	
}	t_camera;

typedef struct s_mouse
{
	int	x;
	int	y;
	int x_prev;
	int y_prev;
	mouse_key_t	button;
	action_t	action;
	modifier_key_t	mods;
}	t_mouse;

typedef struct s_fdf
{
	t_mouse		mouse;
	
	t_camera	camera;

	mlx_t		*mlx;
	mlx_image_t	*image;
}	t_fdf;

void	set_mouse_param(mouse_key_t button, action_t action, modifier_key_t mods, void *param);
t_mat4	fill_mat4(t_mat4 m, float f);
t_mat4	create_mat4(float f);

#endif