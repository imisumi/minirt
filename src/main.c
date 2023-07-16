/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/07/16 20:14:07 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>

double previousTime = 0.0;



void put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	if (x >= 0 && x < image->width && y >= 0 && y < image->height)
		mlx_put_pixel(image, x, y, color);
}

void init_scene(t_scene *s)
{
	t_material mat;
	init_camera(&s->camera);

	init_scene_one(s);



	// s->nb_planes = 0;
	return ;



	// s->nb_spheres = 2;
	// s->spheres = malloc(sizeof(t_sphere) * s->nb_spheres);
	// mat.albedo = vec3_create(1.0f, 1.0f, 1.0f);
	// mat.emission_color = vec3_create(0.0f, 0.0f, 0.0f);
	// mat.emission_intensity = 0.0f;
	// mat.smoothness = 0.0f;
	
	// s->spheres[0] = create_sphere(vec3_create(0.0f, 1.0f, 0.0f), 0.5f);
	// s->spheres[1] = create_sphere(vec3_create(0.0f, 4.9f, 0.0f), 2.0f);
	// s->spheres[0].material = mat;

	
	// mat.albedo = vec3_create(0.0f, 0.0f, 0.0f);
	// mat.emission_color = vec3_create(1.0f, 1.0f, 1.0f);
	// mat.emission_intensity = 10.0f;
	// mat.smoothness = 0.0f;
	// s->spheres[1].material = mat;

	s->nb_spheres = 1;
	s->spheres = malloc(sizeof(t_sphere) * s->nb_spheres);
	mat.albedo = vec3_create(1.0f, 1.0f, 1.0f);
	mat.emission_color = vec3_create(0.0f, 0.0f, 0.0f);
	mat.emission_intensity = 0.0f;
	mat.smoothness = 1.0f;
	mat.specular = 0.0f;
	s->spheres[0] = create_sphere(vec3_create(0.0f, 1.0f, 0.0f), 0.5f);
	// s->spheres[0] = create_sphere(vec3_create(-1.8f, 1.0f, 0.0f), 0.5f);
	// s->spheres[1] = create_sphere(vec3_create(-0.6f, 1.0f, 0.0f), 0.5f);
	// s->spheres[2] = create_sphere(vec3_create(0.6f, 1.0f, 0.0f), 0.5f);
	// s->spheres[3] = create_sphere(vec3_create(1.8f, 1.0f, 0.0f), 0.5f);
	// // mat.smoothness = 0.4f;
	mat.specular = 0.22f;
	s->spheres[0].material = mat;
	s->spheres[0].material.smoothness = 1.0f;
	s->spheres[0].material.albedo = vec3_create(0.9f, 0.1f, 0.2f);
	// s->spheres[0].material.albedo = vec3_create(1.0f, 1.0f, 1.0f);
	// // mat.smoothness = 0.6f;
	// mat.specular = 0.4f;
	// s->spheres[1].material = mat;
	// // mat.smoothness = 0.8f;
	// mat.specular = 0.15f;
	// s->spheres[2].material = mat;
	// // mat.smoothness = 1.0f;
	// mat.specular = 0.02f;
	// s->spheres[3].material = mat;


	// s->nb_inv_planes = 0;
	// s->inv_planes[0].position = vec3_create(0.0f, 0.0f, 0.0f);
	// s->inv_planes[0].normal = vec3_create(0.0f, 1.0f, 0.0f);




	s->nb_planes = 7;
	s->planes = malloc(sizeof(t_plane) * s->nb_planes);
	s->planes[6].position = vec3_create(0.0f, 2.99f, 0.0f);
	s->planes[6].normal = vec3_create(0.0f, -1.0f, 0.0f);
	s->planes[6].width = 1.0f;
	s->planes[6].height = 1.0f;
	s->planes[6].material.albedo = vec3_create(1.0f, 1.0f, 1.0f);
	s->planes[6].material.emission_color = vec3_create(1.0f, 1.0f, 1.0f);
	s->planes[6].material.emission_intensity = 10.0f;
	s->planes[6].material.smoothness = 0.0f;
	s->planes[6].material.specular = 0.0f;
	// // s->planes[1].position = vec3_create(0.0f, 3.1f, 0.0f);
	// // s->planes[1].normal = vec3_create(0.0f, -1.0f, 0.0f);
	// // s->planes[1].width = 30.0f;
	// // s->planes[1].height = 30.0f;
	// // s->planes[1].material.albedo = vec3_create(0.2f, 0.2f, 0.2f);
	// // s->planes[1].material.smoothness = 0.0f;

	
	// bottom
	s->planes[0].position = vec3_create(0.0f, 0.0f, 0.0f);
	s->planes[0].normal = vec3_create(0.0f, 1.0f, 0.0f);
	s->planes[0].width = 5.01f;
	s->planes[0].height = 3.01f;
	s->planes[0].material.albedo = vec3_create(0.0f, 1.0f, 0.0f);
	s->planes[0].material.emission_color = vec3_create(0.0f, 0.0f, 0.0f);
	s->planes[0].material.emission_intensity = 0.0f;
	s->planes[0].material.smoothness = 0.0f;
	s->planes[0].material.specular = 0.0f;

	// top
	s->planes[1].position = vec3_create(0.0f, 3.0f, 0.0f);
	s->planes[1].normal = vec3_create(0.0f, -1.0f, 0.0f);
	s->planes[1].width = 5.01f;
	s->planes[1].height = 3.01f;
	s->planes[1].material.albedo = vec3_create(0.4f, 0.4f, 0.4f);
	s->planes[1].material.emission_color = vec3_create(0.0f, 0.0f, 0.0f);
	s->planes[1].material.emission_intensity = 0.0f;
	s->planes[1].material.smoothness = 0.0f;
	s->planes[1].material.specular = 0.0f;

	//left
	s->planes[2].position = vec3_create(-2.5f, 1.5f, 0.0f);
	s->planes[2].normal = vec3_create(1.0f, 0.0f, 0.0f);
	s->planes[2].width = 3.01f;
	s->planes[2].height = 3.01f;
	s->planes[2].material.albedo = vec3_create(1.0f, 0.0f, 0.0f);
	s->planes[2].material.emission_color = vec3_create(0.0f, 0.0f, 0.0f);
	s->planes[2].material.emission_intensity = 0.0f;
	s->planes[2].material.smoothness = 0.0f;
	s->planes[2].material.specular = 0.0f;

	// right
	s->planes[3].position = vec3_create(2.5f, 1.5f, 0.0f);
	s->planes[3].normal = vec3_create(-1.0f, 0.0f, 0.0f);
	s->planes[3].width = 3.01f;
	s->planes[3].height = 3.01f;
	s->planes[3].material.albedo = vec3_create(0.0f, 0.0f, 1.0f);
	s->planes[3].material.emission_color = vec3_create(0.0f, 0.0f, 0.0f);
	s->planes[3].material.emission_intensity = 0.0f;
	s->planes[3].material.smoothness = 0.0f;
	s->planes[3].material.specular = 0.0f;
	
	// back
	// s->planes[4].position = vec3_create(0.0f, 1.5f, -1.5f);
	s->planes[4].position = vec3_create(0.0f, 10.5f, -1.5f);
	s->planes[4].normal = vec3_create(0.0f, 0.0f, 1.0f);
	s->planes[4].width = 5.01f;
	s->planes[4].height = 3.01f;
	s->planes[4].material.albedo = vec3_create(1.0f, 1.0f, 1.0f);
	s->planes[4].material.emission_color = vec3_create(0.0f, 0.0f, 0.0f);
	s->planes[4].material.emission_intensity = 0.0f;
	s->planes[4].material.smoothness = 0.0f;
	s->planes[4].material.specular = 0.0f;

	// front
	s->planes[5].position = vec3_create(0.0f, 1.5f, 1.5f);
	s->planes[5].normal = vec3_create(0.0f, 0.0f, -1.0f);
	s->planes[5].width = 5.01f;
	s->planes[5].height = 3.01f;
	s->planes[5].material.albedo = vec3_create(1.0f, 1.0f, 1.0f);
	s->planes[5].material.emission_color = vec3_create(0.0f, 0.0f, 0.0f);
	s->planes[5].material.emission_intensity = 0.0f;
	s->planes[5].material.smoothness = 0.0f;
	s->planes[5].material.specular = 0.0f;
}

