/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:33:16 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/12 16:55:07 by imisumi          ###   ########.fr       */
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
	const float		off_1 = (random_float(rng) - 0.5f) / data->utils.width;
	const float		off_2 = (random_float(rng) - 0.5f) / data->utils.height;

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

float	calculate_falloff(t_vec3f light_pos, t_vec3f surface_point)
{
	const float	distance_squared = powf(light_pos[X] - surface_point[X], 2) + \
							powf(light_pos[Y] - surface_point[Y], 2) + \
							powf(light_pos[Z] - surface_point[Z], 2);

	return (1.0f / powf(distance_squared, 2.0f));
}

float	vec3_cosine_angle(t_vec3f v1, t_vec3f v2)
{
	return (vec3f_dot(v1, v2) / (vec3f_length(v1) * vec3f_length(v2)));
}

bool	simple_sphere_intersection_f(t_rayf ray, t_sphere *sphere, \
	t_hitinfo *hitinfo)
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
			hitinfo->hit = true;
			hitinfo->distance = discriminant;
		}
	}
	return (hitinfo->hit);
}

t_hitinfo	new_hitinfo(void)
{
	const t_hitinfo	hitinfo = {.distance = INFINITY, .hit = false};

	return (hitinfo);
}

//TODO use num chanels instead of 4
t_vec3f	sample_exr_texture(float u, float v, t_hdri *hdri)
{
	t_vec3f	color;
	int		x;
	int		y;
	int		pixel_index;

	u = fmax(0.0f, fmin(1.0f, u));
	v = fmax(0.0f, fmin(1.0f, v));
	x = u * (hdri->width - 1);
	y = v * (hdri->height - 1);
	pixel_index = (x + (hdri->height - 1 - y) * hdri->width) * 4;
	color[X] = hdri->rgba[pixel_index];
	color[Y] = hdri->rgba[pixel_index + 1];
	color[Z] = hdri->rgba[pixel_index + 2];
	return (color);
}

t_vec3f	texture(t_vec3f normal, t_hdri *hdri)
{
	const float		phi = atan2(normal[Z], normal[X]);
	const float		theta = asinf(normal[Y]);
	const float		u = 1.0f - (phi + PI) / TWO_PI;
	const float		v = (theta + PI / 2.0f) / PI;
	const t_vec3f	color = sample_exr_texture(u, v, hdri);

	return (color);
}

float	lerpf(float a, float b, float t)
{
	return (a + (b - a) * t);
}

//	float	fresnel_reflect_amount(float n1, float n2, t_vec3f incident, \
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
