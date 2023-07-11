/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:29:39 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/25 23:38:15 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec.h"

t_vec2	vec2_add(t_vec2 a, t_vec2 b)
{
	t_vec2	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return (res);
}

t_vec2	vec2_add_float(t_vec2 a, float f)
{
	t_vec2	res;

	res.x = a.x + f;
	res.y = a.y + f;
	return (res);
}

t_vec2	vec2_sub(t_vec2 a, t_vec2 b)
{
	t_vec2	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return (res);
}

t_vec2	vec2_sub_float(t_vec2 a, float f)
{
	t_vec2	res;

	res.x = a.x - f;
	res.y = a.y - f;
	return (res);
}

t_vec2	vec2_mul(t_vec2 a, t_vec2 b)
{
	t_vec2	res;

	res.x = a.x * b.x;
	res.y = a.y * b.y;
	return (res);
}

t_vec2	vec2_mul_float(t_vec2 a, float f)
{
	t_vec2	res;

	res.x = a.x * f;
	res.y = a.y * f;
	return (res);
}