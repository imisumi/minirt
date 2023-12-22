/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:32:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/12/20 17:29:02 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4f	per_pixel(t_vec3f dir, t_scene scene, uint32_t *rngState)
{
	int bounce = 0;
	t_vec3f incomming_light = {0.0f, 0.0f, 0.0f, 0.0f};
	t_vec3f ray_color = {1.0f, 1.0f, 1.0f, 0.0f};

	t_vec3f ray[2];
	ray[ORIGIN] = scene.camera.position;
	ray[DIR] = dir;

	t_hitinfo closest_hit;
	float	bounce_attenuation = 0.8f;
	while (bounce <= MAX_BOUNCES)
	{
		//! check
		closest_hit.distance = INFINITY;
		closest_hit.hit = false;
		
		// closest_hit = inv_plane_intersection(ray, scene, closest_hit);
		closest_hit = inv_plane_intersection_f(ray, scene, closest_hit);
		// closest_hit = sphere_intersection_f(ray, scene, closest_hit);
		closest_hit = sphere_bvh_intersection_f(ray, scene.spheres, closest_hit, scene.bvh_spheres_f);
		if (closest_hit.hit)
		{
			// ray.origin = vec3_add(closest_hit.position, vec3_mulf(closest_hit.normal, EPSILON));
			ray[ORIGIN] = closest_hit.position + (closest_hit.normal * EPSILON);

			// return ((t_vec4f){1.0f, 0.0f, 0.0f, 1.0f});
			// t_vec3 temp = random_direction(rngState);
			t_vec3f temp = random_directionf(rngState);
			// t_vec3 diffuse_dir = vec3_normalize(vec3_add(closest_hit.normal, temp));
			t_vec3f diffuse_dir = vec3f_normalize(closest_hit.normal + temp);


			// ray.direction = diffuse_dir;
			ray[DIR] = diffuse_dir;


			float intensity_scale = powf(bounce_attenuation, bounce);

			t_vec3f emitted_light = {0};
			// emitted_light = omni_dir_light_f(ray, scene, closest_hit);

			
			// emitted_light += omni_dir_light_f2(ray, scene, closest_hit);
			// emitted_light = omni_dir_light_f_comb(ray, scene, closest_hit);
			emitted_light = emitted_light * intensity_scale;

			ray_color = ray_color * closest_hit.material.color;
			incomming_light = incomming_light + (ray_color * emitted_light);
		}
		else
		{
			t_vec3f	sky;
			// if (scene.ambient_light == 0.0f)
			// 	break ;
			// else if (scene.ambient_light == -1.0f)
			// 	sky = default_skyf(ray[DIR], scene);
			// else
			// 	sky = scene.ambient_color * scene.ambient_light;

				
			// sky = default_skyf(ray[DIR], scene);
			// incomming_light = vec3_add(incomming_light, vec3_mul(ray_color, sky));
			// t_vec3f sky = {0.5f, 0.5f, 0.5f, 0.0f};
			sky = texture(ray[DIR], scene.hdri);
			incomming_light = incomming_light + (ray_color * sky);
			break ;
		}
		bounce++;
	}
	// return ((t_vec4){incomming_light.x, incomming_light.y, incomming_light.z, 1.0f});
	return ((t_vec4f){incomming_light[X], incomming_light[Y], incomming_light[Z], 1.0f});
}

void	render_pixel(t_data *data, uint32_t x, uint32_t y)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	hex_color;
	t_vec4f		avg_color;

	avg_color = data->utils.accumulated_data[x + y * data->utils.width];
	avg_color /= (float)data->utils.accumulated_frames;
	avg_color = vec3f_tone_map(avg_color);
	//? clamp 0.0f - 1.0f maybe not needed
	hex_color = vec4f_to_color(avg_color);
	i = 0;
	while (i < PIXEL_SIZE)
	{
		j = 0;
		while (j < PIXEL_SIZE)
		{
			//! RRGGBBAA
			put_pixel(data->img, (x * PIXEL_SIZE) + i, \
				((data->utils.height - y - 1) * PIXEL_SIZE) + j, \
				hex_color);
			j++;
		}
		i++;
	}
}

void	*render(void *arg)
{
	const t_thread	*thread = arg;
	t_data	*data;

	data = thread->data;
	uint32_t	x;
	uint32_t	y;
	uint32_t	rngState;
	t_vec4f		color;
	t_vec3f		dir;
	
	y = thread->y_start;
	while (y < thread->y_end)
	{
		x = thread->x_start;
		while (x < thread->x_end)
		{
			rngState = get_rngstate(data->utils.width, data->utils.height, x, y);
			dir = data->scene.camera.ray_dir[x + y * data->utils.width];
			if (AA)
				dir = aa_update_dir(data, &rngState, x, y);
			color = per_pixel(dir, data->scene, &rngState);
			data->utils.accumulated_data[x + y * data->utils.width] += color;
			render_pixel(data, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}
