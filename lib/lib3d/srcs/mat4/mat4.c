/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/02 19:20:52 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_mat4	fill_mat4(t_mat4 m, float f)
{
	// int i;
	// int j;

	// i = 0;
	// while (i < 4) {
	// 	j = 0;
	// 	while (j < 4) {
	// 		m.m[i][j] = f;
	// 		j++;
	// 	}
	// 	i++;
	// }

	const t_mat4 new = {
		{{f, f, f, f},
		{f, f, f, f},
		{f, f, f, f},
		{f, f, f, f}}};
	return (new);
	
	// return (m);
}

t_mat4	create_mat4(float f)
{
	t_mat4	m;

	m = fill_mat4(m, f);
	return (m);
}

t_mat4 mat4_identity(void)
{
	t_mat4 result = create_mat4(0.0f);
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	return result;
}

t_mat4 swap_rows(t_mat4 mat, int row1, int row2)
{
    for (int i = 0; i < 4; i++) {
        float temp = mat.m[row1][i];
        mat.m[row1][i] = mat.m[row2][i];
        mat.m[row2][i] = temp;
    }
	return mat;
}

t_mat4 scale_row(t_mat4 mat, int row, float scalar)
{
    for (int i = 0; i < 4; i++) {
        mat.m[row][i] *= scalar;
    }
	return mat;
}

t_mat4 add_rows(t_mat4 mat, int row1, int row2, float scalar) {
    for (int i = 0; i < 4; i++) {
        mat.m[row1][i] += scalar * mat.m[row2][i];
    }
	return mat;
}

t_mat4	mat4_inverse(t_mat4 m)
{
	t_mat4 inv = mat4_identity();
	t_mat4 mat = m;
	for (int i = 0; i < 4; i++) {

		// Find pivot
		int pivot_row = i;
		float pivot = mat.m[i][i];

		for (int j = i + 1; j < 4; j++) {
			if (fabs(mat.m[j][i]) > fabs(pivot)) {
				pivot_row = j;
				pivot = mat.m[j][i];
			}
		}

		// t_mat4 is singular (no inverse)
		if (fabs(pivot) < 1e-8) {
			return mat;
		}

		// Swap pivot row with current row
		mat = swap_rows(mat, i, pivot_row);
		inv = swap_rows(inv, i, pivot_row);

		// Scale pivot row
		mat = scale_row(mat, i, 1.0f / pivot);
		inv = scale_row(inv, i, 1.0f / pivot);

		// Eliminate other rows
		for (int j = 0; j < 4; j++) {
			if (j != i) {
				float factor = -mat.m[j][i];
				mat = add_rows(mat, j, i, factor);
				inv = add_rows(inv, j, i, factor);
			}
		}
	}
	return inv;
}



t_mat4	mat4_perspective(float fovy, float aspect, float nearZ, float farZ)
{
	t_mat4  dest;
	dest = create_mat4(0.0f);
	float f, fn;
	
	f  = 1.0f / tanf(fovy * 0.5f);
	fn = 1.0f / (nearZ - farZ);
	dest.m[0][0] = f / aspect;
	dest.m[1][1] = f;
	dest.m[2][2] = (nearZ + farZ) * fn;
	dest.m[2][3] =-1.0f;
	dest.m[3][2] = 2.0f * nearZ * farZ * fn;
	return (dest);

}


t_mat4 mat4_look_at_f(t_vec3f eye, t_vec3f center, t_vec3f up)
{
	t_vec3f f = center - eye;
	f = vec3f_normalize(f);
	
	t_vec3f s = vec3f_cross(up, f);
	s = vec3f_normalize(s);
	t_vec3f u = vec3f_cross(f, s);
	t_mat4 m;
	
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
	m.m[0][3] = m.m[1][3] = m.m[2][3] = 0.0f;
	m.m[3][3] = 1.0f;
	return (m);
}

t_vec4f mat4_mul_vec4f(t_mat4 matrix, t_vec4f vector)
{
	t_vec4f result;

	result[X] = matrix.m[0][0] * vector[X] + matrix.m[1][0] * vector[Y] + matrix.m[2][0] * vector[Z] + matrix.m[3][0] * vector[W];
	result[Y] = matrix.m[0][1] * vector[X] + matrix.m[1][1] * vector[Y] + matrix.m[2][1] * vector[Z] + matrix.m[3][1] * vector[W];
	result[Z] = matrix.m[0][2] * vector[X] + matrix.m[1][2] * vector[Y] + matrix.m[2][2] * vector[Z] + matrix.m[3][2] * vector[W];
	result[W] = matrix.m[0][3] * vector[X] + matrix.m[1][3] * vector[Y] + matrix.m[2][3] * vector[Z] + matrix.m[3][3] * vector[W];
	return result;
}