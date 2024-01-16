/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:33:16 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/15 21:30:02 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_vec4f vec4f_clamp(t_vec4f vec, float min, float max)
{
	vec[X] = fmaxf(min, fminf(max, vec[X]));
	vec[Y] = fmaxf(min, fminf(max, vec[Y]));
	vec[Z] = fmaxf(min, fminf(max, vec[Z]));
	vec[W] = fmaxf(min, fminf(max, vec[W]));
	return (vec);
}

t_vec3f	vec3f_pow(t_vec3f vec, float exp)
{
	vec[X] = powf(vec[X], exp);
	vec[Y] = powf(vec[Y], exp);
	vec[Z] = powf(vec[Z], exp);
	vec[W] = powf(vec[W], exp);
	return (vec);
}

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

t_vec3f	vec3f_less_than(t_vec3f vec, float value)
{
	vec[X] = vec[X] < value ? vec[X] : value;
	vec[Y] = vec[Y] < value ? vec[Y] : value;
	vec[Z] = vec[Z] < value ? vec[Z] : value;
	vec[W] = vec[W] < value ? vec[W] : value;
	return (vec);
}

t_vec4f LessThan_vec4f(t_vec4f v, t_vec4f threshold) {
    t_vec4f result;
    result[X] = v[X] < threshold[X] ? 1.0f : 0.0f;
    result[Y] = v[Y] < threshold[Y] ? 1.0f : 0.0f;
    result[Z] = v[Z] < threshold[Z] ? 1.0f : 0.0f;
    result[W] = v[W] < threshold[W] ? 1.0f : 0.0f;
    return result;
}

t_vec4f mix_vec4f(t_vec4f x, t_vec4f y, t_vec4f mask)
{
    t_vec4f result;
    result[X] = mask[X] * y[X] + (1.0f - mask[X]) * x[X];
    result[Y] = mask[Y] * y[Y] + (1.0f - mask[Y]) * x[Y];
    result[Z] = mask[Z] * y[Z] + (1.0f - mask[Z]) * x[Z];
    result[W] = mask[W] * y[W] + (1.0f - mask[W]) * x[W];
    return result;
}

t_vec3f LinearToSRGB(t_vec3f rgb)
{
    rgb = vec4f_clamp(rgb, 0.0f, 1.0f);

    t_vec3f condition = {0.0031308f, 0.0031308f, 0.0031308f};
    t_vec3f pow_result = vec3f_pow(rgb, 1.0f / 2.4f);
    
    t_vec3f mix_result = mix_vec4f(
        pow_result * 1.055f - 0.055f,
        rgb * 12.92f,
        LessThan_vec4f(rgb, condition)
    );

    return mix_result;
}

t_vec4f	ACESFilm(t_vec4f x)
{
    float a = 2.51f;
    float b = 0.03f;
    float c = 2.43f;
    float d = 0.59f;
    float e = 0.14f;

    t_vec4f numerator = {x[X] * (a * x[X] + b), x[Y] * (a * x[Y] + b), x[Z] * (a * x[Z] + b), x[W] * (a * x[W] + b)};
    t_vec4f denominator = {x[X] * (c * x[X] + d) + e, x[Y] * (c * x[Y] + d) + e, x[Z] * (c * x[Z] + d) + e, x[W] * (c * x[W] + d) + e};

    t_vec4f result;
    result[X] = numerator[X] / denominator[X];
    result[Y] = numerator[Y] / denominator[Y];
    result[Z] = numerator[Z] / denominator[Z];
    result[W] = numerator[W] / denominator[W];

    // Clamp the result to the range [0.0, 1.0]
    result[X] = fmax(0.0f, fmin(1.0f, result[X]));
    result[Y] = fmax(0.0f, fmin(1.0f, result[Y]));
    result[Z] = fmax(0.0f, fmin(1.0f, result[Z]));
    result[W] = fmax(0.0f, fmin(1.0f, result[W]));

	result[W] = 1.0f;

    return result;
}

