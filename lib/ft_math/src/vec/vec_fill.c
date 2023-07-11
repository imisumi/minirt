/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:29:39 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/15 20:59:29 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec.h"

t_vec2 vec2_fill(float f)
{
	t_vec2	res;

	res.x = f;
	res.y = f;
	return (res);
}

t_vec3 vec3_fill(float f)
{
	t_vec3	res;

	res.x = f;
	res.y = f;
	res.z = f;
	return (res);
}

t_vec4 vec4_fill(float f)
{
	t_vec4	res;

	res.x = f;
	res.y = f;
	res.z = f;
	res.w = f;
	return (res);
}
