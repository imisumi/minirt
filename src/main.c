/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/07/11 16:00:28 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"
#include <GLFW/glfw3.h>

float* pixels;
unsigned char* pixels_8;
uint8_t* pixels_8bit;
int hdr_width;
int hdr_height;
int hdr_channels;
uint32_t total_frames;
t_vec4 *accumulated_data;
uint32_t accumulated_frames;

double previousTime = 0.0;

void put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	if (x >= 0 && x < image->width && y >= 0 && y < image->height)
		mlx_put_pixel(image, x, y, color);
}

// uint32_t vec4_to_color(t_vec4 c)
// {
// 	uint8_t r = (uint8_t)(c.x * 255.0);
// 	uint8_t g = (uint8_t)(c.y * 255.0);
// 	uint8_t b = (uint8_t)(c.z * 255.0);
// 	uint8_t a = (uint8_t)(c.w * 255.0);
// 	return (ft_pixel(r, g, b, a));
// }

// t_vec3 point_at_parameter(t_ray r, float t)
// {
// 	t_vec3 res;

// 	res = vec3_add(r.origin, vec3_mul_float(r.direction, t));
// 	return (res);
// }

void init_scene(t_scene *s)
{
	s->camera.position = vec3_create(0.0, 1.0, 5.0f);
	s->camera.direction = vec3_create(0.0, 0.0, -1.0);

	s->camera.rayDirections = malloc(sizeof(t_vec3) * WIDTH * HEIGHT);

	s->camera.mouseDelta.x = 0;
	s->camera.mouseDelta.y = 0;

	s->camera.projection = mat4_identity();
	s->camera.inv_projection = mat4_identity();
	s->camera.view = mat4_identity();
	s->camera.inv_view = mat4_identity();

	s->camera.verticalFOV = 60.0f;
	s->camera.aspectRatio = (float)WIDTH / (float)HEIGHT;
	s->camera.zNear = 0.1f;
	s->camera.zFar = 10.0f;

	s->camera.prevMousePos.x = -1;
	s->camera.prevMousePos.y = -1;





	s->nb_spheres = 2;
	s->spheres[0] = create_sphere(vec3_create(0.0f, .7f, 0.0f), 0.5f);
	// s->spheres[0].material.albedo = vec3_create(0.3f, 0.3f, 0.5f);
	s->spheres[0].material.albedo = vec3_create(0.0f, 0.0f, 0.0f);
	s->spheres[0].material.emission_color = vec3_create(1.0f, 1.0f, 1.0f);
	s->spheres[0].material.emission_intensity = 100.0f;
	
	s->spheres[1] = create_sphere(vec3_create(1.5f, 0.0f, 0.0f), 0.5f);
	s->spheres[1].material.albedo = vec3_create(1.0f, 0.0f, 0.0f);


	s->nb_inv_planes = 1;
	s->inv_planes[0].position = vec3_create(0.0f, 0.0f, 0.0f);
	s->inv_planes[0].normal = vec3_create(0.0f, 1.0f, 0.0f);

	s->nb_planes = 1;
	s->planes[0].position = vec3_create(0.0f, 0.0f, 0.0f);
	s->planes[0].normal = vec3_create(0.0f, 1.0f, 0.0f);
	s->planes[0].width = 5.0f;
	s->planes[0].height = 5.0f;
	s->planes[0].material.albedo = vec3_create(0.0f, 1.0f, 0.0f);
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

t_vec4 get_sky_color_float(t_ray ray, t_vec2 coord)
{
    float u = atan2(ray.direction.z, ray.direction.x) / (2 * M_PI) + 0.5f;
    float v = 1.0f - (asin(ray.direction.y) / M_PI + 0.5f);

    float visibleU = u * hdr_width;
    float visibleV = v * hdr_height;

    // Sample the visible portion of the skybox
    float visibleR = 0.0f;
    float visibleG = 0.0f;
    float visibleB = 0.0f;

    if (visibleU >= 0 && visibleV >= 0 && visibleU < hdr_width && visibleV < hdr_height)
    {
        // Fully visible skybox portion, perform bilinear interpolation
        int x0 = (int)visibleU;
        int y0 = (int)visibleV;
        int x1 = x0 + 1;
        int y1 = y0 + 1;

        float fracX = visibleU - x0;
        float fracY = visibleV - y0;

        // Sample the four neighboring pixels
        float* pixel00 = pixels + (x0 + y0 * hdr_width) * hdr_channels;
        float* pixel01 = pixels + (x0 + y1 * hdr_width) * hdr_channels;
        float* pixel10 = pixels + (x1 + y0 * hdr_width) * hdr_channels;
        float* pixel11 = pixels + (x1 + y1 * hdr_width) * hdr_channels;

        // Perform bilinear interpolation for each channel (assuming num_channels = 3 for RGB)
        visibleR = (1 - fracX) * (1 - fracY) * pixel00[0] +
                   (1 - fracX) * fracY * pixel01[0] +
                   fracX * (1 - fracY) * pixel10[0] +
                   fracX * fracY * pixel11[0];

        visibleG = (1 - fracX) * (1 - fracY) * pixel00[1] +
                   (1 - fracX) * fracY * pixel01[1] +
                   fracX * (1 - fracY) * pixel10[1] +
                   fracX * fracY * pixel11[1];

        visibleB = (1 - fracX) * (1 - fracY) * pixel00[2] +
                   (1 - fracX) * fracY * pixel01[2] +
                   fracX * (1 - fracY) * pixel10[2] +
                   fracX * fracY * pixel11[2];
    }

    t_vec4 sky_color;
    sky_color = vec4_create(visibleR, visibleG, visibleB, 1.0f);
    return sky_color;
}

t_vec4 get_sky_color_int(t_ray ray, t_vec2 coord)
{
    float u = atan2(ray.direction.z, ray.direction.x) / (2 * M_PI) + 0.5f;
    float v = 1.0f - (asin(ray.direction.y) / M_PI + 0.5f);

    float visibleU = u * hdr_width;
    float visibleV = v * hdr_height;

    // Sample the visible portion of the skybox
    uint8_t visibleR = 0.0f;
    uint8_t visibleG = 0.0f;
    uint8_t visibleB = 0.0f;

    if (visibleU >= 0 && visibleV >= 0 && visibleU < hdr_width && visibleV < hdr_height)
    {
        // Fully visible skybox portion, perform bilinear interpolation
        int x0 = (int)visibleU;
        int y0 = (int)visibleV;
        int x1 = x0 + 1;
        int y1 = y0 + 1;

        float fracX = visibleU - x0;
        float fracY = visibleV - y0;

        // Sample the four neighboring pixels
        uint8_t* pixel00 = (pixels_8bit + (x0 + y0 * hdr_width) * hdr_channels);
        uint8_t* pixel01 = (pixels_8bit + (x0 + y1 * hdr_width) * hdr_channels);
        uint8_t* pixel10 = (pixels_8bit + (x1 + y0 * hdr_width) * hdr_channels);
        uint8_t* pixel11 = (pixels_8bit + (x1 + y1 * hdr_width) * hdr_channels);

        // Perform bilinear interpolation for each channel (assuming num_channels = 3 for RGB)
        visibleR = (1 - fracX) * (1 - fracY) * pixel00[0] +
                   (1 - fracX) * fracY * pixel01[0] +
                   fracX * (1 - fracY) * pixel10[0] +
                   fracX * fracY * pixel11[0];

        visibleG = (1 - fracX) * (1 - fracY) * pixel00[1] +
                   (1 - fracX) * fracY * pixel01[1] +
                   fracX * (1 - fracY) * pixel10[1] +
                   fracX * fracY * pixel11[1];

        visibleB = (1 - fracX) * (1 - fracY) * pixel00[2] +
                   (1 - fracX) * fracY * pixel01[2] +
                   fracX * (1 - fracY) * pixel10[2] +
                   fracX * fracY * pixel11[2];
    }

    t_vec4 sky_color;
    sky_color = vec4_create((float)visibleR / 255.0f, (float)visibleG / 255.0f, (float)visibleB / 255.0f, 1.0f);
    return sky_color;
}

// float RandomValue()



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
				t_vec3 intersection_point = point_at_parameter(ray, t);
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
					obj_hit.hit = true;
					obj_hit.hit_distance = t;
					obj_hit.position = point_at_parameter(ray, t);
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
			obj_hit.position = point_at_parameter(ray, closest_hit);
			obj_hit.normal = vec3_normalize(vec3_sub(obj_hit.position, s.spheres[i].center));
			// obj_hit.material.albedo = s.spheres[i].material.albedo;
			obj_hit.material = s.spheres[i].material;
		}
	}
	return (obj_hit);
}


