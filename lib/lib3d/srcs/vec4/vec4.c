/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/12/15 00:08:45 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_vec4	vec4_new(float x, float y, float z, float w)
{
	return ((t_vec4){x, y, z, w});
}

t_vec4	vec4_mul(t_vec4 v1, t_vec4 v2)
{
	return ((t_vec4){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w});
}

t_vec4	vec4_mulf(t_vec4 v, float scalar)
{
	return ((t_vec4){v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar});
}


t_vec4	vec4_add(t_vec4 v1, t_vec4 v2)
{
	return ((t_vec4){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w});
}

float	vec4_length(t_vec4 v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

t_vec4	vec4_divf(t_vec4 v, float scalar)
{
	return ((t_vec4){v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar});
}

t_vec4	vec4_normalize(t_vec4 v)
{
	float length = vec4_length(v);
	if (length > 0.0f) {
		float invLength = 1.0f / length;
		v.x *= invLength;
		v.y *= invLength;
		v.z *= invLength;
		v.w *= invLength;
	}
	return v;
}

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


// t_vec4	vec4_clamp(t_vec4 v1, float min, float max)
// {
// 	return ((t_vec4){fminf(fmaxf(v1.x, min), max), fminf(fmaxf(v1.y, min), max), fminf(fmaxf(v1.z, min), max), fminf(fmaxf(v1.w, min), max)});
// }

// t_vec4 vec4_clamp(t_vec4 v, float min, float max)
// {
// 	t_vec4 res;

// 	res.x = fminf(fmaxf(v.x, min), max);
// 	res.y = fminf(fmaxf(v.y, min), max);
// 	res.z = fminf(fmaxf(v.z, min), max);
// 	res.w = fminf(fmaxf(v.w, min), max);
// 	return (res);
// }

t_vec4 vec4_clamp(t_vec4 v, float min, float max)
{
	if (v.x < min)
		v.x = min;
	else if (v.x > max)
		v.x = max;
	if (v.y < min)
		v.y = min;
	else if (v.y > max)
		v.y = max;
	if (v.z < min)
		v.z = min;
	else if (v.z > max)
		v.z = max;
	if (v.w < min)
		v.w = min;
	else if (v.w > max)
		v.w = max;
	return (v);
}