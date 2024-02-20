/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tone_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:03:04 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/20 14:57:46 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec4f	aces_film(t_vec4f x)
{
	const t_aces	a = {2.51f, 0.03f, 2.43f, 0.59f, 0.14f};
	const t_vec4f	numerator = {x[X] * (a.a * x[X] + a.b), \
								x[Y] * (a.a * x[Y] + a.b), \
								x[Z] * (a.a * x[Z] + a.b), \
								x[W] * (a.a * x[W] + a.b)};
	const t_vec4f	denominator = {x[X] * (a.c * x[X] + a.d) + a.e, \
									x[Y] * (a.c * x[Y] + a.d) + a.e, \
									x[Z] * (a.c * x[Z] + a.d) + a.e, \
									x[W] * (a.c * x[W] + a.d) + a.e};
	t_vec4f			result;

	result[X] = numerator[X] / denominator[X];
	result[Y] = numerator[Y] / denominator[Y];
	result[Z] = numerator[Z] / denominator[Z];
	result[W] = numerator[W] / denominator[W];
	result = vec4f_clamp(result, 0.0f, 1.0f);
	result[W] = 1.0f;
	return (result);
}

static t_vec3f	linear_to_srgb(t_vec3f rgb)
{
	t_vec3f			pow_result;
	t_vec3f			mix_result;
	const t_vec3f	condition = {0.0031308f, 0.0031308f, 0.0031308f};

	rgb = vec4f_clamp(rgb, 0.0f, 1.0f);
	pow_result = vec3f_pow(rgb, 1.0f / 2.4f);
	mix_result = mix_vec4f(\
		pow_result * 1.055f - 0.055f, \
		rgb * 12.92f, \
		vec4f_less_than(rgb, condition));
	return (mix_result);
}

t_vec4f	vec3f_tone_map(t_vec3f color)
{
	color = linear_to_srgb(aces_film(color));
	color[W] = 1.0f;
	return (color);
}
