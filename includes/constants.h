/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 00:41:53 by ichiro            #+#    #+#             */
/*   Updated: 2024/06/03 12:04:58 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define BONUS 1

# if BONUS == 0
#  define MT 0
#  define PIXEL_SIZE 1
#  define USE_BVH 0
# else
#  define MT 1
#  define PIXEL_SIZE 1
#  define USE_BVH 1
# endif

# define WIDTH 1024
# define HEIGHT 1024

# define SCREEN_SHOT 0

# define MAX_BOUNCES 8

# define THREADS 10

# define MAX_TRIS_LEAF 4
# define MAX_OBJS_MESH 1

# define RENDER_BVH 0
# define MAX_SPHERES_LEAF 4

# define RENDER_SKYBOX 1

# define BACK_FACE_CULL 1

# define AA 1

# define PI 3.14159265359
# define HALF_PI 1.57079632679
# define TWO_PI 6.28318530718

# define EPSILON 0.00001f

#endif
