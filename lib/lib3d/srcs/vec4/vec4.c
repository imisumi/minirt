/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/04/22 13:46:58 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

float	vec4f_length(t_vec4f v)
{
	return (sqrtf(v[X] * v[X] + v[Y] * v[Y] + v[Z] * v[Z] + v[W] * v[W]));
}

t_vec4f	vec4f_normalize(t_vec4f v)
{
	const float	length = vec4f_length(v);
	float		inv_length;

	if (length > 0.0f)
	{
		inv_length = 1.0f / length;
		v[X] *= inv_length;
		v[Y] *= inv_length;
		v[Z] *= inv_length;
		v[W] *= inv_length;
	}
	return (v);
}

t_vec4f	vec4f_clamp(t_vec4f vec, float min, float max)
{
	vec[X] = fmaxf(min, fminf(max, vec[X]));
	vec[Y] = fmaxf(min, fminf(max, vec[Y]));
	vec[Z] = fmaxf(min, fminf(max, vec[Z]));
	vec[W] = fmaxf(min, fminf(max, vec[W]));
	return (vec);
}

// t_vec4f	vec4f_less_than(t_vec4f v, t_vec4f threshold)
// {
// 	t_vec4f	result;

// 	result[X] = v[X] < threshold[X] ? 1.0f : 0.0f;
// 	result[Y] = v[Y] < threshold[Y] ? 1.0f : 0.0f;
// 	result[Z] = v[Z] < threshold[Z] ? 1.0f : 0.0f;
// 	result[W] = v[W] < threshold[W] ? 1.0f : 0.0f;
// 	return (result);
// }

t_vec4f	vec4f_less_than(t_vec4f v, t_vec4f threshold)
{
	t_vec4f	result;

	if (v[X] < threshold[X])
		result[X] = 1.0f;
	else
		result[X] = 0.0f;
	if (v[Y] < threshold[Y])
		result[Y] = 1.0f;
	else
		result[Y] = 0.0f;
	if (v[Z] < threshold[Z])
		result[Z] = 1.0f;
	else
		result[Z] = 0.0f;
	if (v[W] < threshold[W])
		result[W] = 1.0f;
	else
		result[W] = 0.0f;
	return (result);
}

t_vec4f	mix_vec4f(t_vec4f x, t_vec4f y, t_vec4f mask)
{
	const t_vec4f	result = {
		mask[X] * y[X] + (1.0f - mask[X]) * x[X],
		mask[Y] * y[Y] + (1.0f - mask[Y]) * x[Y],
		mask[Z] * y[Z] + (1.0f - mask[Z]) * x[Z],
		mask[W] * y[W] + (1.0f - mask[W]) * x[W]};

	return (result);
}
