/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:29:15 by ichiro            #+#    #+#             */
/*   Updated: 2023/07/14 02:07:02 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

# include "struct.h"
# include "vec.h"
# include "vec2.h"
# include "vec3.h"
# include "vec4.h"
#include "mat4.h"

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



#endif // MATH_H