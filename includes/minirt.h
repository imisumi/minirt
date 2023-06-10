/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/09 17:00:22 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/includes/libft.h"

# include "struct.h"
# include "colors.h"
# include "vec.h"
# include "utils.h"
# include "camera.h"

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <memory.h>
# include <math.h>
# include <stdbool.h>
# include <limits.h>
# include <ctype.h>
# include <stdint.h>

# define PI 3.14159265
# define WIDTH 1000
# define HEIGHT 1000
# define ASPECT_RATIO (float)WIDTH / (float)HEIGHT

typedef struct s_coord
{
	float	x;
	float	y;
} t_coord;

void	key_hook(mlx_key_data_t key, void *param);

#endif
