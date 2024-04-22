/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/04/22 16:11:52 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_mat4	mat4_perspective(float fovy, float aspect, float near_z, float far_z)
{
	t_mat4	dest;
	float	f;
	float	fn;

	dest = create_mat4(0.0f);
	f = 1.0f / tanf(fovy * 0.5f);
	fn = 1.0f / (near_z - far_z);
	dest.m[0][0] = f / aspect;
	dest.m[1][1] = f;
	dest.m[2][2] = (near_z + far_z) * fn;
	dest.m[2][3] = -1.0f;
	dest.m[3][2] = 2.0f * near_z * far_z * fn;
	return (dest);
}

t_mat4	mat4_look_at_f(t_vec3f eye, t_vec3f center, t_vec3f up)
{
	const t_vec3f	f = vec3f_normalize(center - eye);
	const t_vec3f	s = vec3f_normalize(vec3f_cross(up, f));
	const t_vec3f	u = vec3f_cross(f, s);
	t_mat4			m;

	m.m[0][0] = s[X];
	m.m[0][1] = u[X];
	m.m[0][2] = f[X];
	m.m[1][0] = s[Y];
	m.m[1][1] = u[Y];
	m.m[1][2] = f[Y];
	m.m[2][0] = s[Z];
	m.m[2][1] = u[Z];
	m.m[2][2] = f[Z];
	m.m[3][0] = -vec3f_dot(s, eye);
	m.m[3][1] = -vec3f_dot(u, eye);
	m.m[3][2] = -vec3f_dot(f, eye);
	m.m[0][3] = 0.0f;
	m.m[1][3] = 0.0f;
	m.m[2][3] = 0.0f;
	m.m[3][3] = 1.0f;
	return (m);
}

t_vec4f	mat4_mul_vec4f(t_mat4 matrix, t_vec4f vector)
{
	const t_vec4f	result = {
		matrix.m[0][0] * vector[X] + matrix.m[1][0] * vector[Y] + \
			matrix.m[2][0] * vector[Z] + matrix.m[3][0] * vector[W],
		matrix.m[0][1] * vector[X] + matrix.m[1][1] * vector[Y] + \
			matrix.m[2][1] * vector[Z] + matrix.m[3][1] * vector[W],
		matrix.m[0][2] * vector[X] + matrix.m[1][2] * vector[Y] + \
			matrix.m[2][2] * vector[Z] + matrix.m[3][2] * vector[W],
		matrix.m[0][3] * vector[X] + matrix.m[1][3] * vector[Y] + \
			matrix.m[2][3] * vector[Z] + matrix.m[3][3] * vector[W]};

	return (result);
}
