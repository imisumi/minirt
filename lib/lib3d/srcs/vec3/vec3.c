/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/12/15 00:33:44 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3	vec3_addf(t_vec3 a, float b)
{
	return ((t_vec3){a.x + b, a.y + b, a.z + b});
}

t_vec3	vec3_subf(t_vec3 a, float b)
{
	return ((t_vec3){a.x - b, a.y - b, a.z - b});
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec3	vec3_mul(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x * b.x, a.y * b.y, a.z * b.z});
}

t_vec3	vec3_mulf(t_vec3 a, float b)
{
	return ((t_vec3){a.x * b, a.y * b, a.z * b});
}

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float	vec3f_dot(t_vec3f a, t_vec3f b)
{
	return (a[X] * b[X] + a[Y] * b[Y] + a[Z] * b[Z]);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.y * b.z - a.z * b.y, \
					a.z * b.x - a.x * b.z, \
					a.x * b.y - a.y * b.x});
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




t_vec3	vec3_new(float x, float y, float z)
{
	return ((t_vec3){x, y, z});
}


t_vec3	vec3_normalize(t_vec3 v)
{
	float length = vec3_length(v);
	if (length > 0.0f) {
		float invLength = 1.0f / length;
		v.x *= invLength;
		v.y *= invLength;
		v.z *= invLength;
	}
	return v;
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

float		vec3_length(t_vec3 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}


t_vec3		vec3_div(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x / b.x, a.y / b.y, a.z / b.z});
}

t_vec3		vec3_divf(t_vec3 a, float b)
{
	float f = sqrtf(b);
	return ((t_vec3){a.x / b, a.y / b, a.z / b});
}