float hit_inv_plane(t_ray ray, t_vec3 pos, t_vec3 normal)
{
	float denom = vec3_dot(ray.direction, normal);
	if (denom > 1e-6)
	{
		t_vec3 p0l0 = vec3_sub(pos, ray.origin);
		float t = vec3_dot(p0l0, normal) / denom;
		if (t >= 0)
			return (t);
	}
	return (-1.0f);
}

t_vec3 lerp(t_vec3 vec1, t_vec3 vec2, float t)
{
	// if (t == 1.0f)
	// 	return vec1;
	t_vec3 result;
	result.x = vec1.x + (t * (vec2.x - vec1.x));
	result.y = vec1.y + (t * (vec2.y - vec1.y));
	result.z = vec1.z + (t * (vec2.z - vec1.z));
	return result;
}

t_vec4 per_pixel(t_ray ray, t_vec2 coord, t_scene s, t_vec2 xy, uint32_t *rngState)
{
	t_vec3 color;

	t_obj_hit obj_hit;
	obj_hit.hit_distance = MAXFLOAT;
	obj_hit.hit = false;

	t_sphere* closest_sphere = NULL;
	t_inv_plane* closest_inv_plane = NULL;
	t_inv_plane plane;

	t_vec3 ray_color = vec3_create(1.0f, 1.0f, 1.0f);
	t_vec3 incoming_licht = vec3_create(0.0f, 0.0f, 0.0f);
	int max_bounces = 5;
	float is_specular = 0.0f;
	for (int i = 0; i <= max_bounces; i++)
	{
		obj_hit.hit = false;
		obj_hit.hit_distance = MAXFLOAT;
		
		obj_hit = sphere_intersection(ray, s, obj_hit);
		obj_hit = plane_intersection(ray, s, obj_hit);
		
		// TODO: relection
		if (obj_hit.hit == true)
		{
			ray.origin = vec3_add(obj_hit.position, vec3_mul_float(obj_hit.normal, 0.001f));
			// ray.direction = random_himisphere_dir(obj_hit.normal, rngState);
			// if (obj_hit.material.smoothness == 1.0f)
			// {
			// 	// ray.direction = vec3_reflect(ray.direction, obj_hit.normal);
			// 	// ray.direction = vec3_normalize(vec3_add(obj_hit.normal, random_direction_range(rngState, 0.1f)));
			// 	t_vec3 diffuse_dir = vec3_normalize(vec3_add(obj_hit.normal, random_direction(rngState)));
			// 	t_vec3 specular_dir = vec3_reflect(ray.direction, obj_hit.normal);
			// 	ray.direction =  lerp(diffuse_dir, specular_dir, 1.0f);
			// }
			// else
			// 	ray.direction = vec3_normalize(vec3_add(obj_hit.normal, random_direction(rngState)));
			
			t_vec3 diffuse_dir = vec3_normalize(vec3_add(obj_hit.normal, random_direction(rngState)));
			t_vec3 specular_dir = vec3_reflect(ray.direction, obj_hit.normal);
			if (obj_hit.material.specular >= randomFloat(rngState))
				is_specular = 1.0f;
			else
				is_specular = 0.0f;

			ray.direction =  lerp(diffuse_dir, specular_dir, obj_hit.material.smoothness * is_specular);
			// ray.direction =  lerp(diffuse_dir, specular_dir, obj_hit.material.smoothness);
	
			t_material material = obj_hit.material;
			t_vec3 emitted_light = vec3_mul_float(material.emission_color, material.emission_intensity);

			incoming_licht = vec3_add(incoming_licht, vec3_mul(ray_color, emitted_light));

			// ray_color = vec3_mul(ray_color, material.albedo);
			ray_color = vec3_mul(ray_color, lerp(material.albedo, vec3_create(1.0f, 1.0f, 1.0f), is_specular));
		}
		else
		{
			t_vec3 unit_direction = vec3_normalize(ray.direction);
			float t = 0.5f * (unit_direction.y + 1.0f);
			t_vec3 sky = vec3_add(vec3_mul_float(vec3_create(1.0f, 1.0f, 1.0f), 1.0f - t),	vec3_mul_float(vec3_create(0.5f, 0.7f, 1.0f), t));
			incoming_licht = vec3_add(incoming_licht, vec3_mul(ray_color, sky));
			break;
		}
	}
	return vec4_create(incoming_licht.x, incoming_licht.y, incoming_licht.z, 1.0f);
}


