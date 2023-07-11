/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:29:15 by ichiro            #+#    #+#             */
/*   Updated: 2023/07/10 23:11:30 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

# include "struct.h"
# include "vec.h"
# include "vec2.h"
# include "vec3.h"
# include "vec4.h"

// # include "mat4.h"

// #include "temp.h"




// t_quat quat_angleAxis(float angle, t_vec3 axis) {
//     t_quat result;
//     float halfAngle = angle * 0.5f;
//     float sinHalfAngle = sin(halfAngle);
//     result.x = axis.x * sinHalfAngle;
//     result.y = axis.y * sinHalfAngle;
//     result.z = axis.z * sinHalfAngle;
//     result.w = cos(halfAngle);
//     return result;
// }


// t_quat quat_cross(t_quat q1, t_quat q2) {
// 	t_quat result;
// 	result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
// 	result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
// 	result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
// 	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
// 	return result;
// }


t_vec4 vec4_div_float(t_vec4 v, float t)
{
	return (vec4_create(v.x / t, v.y / t, v.z / t, v.w / t));
}


t_vec3 reflect(t_vec3 incident, t_vec3 normal) {
    // Calculate the reflection direction
    t_vec3 reflection_direction;
	float dot_product = vec3_dot(incident, normal);
    reflection_direction.x = incident.x - 2.0f * dot_product * normal.x;
    reflection_direction.y = incident.y - 2.0f * dot_product * normal.y;
    reflection_direction.z = incident.z - 2.0f * dot_product * normal.z;

    return reflection_direction;
}

t_vec4 vec4_add(t_vec4 a, t_vec4 b)
{
	return (vec4_create(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w));
}

t_vec4 vec4_mul(t_vec4 a, t_vec4 b)
{
	return (vec4_create(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w));
}

t_vec3 vec3_reflect(t_vec3 incident, t_vec3 normal)
{
	return vec3_sub(incident, vec3_mul_float(normal, 2.0f * vec3_dot(incident, normal)));
}


#endif // MATH_H