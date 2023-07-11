/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/07/10 23:07:55 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_obj_hit plane_intersection(t_ray ray, t_scene s, t_obj_hit obj_hit)
{
	for (int i = 0; i < s.nb_planes; i++)
	{
		float denom = vec3_dot(ray.direction, s.planes[i].normal);
		if (fabs(denom) > 1e-6)
		{
			t_vec3 p0l0 = vec3_sub(s.planes[i].position, ray.origin);
			float t = vec3_dot(p0l0, s.planes[i].normal) / denom;
			if (t < 0.0f)
				continue;
			
			if (t < obj_hit.hit_distance)
			{
				t_vec3 intersection_point = point_at_parameter(ray, t);
				float half_width = s.planes->width / 2.0f;
				float half_height = s.planes->height / 2.0f;
				
				// Check if the intersection point lies within the plane's limits
				if (intersection_point.x >= (s.planes[i].position.x - half_width) &&
					intersection_point.x <= (s.planes[i].position.x + half_width) &&
					intersection_point.y >= (s.planes[i].position.y - half_height) &&
					intersection_point.y <= (s.planes[i].position.y + half_height) &&
					intersection_point.z >= (s.planes[i].position.z - half_height) &&
					intersection_point.z <= (s.planes[i].position.z + half_height))
				{
					obj_hit.hit = true;
					obj_hit.hit_distance = t;
					obj_hit.position = point_at_parameter(ray, t);
					// obj_hit.normal = vec3_normalize(vec3_sub(obj_hit.position, s.planes[i].position));
					obj_hit.normal = s.planes[i].normal;
					obj_hit.material = s.planes[i].material;
				}
			}
		}
	}
	return (obj_hit);
}