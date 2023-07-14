/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:29:15 by ichiro            #+#    #+#             */
/*   Updated: 2023/07/14 01:08:43 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMP_H
# define TEMP_H

#include <math.h>
#include "struct.h"

t_vec3 hit_position(t_ray r, float t);

t_quat quat_cross(t_quat q1, t_quat q2);
t_quat quat_angleAxis(float angle, t_vec3 axis);

t_vec3 quat_rotate(t_quat q, t_vec3 v);

float t_quat_length(t_quat q);

t_quat quat_normalize(t_quat q);

t_mat4	fill_mat4(t_mat4 m, float f);

t_mat4	create_mat4(float f);

t_mat4 mat4_identity();

t_mat4 mat4_look_at(t_vec3 eye, t_vec3 center, t_vec3 up);
t_mat4 swap_rows(t_mat4 mat, int row1, int row2);

t_mat4 scale_row(t_mat4 mat, int row, float scalar);

t_mat4 add_rows(t_mat4 mat, int row1, int row2, float scalar);

t_mat4 mat4_inverse(t_mat4 m);
void print_mat4(t_mat4 m);

t_mat4 mat4_perspective(float fovy, float aspect, float nearZ, float farZ);

float fov_radians(float fov);

t_vec4 mat4_mul_vec4(t_mat4 matrix, t_vec4 vector);

t_mat4 mat4_mul_mat4(t_mat4 m1, t_mat4 m2);

#endif // TEMP_H