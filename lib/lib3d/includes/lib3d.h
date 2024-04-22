/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/04/22 17:04:24 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB3D_H
# define LIB3D_H

# include <math.h>
# include <stdint.h>

typedef float	t_vec4f __attribute__ ((vector_size ((sizeof(float) * 4))));
typedef float	t_vec3f __attribute__ ((vector_size ((sizeof(float) * 4))));
typedef float	t_vec2f __attribute__ ((vector_size ((sizeof(float) * 2))));

typedef t_vec3f	t_rayf[2];

# define ORIGIN 0
# define DIR 1

# define X 0
# define Y 1
# define Z 2
# define W 3

# define R 0
# define G 1
# define B 2
# define A 3

typedef struct s_mat4
{
	float		m[4][4];
}				t_mat4;

typedef struct s_quaternion
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_quat;

/* ************************************************************************** */
/*                                    vec2                                    */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                    vec3                                    */
/* ************************************************************************** */
float	vec3f_dot(t_vec3f a, t_vec3f b);
t_vec3f	vec3f_cross(t_vec3f a, t_vec3f b);
float	vec3f_length(t_vec3f v);
t_vec3f	vec3f_normalize(t_vec3f v);
t_vec3f	vec3f_pow(t_vec3f vec, float exp);

t_vec3f	vec3f_reflect(t_vec3f v, t_vec3f n);
t_vec3f	vec3f_lerp(const t_vec3f vec1, const t_vec3f vec2, const float t);
t_vec3f	vec3f_exp(t_vec3f v);
t_vec3f	vec3f_refract(t_vec3f incident, t_vec3f normal, float eta);
t_vec3f	vec3f_to_vec4f(t_vec3f v, float f);

t_vec3f	vec3f_less_than(t_vec3f vec, float value);
float	vec3f_distance(t_vec3f point1, t_vec3f point2);

/* ************************************************************************** */
/*                                    vec4                                    */
/* ************************************************************************** */
float	vec4f_length(t_vec4f v);
t_vec4f	vec4f_normalize(t_vec4f v);
t_vec4f	vec4f_clamp(t_vec4f vec, float min, float max);
t_vec4f	vec4f_less_than(t_vec4f v, t_vec4f threshold);
t_vec4f	mix_vec4f(t_vec4f x, t_vec4f y, t_vec4f mask);

/* ************************************************************************** */
/*                                    mat4                                    */
/* ************************************************************************** */
t_mat4	fill_mat4(float f);
t_mat4	create_mat4(float f);
t_mat4	mat4_identity(void);
t_mat4	mat4_inverse(t_mat4 m);

t_mat4	mat4_perspective(float fovy, float aspect, float near_z, float far_z);
t_mat4	mat4_look_at_f(t_vec3f eye, t_vec3f center, t_vec3f up);
t_vec4f	mat4_mul_vec4f(t_mat4 matrix, t_vec4f vector);

t_mat4	swap_rows(t_mat4 mat, int row1, int row2);
t_mat4	scale_row(t_mat4 mat, int row, float scalar);
t_mat4	add_rows(t_mat4 mat, int row1, int row2, float scalar);
void	inverse_2(t_mat4 *inv, t_mat4 *mat, int i);
void	inverse_1(t_mat4 mat, int i, int *pivot_row, float *pivot);

/* ************************************************************************** */
/*                                    quat                                    */
/* ************************************************************************** */
t_quat	quat_new(float x, float y, float z, float w);
// angle in radians
t_quat	quat_angle_axis_f(float angle, t_vec3f axis);
t_quat	quat_cross(t_quat q1, t_quat q2);
float	t_quat_length(t_quat q);
t_quat	quat_normalize(t_quat q);
t_vec3f	quat_rotate_f(t_quat q, t_vec3f v);

#endif
