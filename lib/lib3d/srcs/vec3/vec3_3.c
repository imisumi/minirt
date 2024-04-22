/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/04/22 13:36:38 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

// t_vec3f	vec3f_less_than(t_vec3f vec, float value)
// {
// 	vec[X] = vec[X] < value ? vec[X] : value;
// 	vec[Y] = vec[Y] < value ? vec[Y] : value;
// 	vec[Z] = vec[Z] < value ? vec[Z] : value;
// 	vec[W] = vec[W] < value ? vec[W] : value;
// 	return (vec);
// }

t_vec3f	vec3f_less_than(t_vec3f vec, float value)
{
	if (vec[X] < value)
		vec[X] = vec[X];
	else
		vec[X] = value;
	if (vec[Y] < value)
		vec[Y] = vec[Y];
	else
		vec[Y] = value;
	if (vec[Z] < value)
		vec[Z] = vec[Z];
	else
		vec[Z] = value;
	return (vec);
}

float	vec3f_distance(t_vec3f point1, t_vec3f point2)
{
	const t_vec3f	v = point2 - point1;

	return (sqrtf(v[X] * v[X] + v[Y] * v[Y] + v[Z] * v[Z]));
}
