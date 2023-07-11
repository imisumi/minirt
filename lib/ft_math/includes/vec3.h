/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:29:15 by ichiro            #+#    #+#             */
/*   Updated: 2023/07/11 02:44:53 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include "struct.h"
# include <math.h>

// vec3
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_add_float(t_vec3 a, float f);

t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub_float(t_vec3 a, float f);

t_vec3	vec3_mul(t_vec3 a, t_vec3 b);
t_vec3	vec3_mul_float(t_vec3 a, float f);

t_vec3	vec3_div(t_vec3 a, t_vec3 b);
t_vec3	vec3_div_float(t_vec3 a, float f);

t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
t_vec3	vec3_normalize(t_vec3 v);
float	vec3_dot(t_vec3 a, t_vec3 b);
float	vec3_len(t_vec3 v);
t_vec3 vec3_max(t_vec3 v, float max);
float vec3_dot_float(t_vec3 a, float b);

t_vec3 vec3_reflect(t_vec3 incident, t_vec3 normal);

t_vec3 reflect(t_vec3 incident, t_vec3 normal);

#endif // VEC3_H