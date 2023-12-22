/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:03:04 by ichiro            #+#    #+#             */
/*   Updated: 2023/12/18 23:52:01 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

extern uint32_t	global_frame;

void put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	if (x >= 0 && x < image->width && y >= 0 && y < image->height)
		mlx_put_pixel(image, x, y, color);
}

float randomFloat(uint32_t *state)
{
	*state = *state * 747796405 + 2891336453;
	uint32_t result = ((*state >> ((*state >> 28) + 4)) ^ *state) * 277803737;
	result = (result >> 22) ^ result;
	return (float)result / 4294967295.0f;
}

t_vec2	random_point_in_circle(uint32_t *state)
{
	float angle = randomFloat(state) * TWO_PI;
	// t_vec2 point_on_circle = vec2_new(cosf(angle), sinf(angle));
	t_vec2 point_on_circle = (t_vec2){cosf(angle), sinf(angle)};
	return (vec2_mulf(point_on_circle, sqrtf(randomFloat(state))));
}

t_vec2f	random_point_in_circle_f(uint32_t *state)
{
	float angle = randomFloat(state) * TWO_PI;
	// t_vec2 point_on_circle = vec2_new(cosf(angle), sinf(angle));
	// t_vec2 point_on_circle = (t_vec2){cosf(angle), sinf(angle)};
	// return (vec2_mulf(point_on_circle, sqrtf(randomFloat(state))));
	t_vec2f point_on_circle_f = {cosf(angle), sinf(angle)};
	return point_on_circle_f * sqrtf(randomFloat(state));
}


int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t vec4_to_color(t_vec4 c)
{
	uint8_t r = (uint8_t)(c.x * 255.0);
	uint8_t g = (uint8_t)(c.y * 255.0);
	uint8_t b = (uint8_t)(c.z * 255.0);
	uint8_t a = (uint8_t)(c.w * 255.0);
	return (ft_pixel(r, g, b, a));
}

uint32_t vec4f_to_color(t_vec4f c)
{
	uint8_t r = (uint8_t)(c[X] * 255.0);
	uint8_t g = (uint8_t)(c[Y] * 255.0);
	uint8_t b = (uint8_t)(c[Z] * 255.0);
	// uint8_t a = (uint8_t)(c[] * 255.0);
	uint8_t a = 255;
	return (ft_pixel(r, g, b, a));
}


float random_value_normal_distribution(uint32_t *state)
{
	float theta = TWO_PI * randomFloat(state);
	float random_float = randomFloat(state);
	//! avoid NaN
	while (random_float <= EPSILON)
		random_float = randomFloat(state);
	// float rho = sqrtf(-2 * logf(randomFloat(state)));
	float rho = sqrtf(-2 * logf(random_float));
	return rho * cosf(theta);
}

t_vec3 random_direction(uint32_t *state)
{
	float x = random_value_normal_distribution(state);
	float y = random_value_normal_distribution(state);
	float z = random_value_normal_distribution(state);
	// return vec3_normalize(vec3_new(x, y, z));
	return vec3_normalize((t_vec3){x, y, z});
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

uint32_t	get_rngstate(uint32_t width, uint32_t height, uint32_t x, uint32_t y)
{
	t_vec2		coord;
	t_vec2		num_pixels;
	uint32_t	pixel_index;

	coord = (t_vec2){(float)x / (float)(width), (float)y / (float)(height)};
	num_pixels = (t_vec2){(float)width, (float)height};
	coord = vec2_mul(coord, num_pixels);
	pixel_index = coord.x + coord.y * num_pixels.x;
	return (pixel_index + global_frame * 719393);
}
