/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:33:16 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/14 04:35:22 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3f	default_skyf(t_vec3f direction, t_scene scene)
{
	t_vec3f	sky;
	float	t;

	t = 0.5f * (vec3f_normalize(direction)[Y] + 1.0f);
	sky = ((t_vec3f){0.5f, 0.7f, 1.0f, 0.0f} * (1.0f - t)) + \
			((t_vec3f){1.0f, 1.0f, 1.0f, 0.0f} * t);
	return (sky);
}

t_hitinfo	new_hitinfo(void)
{
	const t_hitinfo	hitinfo = {.distance = INFINITY, .hit = false};

	return (hitinfo);
}

float	lerpf(float a, float b, float t)
{
	return (a + (b - a) * t);
}

//	float fresnel_reflect_amount(float n1, float n2, t_vec3f incident, 
//		t_vec3f normal, float f0, float f90)
//	float cosX = -vec3f_dot(normal, incident);
//	float	f90 = 1.0f; in both returns
float	fresnel_reflect_amount(float n1, float n2, float cosx, float f0)
{
	float	r0;
	float	n;
	float	sin_t2;
	float	x;
	float	ret;

	r0 = (n1 - n2) / (n1 + n2);
	r0 *= r0;
	if (n1 > n2)
	{
		n = n1 / n2;
		sin_t2 = n * n * (1.0 - cosx * cosx);
		if (sin_t2 > 1.0)
			return (1.0f);
		cosx = sqrtf(1.0 - sin_t2);
	}
	x = 1.0 - cosx;
	ret = r0 + (1.0 - r0) * x * x * x * x * x;
	return (lerpf(f0, 1.0f, ret));
}