t_vec4 per_pixel(t_ray ray, t_vec2 coord, t_scene s, t_vec2 xy, uint32_t *rngState)
{
	// t_vec2 numPixels = vec2_create((float)WIDTH, (float)HEIGHT);
	// t_vec2 pixelCoord = vec2_mul(coord, numPixels);
	// uint32_t pixelIndex = pixelCoord.x + pixelCoord.y * numPixels.x;
	// uint32_t rngState = pixelIndex;

	// // float rng = randomFloat(pixelIndex);
	// // float rng = randomFloat(&rngState);
	// // return vec4_create(rng, rng, rng, 1.0f);
	// float r = randomFloat(&rngState);
	// float g = randomFloat(&rngState);
	// float b = randomFloat(&rngState);
	// return vec4_create(r, g, b, 1.0f);

	
	// float ret = pixelIndex / (float)(numPixels.x * numPixels.y);
	// t_vec4 frag;
	// frag = vec4_create(ret, ret, ret, 1.0f);
	// return (frag);


	
	t_vec3 color;

	t_obj_hit obj_hit;
	obj_hit.hit_distance = MAXFLOAT;
	obj_hit.hit = false;

	t_sphere* closest_sphere = NULL;
	t_inv_plane* closest_inv_plane = NULL;
	t_inv_plane plane;
	// plane.normal = vec3_create(1.0f, 0.0f, 0.0f);
	// plane.position = vec3_create(-1.0f, 0.0f, 0.0f);

	// float hit_distance = MAXFLOAT;
	


	// for (int i = 0; i < 5; i++)
	// {
	// 	obj_hit = sphere_intersection(ray, s, obj_hit);
	// 	obj_hit = plane_intersection(ray, s, obj_hit);
	// 	if (obj_hit.hit == false)
	// 		break;
	// 	// TODO: relection
	// 	ray.origin = vec3_add(obj_hit.position, vec3_mul_float(obj_hit.normal, 0.001f));
	// 	ray.direction = reflect(ray.direction, obj_hit.normal);
	// 	// ray.direction = random_himisphere_dir(obj_hit.normal, &rngState);
	// 	obj_hit.hit = false;
	// 	obj_hit.hit_distance = MAXFLOAT;
	// }
	// return get_sky_color_int(ray, coord);



	t_vec3 ray_color = vec3_create(1.0f, 1.0f, 1.0f);
	t_vec3 incoming_licht = vec3_create(0.0f, 0.0f, 0.0f);
	int max_bounces = 10;
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
			// ray.direction = reflect(ray.direction, obj_hit.normal);
			ray.direction = random_himisphere_dir(obj_hit.normal, rngState);
	
			t_material material = obj_hit.material;
			t_vec3 emitted_light = vec3_mul_float(material.emission_color, material.emission_intensity);
			incoming_licht = vec3_add(incoming_licht, vec3_mul(ray_color, emitted_light));
			ray_color = vec3_mul(ray_color, material.albedo);
		}
		else
		{
			t_vec4 temp = get_sky_color_int(ray, coord);
			t_vec3 sky_color = vec3_create(temp.x, temp.y, temp.z);
			incoming_licht = vec3_add(incoming_licht, vec3_mul(ray_color, sky_color));
			break;
		}
			

		// return vec4_create(0.2f, 0.7f, 0.2f, 1.0f);
		// return vec4_create(material.emission_color.x, material.emission_color.y, material.emission_color.z, 1.0f);
		// return vec4_create(material.albedo.x, material.albedo.y, material.albedo.z, 1.0f);
	}
	// if (obj_hit.hit == false)
	// {
	// 	return vec4_create(0.0f, 0.0f, 0.0f, 1.0f);
	// 	return vec4_create(0.7f, 0.5f, 0.6f, 1.0f);
	// }
	return vec4_create(incoming_licht.x, incoming_licht.y, incoming_licht.z, 1.0f);









    // Surface color
    color = vec3_add_float(vec3_mul_float(obj_hit.normal, 0.5f), 0.5f);
	
	// color = vec3_create(1.0f, 0.0f, 0.0f);
	
	// return vec4_create(incoming_light.x, incoming_light.y, incoming_light.z, 1.0f);
	return vec4_create(obj_hit.material.albedo.x, obj_hit.material.albedo.y, obj_hit.material.albedo.z, 1.0f);
	return vec4_create(color.x, color.y, color.z, 1.0);
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
			ray.direction = scene.camera.rayDirections[x + y * WIDTH];




			t_vec2 numPixels = vec2_create((float)WIDTH, (float)HEIGHT);
			t_vec2 pixelCoord = vec2_mul(coord, numPixels);
			uint32_t pixelIndex = pixelCoord.x + pixelCoord.y * numPixels.x;
			uint32_t rngState = pixelIndex + total_frames * 719393;




			// coord.x = x;
			// coord.y = y;
			t_vec4 color = per_pixel(ray, coord, d->scene, vec2_create(x, y), &rngState);

			// color = vec4_clamp(color, 0.0, 1.0);
			
			accumulated_data[x + y * WIDTH] = vec4_add(accumulated_data[x + y * WIDTH], color);
			
			t_vec4 accumulated_color = accumulated_data[x + y * WIDTH];
			accumulated_color = vec4_div_float(accumulated_color, accumulated_frames);
			accumulated_color = vec4_clamp(accumulated_color, 0.0, 1.0);

			
			// printf("x: %f\n", color.x);
			// t_vec4 color = per_pixel(coord, d->scene);
			// put_pixel(d->img, x, d->img->height - y, vec4_to_color(color));
			// put_pixel(d->img, x, HEIGHT - y, vec4_to_color(color));
			
			for (int i = 0; i < PIXEL_SIZE; i++)
			{
				for (int j = 0; j < PIXEL_SIZE; j++)
				{
					// put_pixel(d->img, (x * PIXEL_SIZE) + i, \
					// 	((HEIGHT - y - 1) * PIXEL_SIZE) + j, \
					// 	vec4_to_color(color));
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


void recalculate_view(t_mlx *d)
{
	d->scene.camera.view = mat4_look_at(d->scene.camera.position, \
							vec3_add(d->scene.camera.position, d->scene.camera.direction), \
							vec3_create(0.0f, 1.0f, 0.0f));
	d->scene.camera.inv_view = mat4_inverse(d->scene.camera.view);
}

//! Recalculate projection GOOD
void recalculated_projection(t_mlx *d)
{
	d->scene.camera.projection = mat4_perspective(fov_radians(d->scene.camera.verticalFOV), \
								(float)WIDTH / (float)HEIGHT, \
								d->scene.camera.zNear, d->scene.camera.zFar);
	d->scene.camera.inv_projection = mat4_inverse(d->scene.camera.projection);
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
			d->scene.camera.rayDirections[x + y * WIDTH] = rayDirection;
			// printf("rayDirection: %f, %f, %f\n", target.x, target.y, target.z);

			// glm::vec4 target = m_InverseProjection * glm::vec4(coord.x, coord.y, 1, 1);
			// glm::vec3 rayDirection = glm::vec3(m_InverseView * glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0)); // World space
			// m_RayDirections[x + y * m_ViewportWidth] = rayDirection;
		}
		// exit(0);
	}
}

