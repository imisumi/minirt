/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/05/23 16:19:05 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../lib/MLX42/include/MLX42/MLX42.h"

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_picker
{
	int	i;
	int	j;
	int	size;
	int	spacing;
	int	x_start;
	int	y_start;
	int	border;
	int	outline;
}	t_picker;

typedef struct s_rect
{
	int			x;
	int			y;
	int			width;
	int			height;
	bool		active;
	uint32_t	color;
}	t_rect;

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

typedef struct s_line
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	y1_c;
	int	y2_c;
}	t_line;

typedef struct s_rgb
{
	int			rgba[4];
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
	uint32_t	color;
}	t_rgb;

typedef struct s_draw
{
	int	z;
	int	z1;
	int	delta_x;
	int	delta_y;
	int	sign_x;
	int	sign_y;
	int	err;
	int	e2;
}	t_draw;

typedef struct s_move
{
	float	x;
	float	y;
	float	z;
}	t_move;

typedef struct s_fdf
{
	int			button;
	int			width;
	int			height;
	float		angle;

	int			**map;
	uint32_t	**map_colors;
	bool		color_switch;

	t_vec3		rotation;
	t_vec2		**projected_point;
	t_vec3		**transformed_map;
	t_vec2		**projected_points;
	t_vec3		**grid;
	t_vec3		camera;
	t_vec3		origin;
	float		scale;
	float		flatten;

	t_rgb		*y_color;

	t_rect		menu;
	t_rect		menu_button[32];
	t_rect		color_picker[17];

	bool		perspective;
	bool		parallel;
	bool		isometric;

	mlx_t		*mlx;
	mlx_image_t	*image;
}	t_fdf;

#endif