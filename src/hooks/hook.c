/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:23:41 by ichiro            #+#    #+#             */
/*   Updated: 2023/12/20 22:23:50 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

uint32_t	global_frame = 1;


t_vec3	default_sky(t_vec3 direction, t_scene scene)
{
	t_vec3	sky;
	float	t;

	t = 0.5f * (vec3_normalize(direction).y + 1.0f);
	// sky = vec3_add(vec3_mulf((t_vec3){1.0f, 1.0f, 1.0f}, 1.0f - t), \
	// 				vec3_mulf((t_vec3){0.5f, 0.7f, 1.0f}, t));
	sky = vec3_add(vec3_mulf((t_vec3){0.5f, 0.7f, 1.0f}, 1.0f - t), \
					vec3_mulf((t_vec3){1.0f, 1.0f, 1.0f}, t));
	return (sky);
}

t_vec3	calc_onmi_light(t_vec3 point, t_vec3 normal, t_omnidirectional_light light)
{
	t_vec3 lightDirection = vec3_normalize(vec3_sub(light.position, point));

	float diffuse_factor = vec3_dot(normal, lightDirection);
	diffuse_factor = fmaxf(diffuse_factor, 0.0f);
	t_vec3 diffuse = vec3_mulf(light.color, diffuse_factor * light.intensity);
	return (diffuse);
}

// t_vec3	calc_dls(t_hitinfo hitinfo)
// {
// 	t_sphere sphere;
// 	sphere.position = vec3_new(5.0f, 2.0f, -5.0f);
// 	sphere.radius = 0.01f;

// 	t_vec3	light_dir = vec3_normalize(vec3_sub(sphere.position, hitinfo.position));
// 	float distance = vec3_length(vec3_sub(sphere.position, hitinfo.position));
// }

// t_vec3	omni_dir_light(t_ray ray, t_scene scene, t_hitinfo closest_hit)
// {
// 	t_sphere sphere;
// 	sphere.position = vec3_new(6.0f, 2.0f, -6.0f);

// 	t_ray shadow;
// 	shadow.origin = ray.origin;
// 	t_vec3	light_dir = vec3_normalize(vec3_sub(sphere.position, ray.origin));
// 	shadow.direction = light_dir;

// 	float diffuse_intensity = fmaxf(vec3_dot(closest_hit.normal, light_dir), 0.0f);
// 	t_vec3 diffuse_contribution = vec3_mulf(vec3_new(1.0f, 1.0f, 1.0f), diffuse_intensity * 1.0f);

// 	t_hitinfo shadow_hit;
// 	shadow_hit.distance = INFINITY;
// 	shadow_hit.hit = false;
	
// 	shadow_hit = sphere_intersection(shadow, scene, shadow_hit);
// 	shadow_hit = inv_plane_intersection(shadow, scene, shadow_hit);
	
// 	t_hitinfo light = single_sphere_intersection(shadow, sphere, shadow_hit);
	
// 	if (light.hit && light.distance < shadow_hit.distance)
// 		return (diffuse_contribution);
// 	return ((t_vec3){0.0f, 0.0f, 0.0f});
// }


// float vec3_cosineAngle_f(t_vec3f v1, t_vec3f v2)
// {
// 	return vec3f_dot(v1, v2) / (vec3f_length(v1) * vec3f_length(v2));
// }

float calculateFalloff(t_vec3 lightPos, t_vec3 surfacePoint) {
    float distanceSquared = powf(lightPos.x - surfacePoint.x, 2) +
                            powf(lightPos.y - surfacePoint.y, 2) +
                            powf(lightPos.z - surfacePoint.z, 2);
    return 1.0f / powf(distanceSquared, 2.0f);
}


//! goood
// t_vec3 omni_dir_light(t_ray ray, t_scene scene, t_hitinfo closest_hit)
// {
// 	t_sphere sphere;
// 	sphere.position = vec3_new(6.0f, 2.0f, -6.0f);
// 	sphere.radius = 0.01f;
	
// 	t_ray shadow;
// 	shadow.origin = ray.origin;
// 	t_vec3 light_dir = vec3_normalize(vec3_sub(sphere.position, closest_hit.position));
// 	shadow.direction = light_dir;
	
// 	float distance_to_light = vec3_distance(closest_hit.position, sphere.position);

// 	float light_intensity = 300.0f;
// 	float cosine = vec3_cosineAngle(closest_hit.normal, light_dir);
// 	if (cosine <= 0.0f)
// 		return ((t_vec3){0.0f, 0.0f, 0.0f});
// 	float attenuation = cosine / (distance_to_light * distance_to_light);
// 	float falloff = calculateFalloff(sphere.position, closest_hit.position);
// 	float intensity = cosine * attenuation * light_intensity;
// 	t_vec3 diffuse_contribution = vec3_mulf(vec3_new(1.0f, 1.0f, 1.0f), intensity);
	
// 	t_hitinfo shadow_hit;
// 	shadow_hit.distance = INFINITY;
// 	shadow_hit.hit = false;
	
// 	shadow_hit = sphere_intersection(shadow, scene, shadow_hit);
// 	shadow_hit = inv_plane_intersection(shadow, scene, shadow_hit);
	
// 	t_hitinfo light = single_sphere_intersection(shadow, sphere, shadow_hit);
	
// 	if (light.hit && light.distance < shadow_hit.distance)
// 		return (diffuse_contribution);
// 	return ((t_vec3){0.0f, 0.0f, 0.0f});
// }

// float vec3f_distance(t_vec3f point1, t_vec3f point2)
// {
// 	const t_vec3f v = point2 - point1;

// 	return (sqrtf(v[X] * v[X] + v[Y] * v[Y] + v[Z] * v[Z]));
// }

// t_vec3f omni_dir_light_f(t_rayf ray, t_scene scene, t_hitinfo closest_hit)
// {
// 	t_sphere sphere;
// 	// sphere.position = vec3_new(6.0f, 2.0f, -6.0f);
// 	sphere.pos_f = (t_vec3f){6.0f, 2.0f, -6.0f, 0.0f};
// 	sphere.radius = 0.01f;
	
// 	t_rayf shadow;
// 	shadow[ORIGIN] = ray[ORIGIN];
// 	// t_vec3 light_dir = vec3_normalize(vec3_sub(sphere.position, closest_hit.position));
// 	t_vec3f light_dir = vec3f_normalize(sphere.pos_f - closest_hit.position);
// 	shadow[DIR] = light_dir;
	
// 	// float distance_to_light = vec3_distance(closest_hit.position, sphere.position);
// 	float distance_to_light = vec3f_distance(closest_hit.position, sphere.pos_f);

// 	float light_intensity = 500.0f;
// 	// float cosine = vec3_cosineAngle(closest_hit.normal, light_dir);
// 	float cosine = vec3_cosineAngle_f(closest_hit.normal, light_dir);
// 	if (cosine <= 0.0f)
// 		return ((t_vec3f){0});
// 	float attenuation = cosine / (distance_to_light * distance_to_light);
// 	float falloff = calculateFalloff_f(sphere.pos_f, closest_hit.position);
// 	float intensity = cosine * attenuation * light_intensity;
// 	// t_vec3 diffuse_contribution = vec3_mulf(vec3_new(1.0f, 1.0f, 1.0f), intensity);
// 	t_vec3f diffuse_contribution_f = (t_vec3f){1.0f, 1.0f, 1.0f, 0.0f} * intensity;
	
// 	t_hitinfo shadow_hit;
// 	shadow_hit.distance = INFINITY;
// 	shadow_hit.hit = false;
	
// 	// shadow_hit = sphere_intersection(shadow, scene, shadow_hit);
// 	// shadow_hit = inv_plane_intersection(shadow, scene, shadow_hit);

// 	// shadow_hit = sphere_intersection_f(shadow, scene, shadow_hit);
// 	shadow_hit = sphere_bvh_intersection_f(shadow, scene.spheres, shadow_hit, scene.bvh_spheres_f);
// 	shadow_hit = inv_plane_intersection_f(shadow, scene, shadow_hit);
	
// 	// t_hitinfo light = single_sphere_intersection(shadow, sphere, shadow_hit);
// 	t_hitinfo light = single_sphere_intersection_f(shadow, sphere, shadow_hit);
	
// 	if (light.hit && light.distance < shadow_hit.distance)
// 		return (diffuse_contribution_f);
// 	// return ((t_vec3){0.0f, 0.0f, 0.0f});
// 	return ((t_vec3f){0.0f, 0.0f, 0.0f, 0.0f});
// }



bool	render_zone(t_data *data)
{
	t_thread	zone;

	if (data->utils.accumulated_frames == 1)
		ft_memset(data->utils.accumulated_data, 0, sizeof(t_vec4f) * data->utils.width * data->utils.height);
	if (MT)
	{
		if (create_thread(data) == false)
			return (false);
	}
	else
	{
		zone.x_start = 0;
		zone.x_end = data->utils.width;
		zone.y_start = 0;
		zone.y_end = data->utils.height;
		zone.data = data;
		render(&zone);
	}
	return (true);
}

void	frame_times(void *param)
{
	t_data	*data;

	data = param;
	double currentTime = glfwGetTime();
	double deltaTime = currentTime - data->utils.prev_frame;
	double frameTimeMs = deltaTime * 1000.0;
	double fps = 1000.0 / frameTimeMs;
	// printf("\rframeTimeMs: %.2f ms    frames: %d", frameTimeMs, global_frame);
	char output[50];
	snprintf(output, 50, "%.2f", fps);
	mlx_set_window_title(data->mlx, output);
	fflush(stdout);
}

void	render_loop(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		return mlx_close_window(data->mlx);
	resize_window(param);
	movement(data);
	if (render_zone(data) == false)
		exit(EXIT_FAILURE);
	frame_times(param);
	// if (AA)
		// anti_aliasing(data);
	if (global_frame % 100 == 0)
	{
		screenshot(data);
	}
	data->utils.accumulated_frames++;
	global_frame++;
}