void	movement(t_mlx *d)
{
	bool moved = false;
	bool rotated = false;
	t_vec3 temp;
	t_vec3 up_direction = vec3_create(0.0f, 1.0f, 0.0f);
	t_vec3 right_direction = vec3_cross(d->scene.camera.direction, up_direction);

	float speed = 0.25f;

	if (!mlx_is_mouse_down(d->mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		d->scene.camera.mouse_lock = false;
		d->scene.camera.prevMousePos.x = -1;
		d->scene.camera.prevMousePos.y = -1;
		d->scene.camera.mousePos.x = 0;
		d->scene.camera.mousePos.y = 0;
		return ;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_W)) {
		temp = vec3_mul_float(d->scene.camera.direction, speed);
		d->scene.camera.position = vec3_add(d->scene.camera.position, temp);
		moved = true;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_S)) {
		temp = vec3_mul_float(d->scene.camera.direction, speed);
		d->scene.camera.position = vec3_sub(d->scene.camera.position, temp);
		moved = true;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_A)) {
		temp = vec3_mul_float(right_direction, speed);
		d->scene.camera.position = vec3_sub(d->scene.camera.position, temp);
		moved = true;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_D)) {
		temp = vec3_mul_float(right_direction, speed);
		d->scene.camera.position = vec3_add(d->scene.camera.position, temp);
		moved = true;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_SPACE)) {
		temp = vec3_mul_float(up_direction, speed);
		// d->scene.camera.position = vec3_sub(d->scene.camera.position, temp);
		d->scene.camera.position = vec3_add(d->scene.camera.position, temp);
		moved = true;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT_SHIFT)) {
		temp = vec3_mul_float(up_direction, speed);
		// d->scene.camera.position = vec3_add(d->scene.camera.position, temp);
		d->scene.camera.position = vec3_sub(d->scene.camera.position, temp);
		moved = true;
	}
	if (d->scene.camera.prevMousePos.x >= 0 && d->scene.camera.prevMousePos.y >= 0)
	{
		int x;
		int y;
		mlx_get_mouse_pos(d->mlx, &x, &y);
		d->scene.camera.mousePos = vec2_sub(d->scene.camera.prevMousePos, vec2_create((int)x, (int)y));
		// printf("mousePos: %f, %f\n", d->scene.camera.mousePos.x, d->scene.camera.mousePos.y);
		
		if (d->scene.camera.mousePos.x != d->scene.camera.prevMousePos.x && d->scene.camera.mousePos.y != d->scene.camera.prevMousePos.y)
		{
			// rotated = true;

			d->scene.camera.mouseDelta.x += -1 * d->scene.camera.mousePos.x * 0.12f;
			d->scene.camera.mouseDelta.y +=  d->scene.camera.mousePos.y * 0.12f;
		}
		
	}
	int x;
	int y;
	mlx_get_mouse_pos(d->mlx, &x, &y);
	d->scene.camera.prevMousePos = vec2_create((int)x, (int)y);

	// TODO: rotation

	if (d->scene.camera.mouseDelta.x != 0 || d->scene.camera.mouseDelta.y != 0)
	{
		// printf("HELLO\n");
		float pitch = d->scene.camera.mouseDelta.y * -0.01f;
		float yaw = d->scene.camera.mouseDelta.x * 0.01f;
		
		t_quat pitchRotation = quat_angleAxis(-pitch, right_direction);
		t_quat yawRotation = quat_angleAxis(-yaw, up_direction);
		t_quat q = quat_normalize(quat_cross(pitchRotation, yawRotation));
			
		// Rotate the forward direction using the quaternion
		t_vec3 rotatedForwardDirection = quat_rotate(q, d->scene.camera.direction);
			
		// Update the camera's forward direction
		d->scene.camera.direction = rotatedForwardDirection;
		d->scene.camera.mouseDelta.x = 0;
		d->scene.camera.mouseDelta.y = 0;
		moved = true;
		rotated = true;
	}

	
	// if (mlx_is_key_down(d->mlx, MLX_KEY_DOWN)) {
	// 	d->scene.camera.verticalFOV -= 0.5f;
	// 	recalculated_projection(d);
	// }
	// if (mlx_is_key_down(d->mlx, MLX_KEY_UP)) {
	// 	d->scene.camera.verticalFOV += 0.5f;
	// 	recalculated_projection(d);
	// }
	

	if (moved) {
		accumulated_frames = 1;
		recalculate_view(d);
		if (rotated) {
			recalculat_ray_directions(d);
		}
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

void read_hdr_file(t_mlx *d)
{
	
	const char* filename = "resized_sky_2.jpg";
	// const char* filename = "little_paris_eiffel_tower.jpg";
	// const char* filename = "test.png";
	// int width, height, num_channels;
	// pixels = stbi_loadf(filename, &hdr_width, &hdr_height, &hdr_channels, 0);
	pixels_8 = stbi_load(filename, &hdr_width, &hdr_height, &hdr_channels, 0);
	printf("width: %d, height: %d, channels: %d\n", hdr_width, hdr_height, hdr_channels);

	// if (pixels == NULL) {
	// 	printf("Error in loading the image\n");
	// 	exit(EXIT_FAILURE);
	// }
	float num = 0.0f;
	float num2 = 1.0f;
	// for (int i = 0; i < hdr_width * hdr_height * hdr_channels; i++)
	// {
	// 	if (pixels[i] > num)
	// 		num = pixels[i];
	// 	if (pixels[i] < num2)
	// 		num2 = pixels[i];
	// }
	
	pixels_8bit = malloc(sizeof(uint8_t) * hdr_width * hdr_height * hdr_channels);
	for (int i = 0; i < hdr_width * hdr_height * hdr_channels; i++)
	{
		pixels_8bit[i] = (uint8_t)pixels_8[i];
	}
	
	// printf("%d, %d\n", pixels_8bit[0], pixels_8[0]);
	// exit(0);
	
	// printf("num: %f\n", num);
	// printf("num2: %f\n", num2);
	// printf("%d\n", hdr_width * hdr_height * hdr_channels);

	// for (int y = 0; y < hdr_height; y++) {
	// 	for (int x = 0; x < hdr_width; x++) {
	// 		int index = (y * hdr_width + x) * hdr_channels;
	// 		uint8_t r = pixels_8[index];
	// 		uint8_t g = pixels_8[index + 1];
	// 		uint8_t b = pixels_8[index + 2];
	// 		put_pixel(d->img, x, y, ft_pixel(r, g, b, 255));
	// 	}
	// }
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
	
	read_hdr_file(&data);
	
	// printf("%f %f %f\n", data.scene.camera.direction.x, data.scene.camera.direction.y, data.scene.camera.direction.z);
	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_loop_hook(data.mlx, ft_loop_hook, &data);

	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}