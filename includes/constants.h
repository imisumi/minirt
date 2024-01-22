/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 00:41:53 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/22 12:52:41 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define BONUS 1

// # define MT

# if BONUS
#  define MT 1
#  define PIXEL_SIZE 2
# else
#  define MT 0
#  define PIXEL_SIZE 2
# endif

# define WIDTH 500
# define HEIGHT 500

// # define PIXEL_SIZE 2

# define MAX_BOUNCES 8

// # define MT 1
# define THREADS 6

# define MAX_TRIS_LEAF 4
# define MAX_OBJS_MESH 1

# define RENDER_BVH 0
# define MAX_SPHERES_LEAF 4

# define RENDER_SKYBOX 1

# define BACK_FACE_CULLING 1

# define USE_BVH 1

# define AA 1

# define PI 3.14159265359
// # define PI 3.14159265358979323846264338327950288
// # define HALF_PI 1.57079632679489661923132169163975144
# define HALF_PI 1.57079632679
// # define TWO_PI 6.28318530718
# define TWO_PI 6.28318530718

# define EPSILON 0.00001f

#endif
