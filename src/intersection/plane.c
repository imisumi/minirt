/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:36:28 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/13 19:21:28 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	inv_plane_intersection_f(t_rayf ray, t_scene *s, t_hitinfo *hitinfo)
{
	int		i;
	float	t;
	float	demon;
	t_vec3f	offset_origin;

	i = 0;
	while (i < vec_length(&s->inv_planes))
	{
		demon = vec3f_dot(s->inv_planes[i].normal, ray[DIR]);
		if (fabs(demon) > EPSILON)
		{
			offset_origin = s->inv_planes[i].position - ray[ORIGIN];
			t = vec3f_dot(offset_origin, s->inv_planes[i].normal) / demon;
			if (t >= EPSILON && t < hitinfo->distance)
			{
				hitinfo->hit = true;
				hitinfo->distance = t;
				hitinfo->position = ray[ORIGIN] + (ray[DIR] * t);
				hitinfo->normal = s->inv_planes[i].normal;
				hitinfo->material = s->inv_planes[i].material;
			}
		}
		i++;
	}
	return (hitinfo->hit);
}
