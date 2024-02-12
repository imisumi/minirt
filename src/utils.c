/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:03:04 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/12 16:48:52 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// extern uint32_t	global_frame;

void put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	if (x >= 0 && x < image->width && y >= 0 && y < image->height)
		mlx_put_pixel(image, x, y, color);
}

float random_float(uint32_t *state)
{
	*state = *state * 747796405 + 2891336453;
	uint32_t result = ((*state >> ((*state >> 28) + 4)) ^ *state) * 277803737;
	result = (result >> 22) ^ result;
	return (float)result / 4294967295.0f;
}

t_vec2f	random_point_in_circle_f(uint32_t *state)
{
	float angle = random_float(state) * TWO_PI;
	// t_vec2 point_on_circle = vec2_new(cosf(angle), sinf(angle));
	// t_vec2 point_on_circle = (t_vec2){cosf(angle), sinf(angle)};
	// return (vec2_mulf(point_on_circle, sqrtf(random_float(state))));
	t_vec2f point_on_circle_f = {cosf(angle), sinf(angle)};
	return point_on_circle_f * sqrtf(random_float(state));
}


float random_value_normal_distribution(uint32_t *state)
{
	float theta = TWO_PI * random_float(state);
	float rand_float = random_float(state);
	//! avoid NaN
	while (rand_float <= EPSILON)
		rand_float = random_float(state);
	// float rho = sqrtf(-2 * logf(random_float(state)));
	float rho = sqrtf(-2 * logf(rand_float));
	return rho * cosf(theta);
}

t_vec3f random_directionf(uint32_t *state)
{
	float x = random_value_normal_distribution(state);
	float y = random_value_normal_distribution(state);
	float z = random_value_normal_distribution(state);
	// return vec3_normalize(vec3_new(x, y, z));
	// return vec3_normalize((t_vec3){x, y, z});
	return (vec3f_normalize((t_vec3f){x, y, z, 0.0f}));
}

double	time_delta(double prev_frame)
{
	double	current_time;
	double	delta_time;

	current_time = glfwGetTime();
	delta_time = current_time - prev_frame;
	return (delta_time);
}

uint32_t	get_rngstate(uint32_t width, uint32_t height, uint32_t xy[2], uint32_t frame)
{
	t_vec2f		coord;
	t_vec2f		num_pixels;
	uint32_t	pixel_index;

	coord = (t_vec2f){(float)xy[X] / (float)(width), (float)xy[Y] / (float)(height)};
	num_pixels = (t_vec2f){(float)width, (float)height};
	coord = coord * num_pixels;
	pixel_index = coord[X] + coord[Y] * num_pixels[X];
	return (pixel_index + frame * 719393);
}
