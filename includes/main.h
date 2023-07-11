/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/07/10 23:09:02 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <math.h>

// # include "../lib/cglm/build/include/cglm/cglm.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/includes/libft.h"
# include "../lib/ft_math/includes/math.h"
# define STB_IMAGE_IMPLEMENTATION
# include "../lib/stb/stb_image.h"

#include "struct.h"

#include "scene.h"
# include "hitable.h"
# include "camera.h"

// # define WIDTH 300
// # define HEIGHT 200
// # define PIXEL_SIZE 5

# define WIDTH 800
# define HEIGHT 600
# define PIXEL_SIZE 1

// # define WIDTH 1024
// # define HEIGHT 512
// # define PIXEL_SIZE 1


// typedef struct s_mlx
// {
// 	t_scene		scene;
// 	mlx_t		*mlx;
// 	mlx_image_t	*img;
// }				t_mlx;

// void recalculate_view(t_mlx *d);
// void recalculated_projection(t_mlx *d);
// void recalculat_ray_directions(t_mlx *d);
// void	movement(t_mlx *d);


#endif
