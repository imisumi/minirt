/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:23:41 by ichiro            #+#    #+#             */
/*   Updated: 2023/12/12 18:42:22 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}
uint32_t	global_frame = 1;

t_vec3	default_sky(t_vec3 direction)
{
	t_vec3	sky;
	float	t;

	t = 0.5f * (vec3_normalize(direction).y + 1.0f);
	// sky = vec3_add(vec3_mulf((t_vec3){1.0f, 1.0f, 1.0f}, 1.0f - t), \
	// 				vec3_mulf((t_vec3){0.5f, 0.7f, 1.0f}, t));
	sky = vec3_add(vec3_mulf((t_vec3){0.5f, 0.7f, 1.0f}, 1.0f - t), \
					vec3_mulf((t_vec3){1.0f, 1.0f, 1.0f}, t));
	sky = vec3_new(1.0f, 1.0f, 1.0f);
	// sky = vec3_mulf(sky, 0.5f);
	return ((t_vec3){0.0f, 0.0f, 0.0f});
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

float vec3_distance(t_vec3 point1, t_vec3 point2) {
    float dx = point2.x - point1.x;
    float dy = point2.y - point1.y;
    float dz = point2.z - point1.z;

    return sqrtf(dx * dx + dy * dy + dz * dz);
}

float calculateIntensity(float distance, float intensityAtSource) {
    // Apply inverse square law falloff
    return intensityAtSource / (distance * distance);
}

float calc_quad_intensity(float distance, float q, float threshold)
{
	float intesity = 1.0f / (1.0f + q * distance * distance);
    return fmaxf(intesity, threshold);
}

float	calc_int(float distance, float intensity)
{
	return 1.0f / (distance * distance);
}

float vec3_cosineAngle(t_vec3 v1, t_vec3 v2) {
    return vec3_dot(v1, v2) / (vec3_length(v1) * vec3_length(v2));
}

float calculateFalloff(t_vec3 lightPos, t_vec3 surfacePoint) {
    float distanceSquared = powf(lightPos.x - surfacePoint.x, 2) +
                            powf(lightPos.y - surfacePoint.y, 2) +
                            powf(lightPos.z - surfacePoint.z, 2);
    return 1.0f / powf(distanceSquared, 2.0f);
}

t_vec3 omni_dir_light(t_ray ray, t_scene scene, t_hitinfo closest_hit)
{
	t_sphere sphere;
	sphere.position = vec3_new(6.0f, 2.0f, -6.0f);
	sphere.radius = 0.01f;
	
	t_ray shadow;
	shadow.origin = ray.origin;
	t_vec3 light_dir = vec3_normalize(vec3_sub(sphere.position, closest_hit.position));
	shadow.direction = light_dir;
	
	float distance_to_light = vec3_distance(closest_hit.position, sphere.position);
	float falloff_factor = calculateIntensity(distance_to_light, 10.0f);
	falloff_factor = calc_quad_intensity(distance_to_light, 10.0f, 0.1f);
	
	// falloff_factor = 10.f / distance_to_light;
	// falloff_factor = 1.0f / distance_to_light;
	// falloff_factor = exp(-1.0f * distance_to_light);
	
	float diffuse_intensity = fmaxf(vec3_dot(closest_hit.normal, light_dir), 0.0f);
	diffuse_intensity = vec3_dot(closest_hit.normal, light_dir);
	float intensity_with_falloff = falloff_factor * diffuse_intensity;
	
	t_vec3 diffuse_contribution = vec3_mulf(vec3_new(1.0f, 1.0f, 1.0f), intensity_with_falloff);

	float light_intensity = 300.0f;
	float cosine = vec3_cosineAngle(closest_hit.normal, light_dir);
	if (cosine <= 0.0f)
		return ((t_vec3){0.0f, 0.0f, 0.0f});
	float attenuation = cosine / (distance_to_light * distance_to_light);
	float falloff = calculateFalloff(sphere.position, closest_hit.position);
	float intensity = cosine * attenuation * light_intensity;
	diffuse_contribution = vec3_mulf(vec3_new(1.0f, 1.0f, 1.0f), intensity);
	
	t_hitinfo shadow_hit;
	shadow_hit.distance = INFINITY;
	shadow_hit.hit = false;
	
	shadow_hit = sphere_intersection(shadow, scene, shadow_hit);
	shadow_hit = inv_plane_intersection(shadow, scene, shadow_hit);
	
	t_hitinfo light = single_sphere_intersection(shadow, sphere, shadow_hit);
	
	if (light.hit && light.distance < shadow_hit.distance)
		return (diffuse_contribution);
	return ((t_vec3){0.0f, 0.0f, 0.0f});
}


t_vec4	per_pixel(t_ray ray, t_scene scene, uint32_t *rngState)
{
	int bounce = 0;
	t_vec3	incomming_light = vec3_new(0.0f, 0.0f, 0.0f);
	t_vec3	ray_color = vec3_new(1.0f, 1.0f, 1.0f);

	t_hitinfo closest_hit;
	t_omnidirectional_light circle_light;
	circle_light.position = vec3_new(0.0f, 3.0f, 0.0f);
	circle_light.color = vec3_new(1.0f, 1.0f, 1.0f);
	circle_light.intensity = 1.0f;
	while (bounce <= MAX_BOUNCES)
	{
		//! check
		closest_hit.distance = INFINITY;
		closest_hit.hit = false;
		
		// closest_hit = sphere_intersection(ray, scene, closest_hit);
		closest_hit = sphere_bvh_intersection(ray, scene.spheres, closest_hit, scene.bvh_spheres);
		closest_hit = inv_plane_intersection(ray, scene, closest_hit);
		if (closest_hit.hit)
		{
			t_vec3	original_origin = ray.origin;
			ray.origin = vec3_add(closest_hit.position, vec3_mulf(closest_hit.normal, EPSILON));

			t_vec3 temp = random_direction(rngState);
			t_vec3 diffuse_dir = vec3_normalize(vec3_add(closest_hit.normal, temp));


			ray.direction = diffuse_dir;

			// t_vec3 omni_light = calc_onmi_light(closest_hit.position, closest_hit.normal, circle_light);
			
			t_vec3 emitted_light = vec3_new(3.0f, 3.0f, 3.0f);
			emitted_light = vec3_mulf(closest_hit.material.emission, closest_hit.material.strength);

			emitted_light = (t_vec3){0.0f, 0.0f, 0.0f};
			emitted_light = omni_dir_light(ray, scene, closest_hit);

			
			// emitted_light = vec3_add(emitted_light, omni_light);
			
			// incomming_light = vec3_mul(incomming_light, vec3_mul(ray_color, emitted_light));
			
			ray_color = vec3_mul(ray_color, closest_hit.material.color);
			incomming_light = vec3_add(incomming_light, vec3_mul(ray_color, emitted_light));
		}
		else
		{
			// break ;
			incomming_light = vec3_add(incomming_light, vec3_mul(ray_color, default_sky(ray.direction)));
			break ;
		}
		bounce++;
	}
	return ((t_vec4){incomming_light.x, incomming_light.y, incomming_light.z, 1.0f});
}

uint32_t	get_rngstate(uint32_t width, uint32_t height, uint32_t x, uint32_t y)
{
	t_vec2		coord;
	t_vec2		num_pixels;
	uint32_t	pixel_index;

	coord = (t_vec2){(float)x / (float)(width), (float)y / (float)(height)};
	num_pixels = (t_vec2){(float)width, (float)height};
	coord = vec2_mul(coord, num_pixels);
	pixel_index = coord.x + coord.y * num_pixels.x;
	return (pixel_index + global_frame * 719393);
}

t_vec4	vec3_tone_map(t_vec3 color)
{
	float	gamma = 2.2f;
	float	exposure = 1.0f;
	color = vec3_mulf(color, exposure);
	t_vec3	result = vec3_div(color, vec3_addf(color, 1.0f));
	// t_vec3 result;

	// result.x = 1.0f - expf(-color.x * exposure);
	// result.y = 1.0f - expf(-color.y * exposure);
	// result.z = 1.0f - expf(-color.z * exposure);

	// result = color;
	result.x = powf(result.x, 1.0f / gamma);
	result.y = powf(result.y, 1.0f / gamma);
	result.z = powf(result.z, 1.0f / gamma);
	return (vec4_new(result.x, result.y, result.z, 1.0f));
}

void	*render(void *arg)
{
	t_thread	*thread = arg;
	t_data	*data;

	data = thread->data;
	uint32_t x = 0;
	uint32_t y = 0;
	t_ray	ray;
	ray.origin = data->scene.camera.position;
	
	uint32_t rngState;
	t_vec4	color;

	// uint32_t	screen_width = WIDTH;
	// uint32_t	screen_height = HEIGHT;
	// if (PIXEL_SIZE == 1)
	// {
	// 	screen_width = data->mlx->width;
	// 	screen_height = data->mlx->height;
	// }

	if (data->utils.accumulated_frames == 1)
		ft_memset(data->utils.accumulated_data, 0, sizeof(t_vec4) * data->utils.width * data->utils.height);
	while (y < thread->y_end)
	{
		x = thread->x_start;
		while (x < thread->x_end)
		{
			// rngState = get_rngstate(data, x, y);
			rngState = get_rngstate(data->utils.width, data->utils.height, x, y);

			// t_vec4 target = data->scene.camera.ray_target[x + y * WIDTH];
			// ray.direction = vec3_new(target.x, target.y, target.z);

			ray.direction = data->scene.camera.ray_dir[x + y * data->utils.width];
			// ray.direction = data->scene.camera.ray_dir[x + y * WIDTH];

			// col = per_pixel(ray, data->scene, vec2_new(x, y), &rngState, coord);
			color = per_pixel(ray, data->scene, &rngState);


			data->utils.accumulated_data[x + y * data->utils.width] = vec4_add(data->utils.accumulated_data[x + y * data->utils.width], color);
			t_vec4 accumulated_color = data->utils.accumulated_data[x + y * data->utils.width];
			accumulated_color = vec4_divf(accumulated_color, (float)data->utils.accumulated_frames);
			// data->utils.accumulated_data[x + y * WIDTH] = vec4_add(data->utils.accumulated_data[x + y * WIDTH], color);
			// t_vec4 accumulated_color = data->utils.accumulated_data[x + y * WIDTH];
			// accumulated_color = vec4_divf(accumulated_color, (float)data->utils.accumulated_frames);

			color = accumulated_color;
			color = vec3_tone_map((t_vec3){color.x, color.y, color.z});
			// color = vec4_clamp(color, 0.0f, 1.0f);
			
			uint32_t hex_color = vec4_to_color(color);
			for (int i = 0; i < PIXEL_SIZE; i++)
			{
				for (int j = 0; j < PIXEL_SIZE; j++)
				{
					// put_pixel(data->img, (x * PIXEL_SIZE) + i, \
					// 	((HEIGHT - y - 1) * PIXEL_SIZE) + j, \
					// 	hex_color);
					//! RRGGBBAA
					put_pixel(data->img, (x * PIXEL_SIZE) + i, \
						((data->utils.height - y - 1) * PIXEL_SIZE) + j, \
						hex_color);
				}
			}
			
			// if (thread->index == 3)
			// 	put_pixel(data->img, x, y, 0x00FF00FF);
			// else
			// 	put_pixel(data->img, x, y, 0xFF0000FF);
			x++;
		}
		y++;
	}
	return (NULL);
}

bool	create_thread(t_data *data)
{
	t_thread	threads[THREADS];

	// uint32_t	width = data->mlx->width;
	// uint32_t	height = data->mlx->height;
	// uint32_t	width = data->utils.width;
	// uint32_t	height = data->utils.height;

	uint32_t	step_x = data->utils.width / THREADS;

	// if (data->utils.accumulated_frames == 1)
	// 	ft_memset(data->utils.accumulated_data, 0, sizeof(t_vec4) * data->utils.width * data->utils.height);

	int i = 0;
	while (i < THREADS)
	{
		threads[i].x_start = i * step_x;
		threads[i].x_end = (i + 1) * step_x;
		if (i == THREADS - 1)
			threads[i].x_end = data->utils.width;
		threads[i].y_start = 0;
		threads[i].y_end = data->utils.height;
		threads[i].data = data;
		threads[i].index = i;
		pthread_create(&threads[i].tid, NULL, render, &threads[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(threads[i].tid, NULL);
		i++;
	}
	return (true);
}

bool	render_zone(t_data *data)
{
	t_thread	zone;

	// if (data->utils.accumulated_frames == 1)
		// ft_memset(data->utils.accumulated_data, 0, sizeof(t_vec4) * data->utils.width * data->utils.height);
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

void	render_loop(void *param)
{
	t_data	*data;

	data = param;
	movement(data);
	// if (data->mlx->width != data->img->width || data->mlx->height != data->img->height)
	// 	data->utils.accumulated_frames = 1;
	// mlx_resize_image(data->img, data->mlx->width, data->mlx->height);
	if (render_zone(data) == false)
		exit(EXIT_FAILURE);

	// render(data);

	data->utils.accumulated_frames++;
	global_frame++;
}



void	frame_times(void *param)
{
	t_data	*data;

	data = param;
	double currentTime = glfwGetTime();
	double deltaTime = currentTime - data->utils.prev_frame;
	double frameTimeMs = deltaTime * 1000.0;
	double fps = 1000.0 / frameTimeMs;
	//! use this one
	// printf("\rframeTimeMs: %.2f ms    frames: %d	accumulated frames: %d", frameTimeMs, total_frames, accumulated_frames);
	printf("\rframeTimeMs: %.2f ms    frames: %d", frameTimeMs, global_frame);
	char output[50];

	snprintf(output, 50, "%f", fps);
	// floatToString(fps, output, 2);
	
	mlx_set_window_title(data->mlx, output);


	
	// printf("\rFPS: %.2f    ",1000 / frameTimeMs);
	fflush(stdout);
	data->utils.prev_frame = currentTime;
	
}

void	resize_window(void *param)
{
	t_data	*data;

	data = param;
	if (PIXEL_SIZE != 1)
		return ;
	if (data->mlx->width == data->img->width && data->mlx->height == data->img->height)
		return ;
	data->utils.accumulated_frames = 1;
	mlx_resize_image(data->img, data->mlx->width, data->mlx->height);
	printf("resizing\n");
	
	free(data->utils.accumulated_data);
	free(data->scene.camera.ray_target);
	free(data->scene.camera.ray_dir);

	uint32_t	width = data->mlx->width;
	uint32_t	height = data->mlx->height;
	data->utils.width = width;
	data->utils.height = height;

	data->utils.accumulated_data = malloc(sizeof(t_vec4) * width * height);
	data->scene.camera.ray_target = malloc(sizeof(t_vec4) * width * height);
	data->scene.camera.ray_dir = malloc(sizeof(t_vec3) * width * height);

	data->scene.camera.aspectRatio = (float)width / (float)height;

	recalculate_view(data);
	recalculated_projection(data);
	recalculat_ray_directions(data);
}