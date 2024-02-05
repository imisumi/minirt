/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/05 03:01:01 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

float	vec3f_dot(t_vec3f a, t_vec3f b)
{
	const float dot = (a[X] * b[X] + a[Y] * b[Y] + a[Z] * b[Z]);

	return (dot);
}

t_vec3f vec3f_cross(t_vec3f a, t_vec3f b)
{
	const t_vec3f v = {
		a[Y] * b[Z] - a[Z] * b[Y],
		a[Z] * b[X] - a[X] * b[Z],
		a[X] * b[Y] - a[Y] * b[X],
		0.0f
	};

	return (v);
}

float vec3f_length(t_vec3f v)
{
	return (sqrtf(v[X] * v[X] + v[Y] * v[Y] + v[Z] * v[Z]));
}

t_vec3f vec3f_normalize(t_vec3f v)
{
	float length = vec3f_length(v);
	if (length > 0.0f) {
		float invLength = 1.0f / length;
		v[X] *= invLength;
		v[Y] *= invLength;
		v[Z] *= invLength;
	}
	return v;
}

t_vec3f	vec3f_pow(t_vec3f vec, float exp)
{
	vec[X] = powf(vec[X], exp);
	vec[Y] = powf(vec[Y], exp);
	vec[Z] = powf(vec[Z], exp);
	vec[W] = powf(vec[W], exp);
	return (vec);
}

t_vec3f	vec3f_less_than(t_vec3f vec, float value)
{
	vec[X] = vec[X] < value ? vec[X] : value;
	vec[Y] = vec[Y] < value ? vec[Y] : value;
	vec[Z] = vec[Z] < value ? vec[Z] : value;
	vec[W] = vec[W] < value ? vec[W] : value;
	return (vec);
}

float vec3f_distance(t_vec3f point1, t_vec3f point2)
{
	const t_vec3f v = point2 - point1;

	return (sqrtf(v[X] * v[X] + v[Y] * v[Y] + v[Z] * v[Z]));
}


t_vec3f	vec3f_reflect(t_vec3f v, t_vec3f n)
{
	return (v - (n * 2.0f * vec3f_dot(v, n)));
}

t_vec3f	vec3f_lerp(const t_vec3f vec1, const t_vec3f vec2, const float t)
{
	const t_vec3f	result = (1.0f - t) * vec1 + t * vec2;

	return (result);
}

t_vec3f	vec3f_exp(t_vec3f v)
{
	return ((t_vec3f){expf(v[X]), expf(v[Y]), expf(v[Z]), 0.0f});
}


t_vec3f	vec3f_refract(t_vec3f incident, t_vec3f normal, float eta)
{
	t_vec3f out;
	float N_dot_I = vec3f_dot(normal, incident);
	float k = 1.f - eta * eta * (1.f - N_dot_I * N_dot_I);
	if (k < 0.f)
		out = (t_vec3f){0.f, 0.f, 0.f, 0.0f};
	else
		out = eta * incident - (eta * N_dot_I + sqrtf(k)) * normal;

	return (out);
}

t_vec3f	vec3f_to_vec4f(t_vec3f v, float f)
{
	return ((t_vec3f){v[X], v[Y], v[Z], f});
}