void	render(t_mlx *d)
{
	t_scene scene = d->scene;
	t_ray ray;
	ray.origin = scene.camera.position;
	// for (int y = d->img->height - 1; y >= 0; y--)

	if (accumulated_frames == 1)
		memset(accumulated_data, 0, WIDTH * HEIGHT * sizeof(t_vec4));
	for (int y = HEIGHT - 1; y >= 0; y--)
	{
		for (int x = 0; x < WIDTH; x++)
		{

			t_vec2 coord = {(float)x / (float)(WIDTH), (float)y / (float)(HEIGHT)};
			// coord = vec2_sub_float(vec2_mul_float(coord, 2.0), 1.0f);
			ray.direction = scene.camera.ray_dir[x + y * WIDTH];




			t_vec2 numPixels = vec2_create((float)WIDTH, (float)HEIGHT);
			t_vec2 pixelCoord = vec2_mul(coord, numPixels);
			uint32_t pixelIndex = pixelCoord.x + pixelCoord.y * numPixels.x;
			uint32_t rngState = pixelIndex + total_frames * 719393;




			// coord.x = x;
			// coord.y = y;
			t_vec4 color = per_pixel(ray, coord, d->scene, vec2_create(x, y), &rngState);

			
			accumulated_data[x + y * WIDTH] = vec4_add(accumulated_data[x + y * WIDTH], color);
			
			t_vec4 accumulated_color = accumulated_data[x + y * WIDTH];
			accumulated_color = vec4_div_float(accumulated_color, accumulated_frames);
			accumulated_color = vec4_clamp(accumulated_color, 0.0, 1.0);
			
			for (int i = 0; i < PIXEL_SIZE; i++)
			{
				for (int j = 0; j < PIXEL_SIZE; j++)
				{
					put_pixel(d->img, (x * PIXEL_SIZE) + i, \
						((HEIGHT - y - 1) * PIXEL_SIZE) + j, \
						vec4_to_color(accumulated_color));
				}
			}
		}
		// exit(0);
	}
	accumulated_frames++;
}

