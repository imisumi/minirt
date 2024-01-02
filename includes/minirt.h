/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:31:38 by imisumi           #+#    #+#             */
/*   Updated: 2024/01/02 16:39:06 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <float.h>
# include "tinyexr.h"

# include <GLFW/glfw3.h>

#include "MLX42/MLX42.h"
#include "libft.h"
#include "lib3d.h"
#include "constants.h"
#include "struct.h"
#include "darray.h"


float		randomFloat(uint32_t *state);
t_vec2		random_point_in_circle(uint32_t *state);
uint32_t	vec4_to_color(t_vec4 c);
t_vec3		random_direction(uint32_t *state);
double		time_delta(double prev_frame);


//? hooks
void	ft_hook(void* param);
void	render_loop(void *param);
void	frame_times(void *param);


// void	render(void *param);

void	put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color);



//? camera
void	movement(t_data *data);
void	init_camera(t_camera *cam);
void	recalculate_view(t_data *d);
void	recalculated_projection(t_data *d);
void	recalculat_ray_directions(t_data *d);


float	aabb_intersection(t_ray ray, t_aabb aabb);



void	init_scene(t_scene *scene);


t_bvh_node	*build_bvh_sphere(t_sphere *spheres, uint32_t start, uint32_t end, uint32_t max_depth);



void	resize_window(void *param);




//? thread.c
bool	create_thread(t_data *data);

//? hook
void	*render(void *arg);





//! new
t_vec3f		random_directionf(uint32_t *state);
t_hitinfo	inv_plane_intersection_f(t_rayf ray, t_scene s, t_hitinfo hitinfo);
uint32_t	vec4f_to_color(t_vec4f c);
t_hitinfo	sphere_intersection_f(t_rayf ray, t_scene s, t_hitinfo hitinfo);
t_hitinfo	single_sphere_intersection_f(t_rayf ray, t_sphere sphere, t_hitinfo hitinfo);
uint32_t	get_rngstate(uint32_t width, uint32_t height, uint32_t x, uint32_t y);
t_bvh_node	*build_bvh_sphere_f(t_sphere *spheres, uint32_t start, uint32_t end, uint32_t max_depth);
t_aabb		calculate_sphere_aabb_f(t_sphere *spheres, uint32_t start, uint32_t end);
float		aabb_intersection_f(t_rayf ray, t_aabb aabb);
t_hitinfo	sphere_bvh_intersection_f(t_rayf ray, t_sphere *spheres, t_hitinfo hitinfo, t_bvh_node *node);
t_vec3f	aa_update_dir(t_data *data, uint32_t *rng, uint32_t x, uint32_t y);
t_vec4f	vec3f_tone_map(t_vec3f color);
t_vec3f	default_skyf(t_vec3f direction, t_scene scene);
t_vec3f omni_dir_light_f(t_rayf ray, t_scene scene, t_hitinfo closest_hit);


t_vec3f	texture(t_vec3f normal, t_hdri hdri);



void	screenshot(t_data *data);


#endif
