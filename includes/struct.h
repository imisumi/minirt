/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/25 21:16:49 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_mlx	t_mlx;

typedef struct s_mlx
{
	t_scene		scene;
	mlx_t		*mlx;
	mlx_image_t	*img;
}				t_mlx;



# endif