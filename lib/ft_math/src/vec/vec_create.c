/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:29:39 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/17 01:09:12 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec.h"

t_vec2 vec2_create(float x, float y)
{
	t_vec2 res;

	res.x = x;
	res.y = y;
	return (res);
}

t_vec3 vec3_create(float x, float y, float z)
{
	t_vec3 res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

t_vec4 vec4_create(float x, float y, float z, float w)
{
	t_vec4 res;

	res.x = x;
	res.y = y;
	res.z = z;
	res.w = w;
	return (res);
}