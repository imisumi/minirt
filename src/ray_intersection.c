/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/07/14 01:16:08 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../lib/ft_math/includes/math.h"
# include "../includes/scene.h"

t_vec3 hit_position(t_ray r, float t);

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
				t_vec3 intersection_point = hit_position(ray, t);
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
					bool entersFromOpposite = vec3_dot(ray.direction, s.planes[i].normal) > 0.0f;
					if (entersFromOpposite)
						 continue;  // Ignore the intersection
					obj_hit.hit = true;
					obj_hit.hit_distance = t;
					obj_hit.position = hit_position(ray, t);
					// obj_hit.normal = vec3_normalize(vec3_sub(obj_hit.position, s.planes[i].position));
					obj_hit.normal = s.planes[i].normal;
					obj_hit.material = s.planes[i].material;
				}
			}
		}
	}
	return (obj_hit);
}

t_obj_hit sphere_intersection(t_ray ray, t_scene s, t_obj_hit obj_hit)
{
	for (int i = 0; i < s.nb_spheres; i++)
	{
		t_vec3 origin = vec3_sub(ray.origin, s.spheres[i].center);
		
		float a = vec3_dot(ray.direction, ray.direction);
		float b = 2.0 * vec3_dot(origin, ray.direction);
		float c = vec3_dot(origin, origin) - (s.spheres[i].radius * s.spheres[i].radius);

		float discriminant = (b * b) - (4 * a * c);
		if (discriminant < 0.0f)
			continue;

		float closest_hit = (-b - sqrtf(discriminant)) / (2.0 * a);
		if (closest_hit > 0.0f && closest_hit < obj_hit.hit_distance )
		{
			obj_hit.hit = true;
			obj_hit.hit_distance  = closest_hit;
			obj_hit.position = hit_position(ray, closest_hit);
			obj_hit.normal = vec3_normalize(vec3_sub(obj_hit.position, s.spheres[i].center));
			// obj_hit.material.albedo = s.spheres[i].material.albedo;
			obj_hit.material = s.spheres[i].material;
		}
	}
	return (obj_hit);
}
