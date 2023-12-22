/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/12/17 21:23:21 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_quat	quat_new(float x, float y, float z, float w)
{
	return ((t_quat){x, y, z, w});
}

t_quat	quat_angle_axis(float angle, t_vec3 axis)
{
	t_quat	result;

	float halfAngle = angle * 0.5f;
	float sinHalfAngle = sinf(halfAngle);
	result.x = axis.x * sinHalfAngle;
	result.y = axis.y * sinHalfAngle;
	result.z = axis.z * sinHalfAngle;
	result.w = cosf(halfAngle);
	return (result);
}

t_quat	quat_angle_axis_f(float angle, t_vec3f axis)
{
	t_quat	result;

	float halfAngle = angle * 0.5f;
	float sinHalfAngle = sinf(halfAngle);
	result.x = axis[X] * sinHalfAngle;
	result.y = axis[Y] * sinHalfAngle;
	result.z = axis[Z] * sinHalfAngle;
	result.w = cosf(halfAngle);
	return (result);
}

t_quat	quat_cross(t_quat q1, t_quat q2)
{
	t_quat result;

	result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	return (result);
}

float t_quat_length(t_quat q)
{
	return sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

t_quat quat_normalize(t_quat q)
{
	float length = t_quat_length(q);
	if (length > 0.0f) {
		float invLength = 1.0f / length;
		q.x *= invLength;
		q.y *= invLength;
		q.z *= invLength;
		q.w *= invLength;
	}
	return q;
}












t_vec3 quat_rotate(t_quat q, t_vec3 v) {
    t_vec3 result;
    float qxx = q.x * q.x;
    float qyy = q.y * q.y;
    float qzz = q.z * q.z;
    float qxz = q.x * q.z;
    float qxy = q.x * q.y;
    float qyz = q.y * q.z;
    float qwx = q.w * q.x;
    float qwy = q.w * q.y;
    float qwz = q.w * q.z;

    result.x = (1.0f - 2.0f * (qyy + qzz)) * v.x + (2.0f * (qxy - qwz)) * v.y + (2.0f * (qxz + qwy)) * v.z;
    result.y = (2.0f * (qxy + qwz)) * v.x + (1.0f - 2.0f * (qxx + qzz)) * v.y + (2.0f * (qyz - qwx)) * v.z;
    result.z = (2.0f * (qxz - qwy)) * v.x + (2.0f * (qyz + qwx)) * v.y + (1.0f - 2.0f * (qxx + qyy)) * v.z;

    return result;
}

t_vec3f quat_rotate_f(t_quat q, t_vec3f v)
{
	t_vec3f result;
	float qxx = q.x * q.x;
	float qyy = q.y * q.y;
	float qzz = q.z * q.z;
	float qxz = q.x * q.z;
	float qxy = q.x * q.y;
	float qyz = q.y * q.z;
	float qwx = q.w * q.x;
	float qwy = q.w * q.y;
	float qwz = q.w * q.z;
	
	result[X] = (1.0f - 2.0f * (qyy + qzz)) * v[X] + (2.0f * (qxy - qwz)) * v[Y] + (2.0f * (qxz + qwy)) * v[Z];
	result[Y] = (2.0f * (qxy + qwz)) * v[X] + (1.0f - 2.0f * (qxx + qzz)) * v[Y] + (2.0f * (qyz - qwx)) * v[Z];
	result[Z] = (2.0f * (qxz - qwy)) * v[X] + (2.0f * (qyz + qwx)) * v[Y] + (1.0f - 2.0f * (qxx + qyy)) * v[Z];
	result[W] = 0.0f;
	return result;
}


float fov_radians(float fov)
{
	return fov * (M_PI / 180.0f);
}