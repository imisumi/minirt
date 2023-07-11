/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/07/11 03:06:37 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scene.h"

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <unistd.h>
# include <string.h>

uint32_t ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

float clamp(float value, float min, float max)
{
    // Helper function to clamp a value within a specific range
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return value;
    }
}

float randomFloat(uint32_t *state)
{
	*state = *state * 747796405 + 2891336453;
	uint32_t result = ((*state >> ((*state >> 28) + 4)) ^ *state) * 277803737;
	result = (result >> 22) ^ result;
	return (float)result / 4294967295.0f;
}

t_sphere create_sphere(t_vec3 center, float radius)
{
	t_sphere s;

	s.center = center;
	s.radius = radius;
	return (s);
}

uint32_t vec4_to_color(t_vec4 c)
{
	uint8_t r = (uint8_t)(c.x * 255.0);
	uint8_t g = (uint8_t)(c.y * 255.0);
	uint8_t b = (uint8_t)(c.z * 255.0);
	uint8_t a = (uint8_t)(c.w * 255.0);
	return (ft_pixel(r, g, b, a));
}

t_vec3 point_at_parameter(t_ray r, float t)
{
	t_vec3 res;

	res = vec3_add(r.origin, vec3_mul_float(r.direction, t));
	return (res);
}

float my_sign(float num) {
    if (num > 0.0f) {
        return 1.0f;
    } else if (num < 0.0f) {
        return -1.0f;
    } else {
        return 0.0f;
    }
}

float random_value_normal_distribution(uint32_t *state)
{
	float theta = 2 * 3.1415926 * randomFloat(state);
	float rho = sqrtf(-2 * logf(randomFloat(state)));
	return rho * cosf(theta);
}

t_vec3 random_direction(uint32_t *state)
{
	float x = random_value_normal_distribution(state);
	float y = random_value_normal_distribution(state);
	float z = random_value_normal_distribution(state);
	return vec3_normalize(vec3_create(x, y, z));
	
}

t_vec3 random_himisphere_dir(t_vec3 normal, uint32_t *state)
{
	// t_vec3 dir;
	// dir.x = randomFloat(state);
	// dir.y = randomFloat(state);
	// dir.z = randomFloat(state);
	// float dot = vec3_dot(dir, normal);
	// dot = my_sign(dot);
	// if (dot < 0.0f)
	// 	dir = vec3_mul_float(dir, -1.0f);
	// return dir;
	// return vec3_mul_float(dir, my_sign(vec3_dot(normal, dir)));


	t_vec3 dir;
	dir = random_direction(state);

	return vec3_mul_float(dir, my_sign(vec3_dot(normal, dir)));
}