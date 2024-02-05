/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:33:16 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/05 02:47:22 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3f	aa_update_dir(t_data *data, uint32_t *rng, uint32_t x, uint32_t y)
{
	t_vec3f			new_dir;
	const t_vec3f	cam_right_f = {
		data->scene.camera.view.m[0][0], data->scene.camera.view.m[1][0],
		data->scene.camera.view.m[2][0], 0.0f};
	const t_vec3f	cam_up_f = {
		data->scene.camera.view.m[0][1], data->scene.camera.view.m[1][1],
		data->scene.camera.view.m[2][1], 0.0f};
	//? height or width
	const float		off_1 = (randomFloat(rng) - 0.5f) / data->utils.width;
	const float		off_2 = (randomFloat(rng) - 0.5f) / data->utils.height;

	new_dir = data->scene.camera.ray_target[x + y * data->utils.width] + \
				(cam_right_f * off_1) + (cam_up_f * off_2);
	return (vec3f_normalize(new_dir));
}


t_vec3f	default_skyf(t_vec3f direction, t_scene scene)
{
	t_vec3f	sky;
	float	t;

	t = 0.5f * (vec3f_normalize(direction)[Y] + 1.0f);
	sky = ((t_vec3f){0.5f, 0.7f, 1.0f, 0.0f} * (1.0f - t)) + \
			((t_vec3f){1.0f, 1.0f, 1.0f, 0.0f} * t);
	return (sky);
}


float calculateFalloff_f(t_vec3f lightPos, t_vec3f surfacePoint)
{
	float distanceSquared = powf(lightPos[X] - surfacePoint[X], 2) +
							powf(lightPos[Y] - surfacePoint[Y], 2) +
							powf(lightPos[Z] - surfacePoint[Z], 2);
	return 1.0f / powf(distanceSquared, 2.0f);
}

float vec3_cosineAngle_f(t_vec3f v1, t_vec3f v2)
{
	return vec3f_dot(v1, v2) / (vec3f_length(v1) * vec3f_length(v2));
}

bool	simple_sphere_intersection_f(t_rayf ray, t_sphere *sphere, t_hitinfo *hitinfo)
{
	const		t_vec3f	offset_origin = ray[ORIGIN] - sphere->pos_f;
	const float	a = vec3f_dot(ray[DIR], ray[DIR]);
	const float	b = 2.0f * vec3f_dot(offset_origin, ray[DIR]);
	const float	c = vec3f_dot(offset_origin, offset_origin) - sphere->radius * sphere->radius;
	float		discriminant;

	discriminant = b * b - 4 * a * c;
	if (discriminant >= 0.0f)
	{
		float	discriminant = (-b - sqrtf(discriminant)) / (2.0f * a);
		if (discriminant > 0.0f && discriminant < hitinfo->distance)
		{
			hitinfo->hit = true;
			hitinfo->distance = discriminant;
		}
	}
	return (hitinfo->hit);
}

t_hitinfo	new_hitinfo()
{
	const t_hitinfo hitinfo = {.distance = INFINITY, .hit = false};

	return (hitinfo);
}

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
		
		// light = single_sphere_intersection_f(shadow_ray, sphere, shadow_hit);
		simple_sphere_intersection_f(shadow_ray, &sphere, &shadow_hit);
		if (light.distance != shadow_hit.distance && light.distance < shadow_hit.distance)
		{
			float	distance_to_light = vec3f_distance(closest_hit.position, sphere.pos_f);
			float cosine = vec3_cosineAngle_f(closest_hit.normal, shadow_ray[DIR]);
			if (cosine > 0.0f)
			{
				float attenuation = cosine / (distance_to_light * distance_to_light);
				float falloff = calculateFalloff_f(sphere.pos_f, closest_hit.position);
				float intensity = cosine * attenuation * scene->point_lights[i].intensity;;

				diffuse_contribution_f += (scene->point_lights[i].color * intensity);
			}
		}
		i++;
	}
	return (diffuse_contribution_f);
}

t_vec3f	sampleEXRTexture(float u, float v, t_hdri hdri)
{
	t_vec3f	color;
	int width = hdri.width;
	int height = hdri.height;
	
	// Clamp texture coordinates to the valid range [0, 1]
	u = fmax(0.0f, fmin(1.0f, u));
	v = fmax(0.0f, fmin(1.0f, v));
	
	// Calculate pixel coordinates in the EXR texture
	int x = u * (width - 1);
	int y = v * (height - 1);
	
	int	pixelIndex = (x + (height - 1 - y) * width) * 4;

	color[X] = hdri.rgba[pixelIndex + 0];
	color[Y] = hdri.rgba[pixelIndex + 1];
	color[Z] = hdri.rgba[pixelIndex + 2];
	return (color);
}

t_vec3f	texture(t_vec3f normal, t_hdri hdri)
{
	const float		phi = atan2(normal[Z], normal[X]);
	const float		theta = asinf(normal[Y]);
	const float		u = 1.0f - (phi + PI) / TWO_PI;
	const float		v = (theta + PI / 2.0f) / PI;
	const t_vec3f	color = sampleEXRTexture(u, v, hdri);

	return (color);
}

float	lerpf(float a, float b, float t)
{
	return (a + (b - a) * t);
}

// float	fresnel_reflect_amount(float n1, float n2, t_vec3f incident, \
	t_vec3f normal, float f0, float f90)
// float cosX = -vec3f_dot(normal, incident);
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
		cosx = sqrtf(1.0-sin_t2);
	}
	x = 1.0 - cosx;
	ret = r0 + (1.0 - r0) * x * x * x * x * x;
	return (lerpf(f0, 1.0f, ret));
}