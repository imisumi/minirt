
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:29:39 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/17 01:22:01 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec.h"


t_vec4 vec4_clamp(t_vec4 v, float min, float max)
{
	t_vec4 res;

	res.x = fminf(fmaxf(v.x, min), max);
	res.y = fminf(fmaxf(v.y, min), max);
	res.z = fminf(fmaxf(v.z, min), max);
	res.w = fminf(fmaxf(v.w, min), max);
	return (res);
}

float vec4_len(t_vec4 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

t_vec4 vec4_normalize(t_vec4 v)
{
	float len;

	len = vec4_len(v);
	v.x /= len;
	v.y /= len;
	v.z /= len;
	v.w /= len;
	return(v);
}