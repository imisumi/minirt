/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:03:04 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/04 16:22:14 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

uint32_t ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}


uint32_t	vec4f_to_color(t_vec4f c)
{
	const uint32_t color = ft_pixel(
		(uint8_t)(c[X] * 255.0),
		(uint8_t)(c[Y] * 255.0),
		(uint8_t)(c[Z] * 255.0),
		255);

	return (color);
}


t_vec3f LinearToSRGB(t_vec3f rgb)
{
	rgb = vec4f_clamp(rgb, 0.0f, 1.0f);

	t_vec3f condition = {0.0031308f, 0.0031308f, 0.0031308f};
	t_vec3f pow_result = vec3f_pow(rgb, 1.0f / 2.4f);

	t_vec3f mix_result = mix_vec4f(
		pow_result * 1.055f - 0.055f,
		rgb * 12.92f,
		LessThan_vec4f(rgb, condition)
	);

	return mix_result;
}

t_vec4f	ACESFilm(t_vec4f x)
{
	float a = 2.51f;
	float b = 0.03f;
	float c = 2.43f;
	float d = 0.59f;
	float e = 0.14f;

	t_vec4f numerator = {x[X] * (a * x[X] + b), x[Y] * (a * x[Y] + b), x[Z] * (a * x[Z] + b), x[W] * (a * x[W] + b)};
	t_vec4f denominator = {x[X] * (c * x[X] + d) + e, x[Y] * (c * x[Y] + d) + e, x[Z] * (c * x[Z] + d) + e, x[W] * (c * x[W] + d) + e};

	t_vec4f result;
	result[X] = numerator[X] / denominator[X];
	result[Y] = numerator[Y] / denominator[Y];
	result[Z] = numerator[Z] / denominator[Z];
	result[W] = numerator[W] / denominator[W];

	// Clamp the result to the range [0.0, 1.0]
	result[X] = fmax(0.0f, fmin(1.0f, result[X]));
	result[Y] = fmax(0.0f, fmin(1.0f, result[Y]));
	result[Z] = fmax(0.0f, fmin(1.0f, result[Z]));
	result[W] = fmax(0.0f, fmin(1.0f, result[W]));

	result[W] = 1.0f;

	return result;
}

t_vec4f	vec3f_tone_map(t_vec3f color)
{
	color = ACESFilm(color);
	color = LinearToSRGB(color);
	color[W] = 1.0f;
	return color;
	float	gamma = 2.2f;
	float	exposure = 1.0f;
	color = color * exposure;
	t_vec3f	result = color / (color + 1.0f);

	result[X] = powf(result[X], 1.0f / gamma);
	result[Y] = powf(result[Y], 1.0f / gamma);
	result[Z] = powf(result[Z], 1.0f / gamma);
	return((t_vec4f){result[X], result[Y], result[Z], 1.0f});
}