void recalculat_ray_directions(t_mlx *d)
{
	// for (uint32_t y = 0; y < d->img->height; y++)
	for (uint32_t y = 0; y < HEIGHT; y++)
	{
		for (uint32_t x = 0; x < WIDTH; x++)
		{
			t_vec2 coord = {(float)x / (float)(WIDTH), (float)y / (float)(HEIGHT)};
			coord = vec2_sub_float(vec2_mul_float(coord, 2.0), 1.0f);

			t_vec4 target = mat4_mul_vec4(d->scene.camera.inv_projection, vec4_create(coord.x, coord.y, 1, 1));
			t_vec3 t = vec3_div_float(vec3_create(target.x, target.y, target.z), target.w);
			target = vec4_normalize(vec4_create(-t.x, t.y, -t.z, 0.0f));
			// target = vec4_normalize(vec4_create(-t.x, t.y, -t.z, 0.0f));
			target = mat4_mul_vec4(d->scene.camera.inv_view, target);
			// printf("rayDirection: %f, %f, %f\n", d->scene.camera.inv_view.m[0][1], d->scene.camera.inv_view.m[1][1], d->scene.camera.inv_view.m[2][2]);
			t_vec3 rayDirection = vec3_create(target.x, target.y, target.z);
			d->scene.camera.ray_dir[x + y * WIDTH] = rayDirection;
			// printf("rayDirection: %f, %f, %f\n", target.x, target.y, target.z);

			// glm::vec4 target = m_InverseProjection * glm::vec4(coord.x, coord.y, 1, 1);
			// glm::vec3 rayDirection = glm::vec3(m_InverseView * glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0)); // World space
			// m_ray_dir[x + y * m_ViewportWidth] = rayDirection;
		}
		// exit(0);
	}
}

void	ft_loop_hook(void *param)
{
	t_mlx	*data;

	data = param;
	double currentTime = glfwGetTime();
	double deltaTime = currentTime - previousTime;
	double frameTimeMs = deltaTime * 1000.0;
	//! use this one
	printf("\rframeTimeMs: %.2f ms    frames: %d	accumulated frames: %d", frameTimeMs, total_frames, accumulated_frames);


	
	// printf("\rFPS: %.2f    ",1000 / frameTimeMs);
	fflush(stdout);
	previousTime = currentTime;

	// sky(data);
	movement(data);
	render(data);
	total_frames++;
}

void ft_hook(void* param)
{
	t_mlx	*data = param;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}

int main(int argc, const char* argv[])
{
	t_mlx data;
	total_frames = 0;
	accumulated_data = malloc(sizeof(t_vec4) * WIDTH * HEIGHT);
	accumulated_frames = 1;

	int width = WIDTH;
	int height = HEIGHT;
	if (PIXEL_SIZE > 1)
	{
		width *= PIXEL_SIZE;
		height *= PIXEL_SIZE;
	}
	data.mlx = mlx_init(width, height, "Ray Tracer", true);
	if (!data.mlx)
		exit(EXIT_FAILURE);
	data.img = mlx_new_image(data.mlx, width, height);
	if (!data.img)
	{
		mlx_close_window(data.mlx);
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(data.mlx, data.img, 0, 0) == -1)
	{
		mlx_close_window(data.mlx);
		exit(EXIT_FAILURE);
	}


	init_scene(&data.scene);

	recalculate_view(&data);
	recalculated_projection(&data);
	recalculat_ray_directions(&data);
	
	// read_hdr_file(&data);
	
	// printf("%f %f %f\n", data.scene.camera.direction.x, data.scene.camera.direction.y, data.scene.camera.direction.z);
	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_loop_hook(data.mlx, ft_loop_hook, &data);

	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}