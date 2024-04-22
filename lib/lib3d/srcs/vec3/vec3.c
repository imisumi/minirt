/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/04/22 13:35:57 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

float	vec3f_dot(t_vec3f a, t_vec3f b)
{
	const float	dot = (a[X] * b[X] + a[Y] * b[Y] + a[Z] * b[Z]);

	return (dot);
}

t_vec3f	vec3f_cross(t_vec3f a, t_vec3f b)
{
	const t_vec3f	v = {
		a[Y] * b[Z] - a[Z] * b[Y],
		a[Z] * b[X] - a[X] * b[Z],
		a[X] * b[Y] - a[Y] * b[X],
		0.0f
	};

	return (v);
}

float	vec3f_length(t_vec3f v)
{
	return (sqrtf(v[X] * v[X] + v[Y] * v[Y] + v[Z] * v[Z]));
}

t_vec3f	vec3f_normalize(t_vec3f v)
{
	const float	length = vec3f_length(v);
	float		inv_length;

	if (length > 0.0f)
	{
		inv_length = 1.0f / length;
		v[X] *= inv_length;
		v[Y] *= inv_length;
		v[Z] *= inv_length;
	}
	return (v);
}

t_vec3f	vec3f_pow(t_vec3f vec, float exp)
{
	vec[X] = powf(vec[X], exp);
	vec[Y] = powf(vec[Y], exp);
	vec[Z] = powf(vec[Z], exp);
	vec[W] = powf(vec[W], exp);
	return (vec);
}
