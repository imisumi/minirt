/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/07/15 17:23:23 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITABLE_H
# define HITABLE_H

// #include "main.h"
#include "scene.h"

#include <stdio.h>

// typedef struct hit_record
// {
// 	float t;
// 	t_vec3 p;
// 	t_vec3 normal;
// } t_hit_record;

// typedef struct s_sphere
// {
// 	t_vec3 center;
// 	float radius;
// } t_sphere;

// typedef struct s_camera
// {
// 	// t_vec3 origin;
// 	// t_vec3 lower_left_corner;
// 	// t_vec3 horizontal;
// 	// t_vec3 vertical;
	
// 	t_mat4	projection;
// 	t_mat4	inv_projection;
// 	t_mat4	view;
// 	t_mat4	inv_view;
	
// 	float	vertical_fov;
//     float  aspectRatio;
// 	float	zNear;
// 	float	zFar;

// 	t_vec3	position;
// 	t_vec3	direction;

// 	t_vec2	mouse_delta;
//     t_vec2	mouse_pos;
//     bool    mouse_lock;
//     t_vec2	prev_mouse_pos;

// 	t_vec3	*ray_dir;
// } t_camera;

// typedef struct s_scene
// {
// 	t_sphere spheres[10];
// 	uint8_t nb_spheres;

// 	t_camera camera;
// } t_scene;

















t_vec3 hit_position(t_ray r, float t);

t_quat quat_cross(t_quat q1, t_quat q2) {
	t_quat result;
	result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	return result;
}

