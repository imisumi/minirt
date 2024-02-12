/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:33:16 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/12 16:51:06 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3f omni_dir_light_f(t_rayf ray, t_scene *scene, t_hitinfo closest_hit)
{
	t_sphere sphere;
	sphere.radius = 0.01f;
	int	i;

	t_rayf		shadow_ray;
	t_vec3f		diffuse_contribution_f;
	t_hitinfo	light;
	t_hitinfo	shadow_hit;

	
	i = 0;
	diffuse_contribution_f = (t_vec3f){0.0f, 0.0f, 0.0f, 0.0f};
	while (i < vec_length(&scene->point_lights))
	{
		light = new_hitinfo();
		shadow_hit = new_hitinfo();
		
		sphere.pos_f = scene->point_lights[i].position;
		shadow_ray[ORIGIN] = ray[ORIGIN];
		shadow_ray[DIR] = vec3f_normalize(sphere.pos_f - closest_hit.position);

		shadow_hit = sphere_bvh_intersection_f(shadow_ray, scene->spheres, shadow_hit, scene->bvh_spheres_f);
		inv_plane_intersection_f(shadow_ray, scene, &shadow_hit);
		
		simple_sphere_intersection_f(shadow_ray, &sphere, &shadow_hit);
		if (light.distance != shadow_hit.distance && light.distance < shadow_hit.distance)
		{
			float	distance_to_light = vec3f_distance(closest_hit.position, sphere.pos_f);
			float cosine = vec3_cosine_angle(closest_hit.normal, shadow_ray[DIR]);
			if (cosine > 0.0f)
			{
				float attenuation = cosine / (distance_to_light * distance_to_light);
				float falloff = calculate_falloff(sphere.pos_f, closest_hit.position);
				float intensity = cosine * attenuation * scene->point_lights[i].intensity;;

				diffuse_contribution_f += (scene->point_lights[i].color * intensity);
			}
		}
		i++;
	}
	return (diffuse_contribution_f);
}