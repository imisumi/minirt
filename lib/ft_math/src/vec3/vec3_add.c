/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:29:39 by ichiro            #+#    #+#             */
/*   Updated: 2023/07/11 02:44:47 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3.h"

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vec3	vec3_add_float(t_vec3 a, float f)
{
	t_vec3	res;

	res.x = a.x + f;
	res.y = a.y + f;
	res.z = a.z + f;
	return (res);
}


t_vec3 vec3_reflect(t_vec3 incident, t_vec3 normal)
{
	return vec3_sub(incident, vec3_mul_float(normal, 2.0f * vec3_dot(incident, normal)));
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