t_quat quat_angleAxis(float angle, t_vec3 axis) {
    t_quat result;
    float halfAngle = angle * 0.5f;
    float sinHalfAngle = sin(halfAngle);
    result.x = axis.x * sinHalfAngle;
    result.y = axis.y * sinHalfAngle;
    result.z = axis.z * sinHalfAngle;
    result.w = cos(halfAngle);
    return result;
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


float t_quat_length(t_quat q) {
    return sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

t_quat quat_normalize(t_quat q) {
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

t_mat4	fill_mat4(t_mat4 m, float f) {
	int i;
	int j;

	i = 0;
	while (i < 4) {
		j = 0;
		while (j < 4) {
			m.m[i][j] = f;
			j++;
		}
		i++;
	}
	return (m);
}

t_mat4	create_mat4(float f) {
	t_mat4 m;

	m = fill_mat4(m, f);
	return (m);
}

t_mat4 mat4_identity()
{
	t_mat4 result = create_mat4(0.0f);
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	return result;
}

t_mat4 mat4_look_at(t_vec3 eye, t_vec3 center, t_vec3 up)
{
	t_vec3 f = vec3_sub(center, eye);
	f = vec3_normalize(f);
	
	t_vec3 s = vec3_cross(up, f);
	s = vec3_normalize(s);
	t_vec3 u = vec3_cross(f, s);
	t_mat4 m;
	
	m.m[0][0] = s.x;
	m.m[0][1] = u.x;
	m.m[0][2] = f.x;
	m.m[1][0] = s.y;
	m.m[1][1] = u.y;
	m.m[1][2] = f.y;
	m.m[2][0] = s.z;
	m.m[2][1] = u.z;
	m.m[2][2] = f.z;
	m.m[3][0] = -vec3_dot(s, eye);
	m.m[3][1] = -vec3_dot(u, eye);
	m.m[3][2] = -vec3_dot(f, eye);
	m.m[0][3] = m.m[1][3] = m.m[2][3] = 0.0f;
	m.m[3][3] = 1.0f;
	return (m);
}

// t_mat4 mat4_look_at(t_vec3 pos, t_vec3 target, t_vec3 up)
// {
//     t_vec3 f = vec3_add(target, vec3_mul_float(pos, -1.0f));
//     t_vec3 f_normalized = vec3_normalize(f);

//     t_vec3 s = vec3_cross(f_normalized, up);
//     t_vec3 s_normalized = vec3_normalize(s);

//     t_vec3 u = vec3_cross(s_normalized, f_normalized);

//     t_mat4 result = mat4_identity();
//     result.m[0][0] = s_normalized.x;
//     result.m[1][0] = s_normalized.y;
//     result.m[2][0] = s_normalized.z;
//     result.m[0][1] = u.x;
//     result.m[1][1] = u.y;
//     result.m[2][1] = u.z;
//     result.m[0][2] = -f_normalized.x;
//     result.m[1][2] = -f_normalized.y;
//     result.m[2][2] = -f_normalized.z;
// 	//! might be wrong
//     // result.m[3][0] = -vec3_dot(s_normalized, pos);
// 	result.m[3][0] = -vec3_dot(s_normalized, pos);
//     result.m[3][1] = -vec3_dot(u, pos);
//     result.m[3][2] = vec3_dot(f_normalized, pos);

//     return result;
// }

// t_mat4 mat4_identity()
// {
//     t_mat4 res;

//     res.m[0][0] = 1.0f;
//     res.m[0][1] = 0.0f;
//     res.m[0][2] = 0.0f;
//     res.m[0][3] = 0.0f;

//     res.m[1][0] = 0.0f;
//     res.m[1][1] = 1.0f;
//     res.m[1][2] = 0.0f;
//     res.m[1][3] = 0.0f;

//     res.m[2][0] = 0.0f;
//     res.m[2][1] = 0.0f;
//     res.m[2][2] = 1.0f;
//     res.m[2][3] = 0.0f;

//     res.m[3][0] = 0.0f;
//     res.m[3][1] = 0.0f;
//     res.m[3][2] = 0.0f;
//     res.m[3][3] = 1.0f;

//     return res;
// }

t_mat4 swap_rows(t_mat4 mat, int row1, int row2) {
    for (int i = 0; i < 4; i++) {
        float temp = mat.m[row1][i];
        mat.m[row1][i] = mat.m[row2][i];
        mat.m[row2][i] = temp;
    }
	return mat;
}

t_mat4 scale_row(t_mat4 mat, int row, float scalar) {
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

t_mat4 mat4_inverse(t_mat4 m) {
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

// t_mat4 mat4_inverse(t_mat4 m)
// 	{
// 	float det = m.m[0][0] * (m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1]) -
// 	            m.m[0][1] * (m.m[1][0] * m.m[2][2] - m.m[1][2] * m.m[2][0]) +
// 	            m.m[0][2] * (m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0]);
// 	t_mat4 res = mat4_identity();
// 	if (det == 0.0f)
// 	{
// 	    // Matrix is not invertible, handle this case accordingly
// 	    // For example, set the inverse matrix to an identity matrix
// 	    // or return an error.
// 	    return res;
// 	}
		
// 	float inv_det = 1.0f / det;

		
// 	res.m[0][0] = (m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1]) * inv_det;
// 	res.m[0][1] = -(m.m[0][1] * m.m[2][2] - m.m[0][2] * m.m[2][1]) * inv_det;
// 	res.m[0][2] = (m.m[0][1] * m.m[1][2] - m.m[0][2] * m.m[1][1]) * inv_det;
// 	res.m[0][3] = 0.0f;
		
// 	res.m[1][0] = -(m.m[1][0] * m.m[2][2] - m.m[1][2] * m.m[2][0]) * inv_det;
// 	res.m[1][1] = (m.m[0][0] * m.m[2][2] - m.m[0][2] * m.m[2][0]) * inv_det;
// 	res.m[1][2] = -(m.m[0][0] * m.m[1][2] - m.m[0][2] * m.m[1][0]) * inv_det;
// 	res.m[1][3] = 0.0f;
	
// 	res.m[2][0] = (m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0]) * inv_det;
// 	res.m[2][1] = -(m.m[0][0] * m.m[2][1] - m.m[0][1] * m.m[2][0]) * inv_det;
// 	res.m[2][2] = (m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0]) * inv_det;
// 	res.m[2][3] = 0.0f;
	
// 	res.m[3][0] = -(m.m[1][0] * m.m[2][3] * m.m[3][2] - m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[2][0] * m.m[1][3] * m.m[3][2] + m.m[2][0] * m.m[1][2] * m.m[3][3] + m.m[3][0] * m.m[1][3] * m.m[2][2] - m.m[3][0] * m.m[1][2] * m.m[2][3]) * inv_det;
// 	res.m[3][1] = (m.m[0][0] * m.m[2][3] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][3] - m.m[2][0] * m.m[0][3] * m.m[3][2] + m.m[2][0] * m.m[0][2] * m.m[3][3] + m.m[3][0] * m.m[0][3] * m.m[2][2] - m.m[3][0] * m.m[0][2] * m.m[2][3]) * inv_det;
// 	res.m[3][2] = -(m.m[0][0] * m.m[1][3] * m.m[3][2] - m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[1][0] * m.m[0][3] * m.m[3][2] + m.m[1][0] * m.m[0][2] * m.m[3][3] + m.m[3][0] * m.m[0][3] * m.m[1][2] - m.m[3][0] * m.m[0][2] * m.m[1][3]) * inv_det;
// 	res.m[3][3] = 1.0f;
// 	return res;
	
// }

void print_mat4(t_mat4 m)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%f ", m.m[i][j]);
        }
        printf("\n");
    }
     printf("\n");
}


t_mat4 mat4_perspective(float fovy, float aspect, float nearZ, float farZ)
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



	// TODO		af*x
	// TODO		f*y
	// TODO		λ*z-λ*znear

	// float a = height / width;
	// float f = 1.0f / tanf(fov / 2);
	// float λ = (zfar / (zfar - znear)) - ((zfar * ) / (zfar - znear));

	// float zfar = farZ;
	// float znear = nearZ;
	// float fov = fovy;

	// t_mat4 m;
	// m = create_mat4(0.0f);
	// m.m[0][0] = aspect * (1 / tanf(fov / 2));
	// m.m[1][1] = 1 / tanf(fov / 2);
	// m.m[2][2] = zfar / (zfar - znear);
	// m.m[2][3] = (-zfar * znear) / (zfar - znear);
	// m.m[3][2] = 1.0f;
	// return (m);
}

float fov_radians(float fov)
{
    return fov * (M_PI / 180.0f);
}


t_vec4 mat4_mul_vec4(t_mat4 matrix, t_vec4 vector) {
    t_vec4 result;
    
    result.x = matrix.m[0][0] * vector.x + matrix.m[1][0] * vector.y + matrix.m[2][0] * vector.z + matrix.m[3][0] * vector.w;
    result.y = matrix.m[0][1] * vector.x + matrix.m[1][1] * vector.y + matrix.m[2][1] * vector.z + matrix.m[3][1] * vector.w;
    result.z = matrix.m[0][2] * vector.x + matrix.m[1][2] * vector.y + matrix.m[2][2] * vector.z + matrix.m[3][2] * vector.w;
    result.w = matrix.m[0][3] * vector.x + matrix.m[1][3] * vector.y + matrix.m[2][3] * vector.z + matrix.m[3][3] * vector.w;
    
    return result;
}

// t_vec4 mat4_mul_vec4(t_mat4 m, t_vec4 v) {
// 	t_vec4 res;
// 	res.x = m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * v.z + m.m[3][0] * v.w;
// 	res.y = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z + m.m[3][1] * v.w;
// 	res.z = m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z + m.m[3][2] * v.w;
// 	res.w = m.m[0][3] * v.x + m.m[1][3] * v.y + m.m[2][3] * v.z + m.m[3][3] * v.w;
// 	return res;
// }


t_mat4 mat4_mul_mat4(t_mat4 m1, t_mat4 m2)
{
    t_mat4 res;

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            res.m[row][col] = 0.0f;
            for (int k = 0; k < 4; k++) {
                res.m[row][col] += m1.m[row][k] * m2.m[k][col];
            }
        }
    }

    return res;
}

// t_mat4 mat4_mul_mat4(t_mat4 m1, t_mat4 m2)
// {
//     t_mat4 res;

//     for (int row = 0; row < 4; row++) {
//         for (int col = 0; col < 4; col++) {
//             res.m[row][col] = 0.0f;
//             for (int k = 0; k < 4; k++) {
//                 res.m[row][col] += m1.m[row][k] * m2.m[k][col];
//             }
//         }
//     }

//     return res;
// }

#endif