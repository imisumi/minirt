/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/07 12:25:22 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../lib/MLX42/include/MLX42/MLX42.h"

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>

// typedef struct s_ray
// {
// 	t_vec3 a;
// 	t_vec3 b;
// } t_ray;

// typedef struct s_vec2
// {
// 	float	x;
// 	float	y;
// }	t_vec2;

// typedef struct s_vec3
// {
// 	float	x;
// 	float	y;
// 	float	z;
// }	t_vec3;

typedef struct s_fdf
{
	mlx_t		*mlx;
	mlx_image_t	*image;
}	t_fdf;

#endif