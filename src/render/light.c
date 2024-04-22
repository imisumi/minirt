/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:33:16 by ichiro            #+#    #+#             */
/*   Updated: 2024/04/22 20:02:46 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	vec3_cosine_angle(t_vec3f v1, t_vec3f v2)
{
	return (vec3f_dot(v1, v2) / (vec3f_length(v1) * vec3f_length(v2)));
}

static void	calculate_lighting(t_hitinfo *hitinfo, t_scene *scene, \
	t_light_utils *u)
{
	float		attenuation;
	float		intensity;
	const float	distance_to_light = vec3f_distance(hitinfo->position, \
		u->sphere.pos_f);
	const float	cosine = vec3_cosine_angle(hitinfo->normal, u->shadow_ray[DIR]);

	if (cosine > 0.0f)
	{
		attenuation = cosine / (distance_to_light * distance_to_light);
		intensity = cosine * attenuation * scene->point_lights[u->i].intensity;
		u->diffuse_contribution += (scene->point_lights[u->i].color * \
			intensity);
	}
}

static bool	simple_sphere_intersection_f(t_rayf ray, t_sphere *sphere, \
	t_hitinfo *hitinfo, t_hitinfo *light)
{
	const t_vec3f	offset_origin = ray[ORIGIN] - sphere->pos_f;
	const float		a = vec3f_dot(ray[DIR], ray[DIR]);
	const float		b = 2.0f * vec3f_dot(offset_origin, ray[DIR]);
	const float		c = vec3f_dot(offset_origin, offset_origin) - \
		sphere->radius * sphere->radius;
	float			discriminant;

	discriminant = b * b - 4 * a * c;
	if (discriminant >= 0.0f)
	{
		discriminant = (-b - sqrtf(discriminant)) / (2.0f * a);
		if (discriminant > EPSILON && discriminant < hitinfo->distance)
		{
			light->hit = true;
			light->distance = discriminant;
		}
	}
	return (light->hit);
}

t_vec3f	omni_dir_light_f(t_rayf ray, t_scene *scene, t_hitinfo hitinfo)
{
	t_light_utils	u;

	ft_memset(&u, 0, sizeof(t_light_utils));
	u.sphere.radius = 0.01f;
	while (u.i < vec_length(&scene->point_lights))
	{
		u.light = new_hitinfo();
		u.shadow_hit = new_hitinfo();
		u.sphere.pos_f = scene->point_lights[u.i].position;
		u.shadow_ray[ORIGIN] = ray[ORIGIN];
		u.shadow_ray[DIR] = vec3f_normalize(u.sphere.pos_f - hitinfo.position);
		u.shadow_hit = sphere_bvh_intersection_f(u.shadow_ray, scene->spheres, \
			u.shadow_hit, scene->bvh_spheres_f);
		inv_plane_intersection_f(u.shadow_ray, scene, &u.shadow_hit);
		simple_sphere_intersection_f(u.shadow_ray, &u.sphere, \
			&u.shadow_hit, &u.light);
		if (u.light.distance != u.shadow_hit.distance && \
			u.light.distance < u.shadow_hit.distance)
		{
			calculate_lighting(&hitinfo, scene, &u);
		}
		u.i++;
	}
	return (u.diffuse_contribution);
}
