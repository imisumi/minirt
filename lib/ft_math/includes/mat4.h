/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:29:15 by ichiro            #+#    #+#             */
/*   Updated: 2023/07/14 02:03:13 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT4_H
# define MAT4_H

# include "struct.h"
# include "vec3.h"
#include <stdio.h>

# include <math.h>

t_mat4	fill_mat4(t_mat4 m, float f);

t_mat4	create_mat4(float f);

t_mat4 mat4_identity(void);


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
	
// 	float	verticalFOV;
//     float  aspectRatio;
// 	float	zNear;
// 	float	zFar;

// 	t_vec3	position;
// 	t_vec3	direction;

// 	t_vec2	mouseDelta;
//     t_vec2	mousePos;
//     bool    mouse_lock;
//     t_vec2	prevMousePos;

// 	t_vec3	*rayDirections;
// } t_camera;

// typedef struct s_scene
// {
// 	t_sphere spheres[10];
// 	uint8_t nb_spheres;

// 	t_camera camera;
// } t_scene;

















t_vec3 hit_position(t_ray r, float t);

t_quat quat_cross(t_quat q1, t_quat q2);

t_quat quat_angleAxis(float angle, t_vec3 axis);

t_vec3 quat_rotate(t_quat q, t_vec3 v);


float t_quat_length(t_quat q);

t_quat quat_normalize(t_quat q);




t_mat4 mat4_look_at(t_vec3 eye, t_vec3 center, t_vec3 up);

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

t_mat4 swap_rows(t_mat4 mat, int row1, int row2);

t_mat4 scale_row(t_mat4 mat, int row, float scalar);

t_mat4 add_rows(t_mat4 mat, int row1, int row2, float scalar);

t_mat4 mat4_inverse(t_mat4 m);

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

void print_mat4(t_mat4 m);


t_mat4 mat4_perspective(float fovy, float aspect, float nearZ, float farZ);

float fov_radians(float fov);


t_vec4 mat4_mul_vec4(t_mat4 matrix, t_vec4 vector);

// t_vec4 mat4_mul_vec4(t_mat4 m, t_vec4 v) {
// 	t_vec4 res;
// 	res.x = m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * v.z + m.m[3][0] * v.w;
// 	res.y = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z + m.m[3][1] * v.w;
// 	res.z = m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z + m.m[3][2] * v.w;
// 	res.w = m.m[0][3] * v.x + m.m[1][3] * v.y + m.m[2][3] * v.z + m.m[3][3] * v.w;
// 	return res;
// }


t_mat4 mat4_mul_mat4(t_mat4 m1, t_mat4 m2);

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


#endif // MAT4_H