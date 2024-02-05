/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/04 16:21:37 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

float	vec4f_length(t_vec4f v)
{
	return sqrtf(v[X] * v[X] + v[Y] * v[Y] + v[Z] * v[Z] + v[W] * v[W]);
}

t_vec4f vec4f_normalize(t_vec4f v)
{
	float length = vec4f_length(v);
	if (length > 0.0f) {
		float invLength = 1.0f / length;
		v[X] *= invLength;
		v[Y] *= invLength;
		v[Z] *= invLength;
		v[W] *= invLength;
	}
	return v;
}

t_vec4f	vec4f_clamp(t_vec4f vec, float min, float max)
{
	vec[X] = fmaxf(min, fminf(max, vec[X]));
	vec[Y] = fmaxf(min, fminf(max, vec[Y]));
	vec[Z] = fmaxf(min, fminf(max, vec[Z]));
	vec[W] = fmaxf(min, fminf(max, vec[W]));
	return (vec);
}

t_vec4f LessThan_vec4f(t_vec4f v, t_vec4f threshold)
{
	t_vec4f result;

	result[X] = v[X] < threshold[X] ? 1.0f : 0.0f;
	result[Y] = v[Y] < threshold[Y] ? 1.0f : 0.0f;
	result[Z] = v[Z] < threshold[Z] ? 1.0f : 0.0f;
	result[W] = v[W] < threshold[W] ? 1.0f : 0.0f;
	return result;
}

t_vec4f mix_vec4f(t_vec4f x, t_vec4f y, t_vec4f mask)
{
	t_vec4f result;

	result[X] = mask[X] * y[X] + (1.0f - mask[X]) * x[X];
	result[Y] = mask[Y] * y[Y] + (1.0f - mask[Y]) * x[Y];
	result[Z] = mask[Z] * y[Z] + (1.0f - mask[Z]) * x[Z];
	result[W] = mask[W] * y[W] + (1.0f - mask[W]) * x[W];
	return result;
}
