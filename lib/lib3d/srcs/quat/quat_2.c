/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/04/22 13:59:50 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

//?		qxx [0]
//?		qyy [1]
//?		qzz [2]
//?		qxz [3]
//?		qxy [4]
//?		qyz [5]
//?		qwx [6]
//?		qwy [7]
//?		qwz [8]
t_vec3f	quat_rotate_f(t_quat q, t_vec3f v)
{
	const float		qxy[9] = {
		q.x * q.x,
		q.y * q.y,
		q.z * q.z,
		q.x * q.z,
		q.x * q.y,
		q.y * q.z,
		q.w * q.x,
		q.w * q.y,
		q.w * q.z};
	const t_vec3f	result = {
		(1.0f - 2.0f * (qxy[1] + qxy[2])) * v[X] + (2.0f * (qxy[4] - qxy[8])) \
			* v[Y] + (2.0f * (qxy[3] + qxy[7])) * v[Z],
		(2.0f * (qxy[4] + qxy[8])) * v[X] + (1.0f - 2.0f * (qxy[0] + qxy[2])) \
			* v[Y] + (2.0f * (qxy[5] - qxy[6])) * v[Z],
		(2.0f * (qxy[3] - qxy[7])) * v[X] + (2.0f * (qxy[5] + qxy[6])) * v[Y] \
			+ (1.0f - 2.0f * (qxy[0] + qxy[1])) * v[Z],
		0.0f};

	return (result);
}

// t_vec3f	quat_rotate_f(t_quat q, t_vec3f v)
// {
// 	t_vec3f	result;

// 	float	qxx = q.x * q.x;
// 	float	qyy = q.y * q.y;
// 	float	qzz = q.z * q.z;
// 	float	qxz = q.x * q.z;
// 	float	qxy = q.x * q.y;
// 	float	qyz = q.y * q.z;
// 	float	qwx = q.w * q.x;
// 	float	qwy = q.w * q.y;
// 	float	qwz = q.w * q.z;

// 	result[X] = (1.0f - 2.0f * (qyy + qzz)) * v[X] + (2.0f * 
//		(qxy - qwz)) * v[Y] + (2.0f * (qxz + qwy)) * v[Z];
// 	result[Y] = (2.0f * (qxy + qwz)) * v[X] + (1.0f - 2.0f * 
//		(qxx + qzz)) * v[Y] + (2.0f * (qyz - qwx)) * v[Z];
// 	result[Z] = (2.0f * (qxz - qwy)) * v[X] + (2.0f * (qyz + qwx)) 
//		* v[Y] + (1.0f - 2.0f * (qxx + qyy)) * v[Z];
// 	result[W] = 0.0f;
// 	return result;
// }