t_vec4f	vec3f_tone_map(t_vec3f color)
{
	color = ACESFilm(color);
	color = LinearToSRGB(color);
	color[W] = 1.0f;
	return color;
	float	gamma = 2.2f;
	float	exposure = 1.0f;
	color = color * exposure;
	t_vec3f	result = color / (color + 1.0f);
	// t_vec3 result;

	// result[X] = 1.0f - expf(-color[R] * exposure);
	// result[Y] = 1.0f - expf(-color[G] * exposure);
	// result[Z] = 1.0f - expf(-color[B] * exposure);

	result[X] = powf(result[X], 1.0f / gamma);
	result[Y] = powf(result[Y], 1.0f / gamma);
	result[Z] = powf(result[Z], 1.0f / gamma);
	return((t_vec4f){result[X], result[Y], result[Z], 1.0f});
	// return (vec4_new(result.x, result.y, result.z, 1.0f));
}






// t_vec4f	linear_to_srgb(t_vec4f color)
// {
// 	color = vec4f_clamp(color, 0.0f, 1.0f);
// 	return	vec3f_lerp(
// 		vec3f_pow(((color + 0.055f) / 1.055f), 2.4f),
// 		color / 12.92f,
// 		vec3f_less_than(color, 0.04045f));

// 	// return	vec3f_lerp(
// 	// 	vec3f_pow(((color + 0.055f) / 1.055f), 2.4f),
// 	// 	color / 12.92f,
// 	// 	vec3f_less_than(color, 0.04045f)
// 	// );
// }

// t_vec4f	ACESFilm(t_vec4f x)
// {
// 	float a = 2.51f;
// 	float b = 0.03f;
// 	float c = 2.43f;
// 	float d = 0.59f;
// 	float e = 0.14f;
// 	return clamp((x*(a*x + b)) / (x*(c*x + d) + e), 0.0f, 1.0f);
// }




t_vec3f	default_skyf(t_vec3f direction, t_scene scene)
{
	t_vec3f	sky;
	float	t;

	t = 0.5f * (vec3f_normalize(direction)[Y] + 1.0f);
	sky = ((t_vec3f){0.5f, 0.7f, 1.0f, 0.0f} * (1.0f - t)) + \
			((t_vec3f){1.0f, 1.0f, 1.0f, 0.0f} * t);
	return (sky);
}

