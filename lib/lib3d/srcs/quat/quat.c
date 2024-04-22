/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/04/22 14:00:17 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_quat	quat_new(float x, float y, float z, float w)
{
	return ((t_quat){x, y, z, w});
}

// angle in radians
t_quat	quat_angle_axis_f(float angle, t_vec3f axis)
{
	t_quat		result;
	const float	half_angle = angle * 0.5f;
	const float	sin_half_angle = sinf(half_angle);

	result.x = axis[X] * sin_half_angle;
	result.y = axis[Y] * sin_half_angle;
	result.z = axis[Z] * sin_half_angle;
	result.w = cosf(half_angle);
	return (result);
}

t_quat	quat_cross(t_quat q1, t_quat q2)
{
	const t_quat	result = {
		q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
		q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
		q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w,
		q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z};

	return (result);
}

float	t_quat_length(t_quat q)
{
	return (sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w));
}

t_quat	quat_normalize(t_quat q)
{
	const float	length = t_quat_length(q);
	float		inv_length;

	if (length > 0.0f)
	{
		inv_length = 1.0f / length;
		q.x *= inv_length;
		q.y *= inv_length;
		q.z *= inv_length;
		q.w *= inv_length;
	}
	return (q);
}
