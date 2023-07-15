/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/07/15 17:14:37 by imisumi          ###   ########.fr       */
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

#include <GLFW/glfw3.h>

// # include "../lib/cglm/build/include/cglm/cglm.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/includes/libft.h"
# include "../lib/ft_math/includes/math.h"

// # define STB_IMAGE_IMPLEMENTATION
// # include "../lib/stb/stb_image.h"


#include "scene.h"
// # include "hitable.h"

# define WIDTH 400
# define HEIGHT 300
# define PIXEL_SIZE 4

// # define WIDTH 300
// # define HEIGHT 100
// # define PIXEL_SIZE 4

// # define WIDTH 1024
// # define HEIGHT 1024
// # define PIXEL_SIZE 1


// # define WIDTH 200
// # define HEIGHT 200
// # define PIXEL_SIZE 6

// # define WIDTH 512
// # define HEIGHT 512
// # define PIXEL_SIZE 2




uint32_t total_frames;
t_vec4 *accumulated_data;
uint32_t accumulated_frames;




//! utils.c
uint32_t ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
float clamp(float value, float min, float max);
float randomFloat(uint32_t *state);
t_sphere create_sphere(t_vec3 center, float radius);

uint32_t vec4_to_color(t_vec4 c);

t_vec3 hit_position(t_ray r, float t);

float my_sign(float num);

float random_value_normal_distribution(uint32_t *state);

t_vec3 random_direction(uint32_t *state);

t_vec3 random_himisphere_dir(t_vec3 normal, uint32_t *state);


t_obj_hit plane_intersection(t_ray ray, t_scene s, t_obj_hit obj_hit);
t_obj_hit sphere_intersection(t_ray ray, t_scene s, t_obj_hit obj_hit);


//! camera.c
void recalculat_ray_directions(t_mlx *d);

void recalculate_view(t_mlx *d);
void recalculated_projection(t_mlx *d);
void	movement(t_mlx *d);

void init_camera(t_camera *cam);

#endif