float vec3f_distance(t_vec3f point1, t_vec3f point2)
{
	const t_vec3f v = point2 - point1;

	return (sqrtf(v[X] * v[X] + v[Y] * v[Y] + v[Z] * v[Z]));
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


// t_vec3f omni_dir_light_f(t_rayf ray, t_scene scene, t_hitinfo closest_hit)
// {
// 	t_sphere sphere;
// 	// sphere.position = vec3_new(6.0f, 2.0f, -6.0f);
// 	sphere.pos_f = (t_vec3f){6.0f, 2.0f, -6.0f, 0.0f};
// 	sphere.pos_f = scene.point_lights[0].position;
// 	sphere.radius = 0.01f;
	
// 	t_rayf shadow;
// 	shadow[ORIGIN] = ray[ORIGIN];
// 	// t_vec3 light_dir = vec3_normalize(vec3_sub(sphere.position, closest_hit.position));
// 	t_vec3f light_dir = vec3f_normalize(sphere.pos_f - closest_hit.position);
// 	shadow[DIR] = light_dir;
	
// 	// float distance_to_light = vec3_distance(closest_hit.position, sphere.position);
// 	float distance_to_light = vec3f_distance(closest_hit.position, sphere.pos_f);

// 	float light_intensity = 500.0f;
// 	light_intensity = scene.point_lights[0].intensity;
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

t_hitinfo	simple_sphere_intersection_f(t_rayf ray, t_sphere sphere, t_hitinfo hitinfo)
{
	const		t_vec3f	offset_origin = ray[ORIGIN] - sphere.pos_f;
	const float	a = vec3f_dot(ray[DIR], ray[DIR]);
	const float	b = 2.0f * vec3f_dot(offset_origin, ray[DIR]);
	const float	c = vec3f_dot(offset_origin, offset_origin) - sphere.radius * sphere.radius;
	float		discriminant;

	discriminant = b * b - 4 * a * c;
	if (discriminant >= 0.0f)
	{
		float	discriminant = (-b - sqrtf(discriminant)) / (2.0f * a);
		if (discriminant > 0.0f && discriminant < hitinfo.distance)
		{
			hitinfo.hit = true;
			hitinfo.distance = discriminant;
		}
	}
	return (hitinfo);
}

t_hitinfo	new_hitinfo()
{
	const t_hitinfo hitinfo = {.distance = INFINITY, .hit = false};

	return (hitinfo);
}

t_vec3f omni_dir_light_f(t_rayf ray, t_scene scene, t_hitinfo closest_hit)
{
	t_sphere sphere;
	sphere.radius = 0.01f;
	// sphere.radius = 1.0f;
	int	i;

	t_rayf		shadow_ray;
	t_vec3f		diffuse_contribution_f;
	t_hitinfo	light;
	t_hitinfo	shadow_hit;

	
	i = 0;
	diffuse_contribution_f = (t_vec3f){0.0f, 0.0f, 0.0f, 0.0f};
	while (i < array_length(&scene.point_lights))
	{
		light = new_hitinfo();
		shadow_hit = new_hitinfo();
		
		sphere.pos_f = scene.point_lights[i].position;
		shadow_ray[ORIGIN] = ray[ORIGIN];
		shadow_ray[DIR] = vec3f_normalize(sphere.pos_f - closest_hit.position);

		shadow_hit = sphere_bvh_intersection_f(shadow_ray, scene.spheres, shadow_hit, scene.bvh_spheres_f);
		shadow_hit = inv_plane_intersection_f(shadow_ray, scene, shadow_hit);
		
		// light = single_sphere_intersection_f(shadow_ray, sphere, shadow_hit);
		light = simple_sphere_intersection_f(shadow_ray, sphere, shadow_hit);
		if (light.distance != shadow_hit.distance && light.distance < shadow_hit.distance)
		{
			float	distance_to_light = vec3f_distance(closest_hit.position, sphere.pos_f);
			float cosine = vec3_cosineAngle_f(closest_hit.normal, shadow_ray[DIR]);
			if (cosine > 0.0f)
			{
				float attenuation = cosine / (distance_to_light * distance_to_light);
				float falloff = calculateFalloff_f(sphere.pos_f, closest_hit.position);
				float intensity = cosine * attenuation * scene.point_lights[i].intensity;;

				diffuse_contribution_f += (scene.point_lights[i].color * intensity);
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
	
	// Get the pixel value from the EXR texture
	// int pixelIndex = (y * width + x) * 4; // Each pixel has 4 float components (RGBA)
	int	pixelIndex = (x + (height - 1 - y) * width) * 4;
	// float brightness = 0.3f * rgba[pixelIndex] + 0.59f * rgba[pixelIndex + 1] + 0.11f * rgba[pixelIndex + 2];
	
	color[X] = hdri.rgba[pixelIndex + 0];
	color[Y] = hdri.rgba[pixelIndex + 1];
	color[Z] = hdri.rgba[pixelIndex + 2];

	return color;
}

t_vec3f	texture(t_vec3f normal, t_hdri hdri)
{
	t_vec3f	color;
	float u;
	float v;

	// u = 0.5f + atan2(normal.z, normal.x) / (TWO_PI);
	// v = 0.5f - asinf(normal.y) / PI;

	float phi = atan2(normal[Z], normal[X]);
	float theta = asinf(normal[Y]);
	u = 1.0f - (phi + PI) / TWO_PI;
	v = (theta + PI / 2.0f) / PI;
	color = sampleEXRTexture(u, v, hdri);
	return (color);
}
