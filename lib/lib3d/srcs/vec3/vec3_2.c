/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/04/22 13:34:38 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

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
	t_vec3f		out;
	const float	n_dot_i = vec3f_dot(normal, incident);
	const float	k = 1.f - eta * eta * (1.f - n_dot_i * n_dot_i);

	if (k < 0.f)
		out = (t_vec3f){0.f, 0.f, 0.f, 0.0f};
	else
		out = eta * incident - (eta * n_dot_i + sqrtf(k)) * normal;
	return (out);
}

t_vec3f	vec3f_to_vec4f(t_vec3f v, float f)
{
	return ((t_vec3f){v[X], v[Y], v[Z], f});
}
