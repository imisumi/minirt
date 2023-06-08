/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:16:03 by imisumi           #+#    #+#             */
/*   Updated: 2023/06/09 01:21:50 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/shader.h"

#include <sys/time.h>

float change = 0;
t_vec3 light_dir = {-1.0f, -1.0f, 1.0f};

// float iTime = gettimeofday(NULL, NULL);

uint32_t ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t vec4_convert_to_rgba(t_rgba color)
{
	uint8_t r = color.r * 255;
	uint8_t g = color.g * 255;
	uint8_t b = color.b * 255;
	uint8_t a = color.a * 255;
	uint32_t res = ft_pixel(r, g, b, a);
	return (res);
}

uint32_t vec3_convert_to_rgb(t_vec3 color)
{
	uint8_t r = color.x * 255;
	uint8_t g = color.y * 255;
	uint8_t b = color.z * 255;
	uint8_t a = 255;
	uint32_t res = ft_pixel(r, g, b, a);
	return (res);
}

void	ft_mlx_put_pixel(t_fdf *data, int x, int y, uint32_t color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		mlx_put_pixel(data->image, x, y, color);
}

void	draw_background(t_fdf *data)
{
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			ft_mlx_put_pixel(data, x, y, SKY_BLUE);
}



float hit_sphere(t_vec3 center, float radius, t_ray r) {
	t_vec3 oc = vec3_sub(r.a, center);
	float a = dot(r.b, r.b);
	float b = 2.0f * dot(oc, r.b);
	float c = dot(oc, oc) - (radius * radius);
	float discriminant = (b * b) - (4 * a * c);

// 	// return (discriminant > 0);
	
	if (discriminant < 0)
		return -1.0f;
	else
		return (-b - sqrt(discriminant)) / (2.0f * a);
}

t_vec3 color (t_ray r)
{
// 	if (hit_sphere((t_vec3){0, 0, -1}, 0.5, r))
// 		return (t_vec3){1, 0, 0};
// 	t_vec3 unit_direction = r.b;
// 	float t = (unit_direction.y + 1.0) * 0.5;

	
	float t = hit_sphere((t_vec3){0, 0, -1}, 0.5, r);
	// printf("t = %f\n", t);
	if (t > 0.0)
	{
		t_vec3 n = vec3_sub(point_at_parameter(t, r), (t_vec3){0, 0, -1});
		return vec3_mul_float((t_vec3){n.x + 1, n.y + 1, n.z + 1}, 0.5);
	}


	t_vec3 unit_direction = r.b;
	t = (unit_direction.y + 1.0) * 0.5;

	t_vec3 v1 = {1.0, 1.0, 1.0};
	t_vec3 v2 = {0.5, 0.7, 1.0};
	return vec3_add(vec3_mul_float(v1, (1.0f - t)), vec3_mul_float(v2, t));
}

void test_map(t_fdf *data)
{
    t_vec3 lower_left_corner = {-2.0, -1.0, -1.0};
    t_vec3 horizontal = {4.0, 0.0, 0.0};
    t_vec3 vertical = {0.0, 2.0, 0.0};
	t_vec3 origin = {0.0, 0.0, 0.0};
    float u = 0.5;
    float v = 0.5;
	int yy = 0;
	for (int y = HEIGHT - 1; y >= 0; y--) {
		for (int x = 0; x < WIDTH; x++) {
			float u = (float)x / WIDTH;
			float v = (float)y / HEIGHT;

			t_ray r = {origin, vec3_add(lower_left_corner, vec3_add(vec3_mul_float(horizontal, u), vec3_mul_float(vertical, v)))};
			
			t_vec3 col = color(r);
			
		
			int ir = (int)(255.99 * col.x);
			int ig = (int)(255.99 * col.y);
			int ib = (int)(255.99 * col.z);
			ft_mlx_put_pixel(data, x, yy, (ir << 24) | (ig << 16) | (ib << 8) | 255);
		}
		yy++;
	}
}

uint32_t per_pixel(t_coord coord)
{
	uint8_t r = ((uint8_t)roundf(coord.x *  255.99f));
	uint8_t g = ((uint8_t)roundf(coord.y *  255.99f));

	
	// float a = 
	// float b = 
	// float c = 


	return 0xff000000 | (g << 8) | r;
}



// void mainImage(t_data *data)
// {
// 	int x, y;
// 	t_vec2 uv;
// 	t_rgb col;
// 	t_rgba fragColor;

// 	for (y = 0; y < HEIGHT; y++)
// 	{
// 		for (x = 0; x < WIDTH; x++)
// 		{
// 			uv.x = (float)x / WIDTH;
// 			uv.y = (float)y / HEIGHT;

// 			col = 0.5 + 0.5 * cos(uv.xyx + vec3(0, 2, 4));

// 			fragColor.r = col.r;
// 			fragColor.g = col.g;
// 			fragColor.b = col.b;
// 			fragColor.a = 1.0;

// 			drawPixel(data, x, y, *((int*)&fragColor));
// 		}
// 	}
// }

#include <math.h>

void mainImage(t_fdf *data)
{
	// struct timeval end;
    // double elapsed_time;
	// gettimeofday(&end, NULL);
	
	// elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

	// float iTime = 0.0;
    int x, y;
    t_vec2 uv;
    t_vec3 col;
    t_rgba fragColor;
	int yy = 0;

    for (y = HEIGHT - 1; y >= 0; y--)
    {
        for (x = 0; x < WIDTH; x++)
        {
            uv.x = (float)x / WIDTH;
            uv.y = (float)y / HEIGHT;

            col.x = 0.5 + 0.5 * cos(change + uv.x + uv.y + 0);
            col.y = 0.5 + 0.5 * cos(change + uv.x + uv.y + 2);
            col.z = 0.5 + 0.5 * cos(change + uv.x + uv.y + 4);

            // fragColor.r = col.x;
            // fragColor.g = col.y;
            // fragColor.b = col.z;
            // fragColor.a = 1.0;

			fragColor.r = (uint8_t)(col.x * 255.0);
            fragColor.g = (uint8_t)(col.y * 255.0);
            fragColor.b = (uint8_t)(col.z * 255.0);
            fragColor.a = 255;


			// uint32_t color = 0;
            // color |= (uint8_t)(fragColor.a * 255.0) << 24;  // Alpha channel
            // color |= (uint8_t)(fragColor.b * 255.0) << 16;  // Blue channel
            // color |= (uint8_t)(fragColor.g * 255.0) << 8;   // Green channel
            // color |= (uint8_t)(fragColor.r * 255.0); 
			// printf("%d\n", color);
			// color = OCEAN_BLUE;
            // drawPixel(data, x, y, *((int*)&fragColor));
			ft_mlx_put_pixel(data, x, yy, ft_pixel(fragColor.r, fragColor.g, fragColor.b, 255));
			// ft_mlx_put_pixel(data, x, y, *((int*)&fragColor));
        }
		yy++;
    }
	change += 0.05;
}


void hello_world(t_fdf *data)
{
	// float u = 0.5;
	// float v = 0.5;
	// int yy = 0;
	// for (int y = HEIGHT - 1; y >= 0; y--) {
	// 	for (int x = 0; x < WIDTH; x++) {
	// 		float r = (float)x / WIDTH;
	// 		float g = (float)y / HEIGHT;
	// 		float b = 0.2;
	// 		int ir = (int)(r * 255.99);
	// 		int ig = (int)(g * 255.99);
	// 		int ib = (int)(b * 255.99);
	// 		ft_mlx_put_pixel(data, x, yy, (ir << 24) | (ig << 16) | (ib << 8) | 255);
	// 	}
	// 	yy++;
	// }
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			t_coord coord = {x, y};
			t_coord uv = {coord.x / WIDTH, coord.y / HEIGHT};
			// t_coord coord = {(float)x / (float)WIDTH, (float)y / (float)HEIGHT};
			// printf("%f	%f\n", coord.x, coord.y);
			uint32_t color = per_pixel(uv);
			// printf("%x\n", color);
			color = LIGHT_CORAL;
			ft_mlx_put_pixel(data, x, y, color);
			// break;
		}
	}
}

float max(float a, float b) {
    return (a > b) ? a : b;
}


void cherno(t_fdf *data)
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {

			t_vec2 coord = {(float)x / (float)WIDTH, (float)y / (float)HEIGHT};
			//! 0 - 1 -> -1 to 1
			coord.x = (coord.x * 2.0f) - 1.0f;
			coord.y = (coord.y * 2.0f) - 1.0f;
			
			uint8_t r = (uint8_t)(255.0f * coord.x);
			uint8_t g = (uint8_t)(255.0f * coord.y);

			t_vec3 ray_direction = {coord.x, coord.y, -1.0f};
			ray_direction.x *= ASPECT_RATIO;
			t_vec3 ray_origin = {0.0f, 0.0f, 1.0f};
			t_vec3 sphere_origin = {0.0f, 0.0f, 0.0f};
			// t_vec3 light_dir = {-1.0f, -1.0f, -1.0f};
			light_dir = vec3_normalize(light_dir);
			float radius = 0.5f;

			// TODO (bx^2 + by^2)t^2 + (2(axbx + ayby))t + (ax^2 + ay^2 - r^2) = 0
			//? a = ray origin
			//? b = ray direction
			//? r = radius
			//? t = time
			float a = vec3_dot_float(ray_direction, ray_direction);
			float b = 2.0f * vec3_dot_float(ray_origin, ray_direction);
			float c = vec3_dot_float(ray_origin, ray_origin) - (radius * radius);

			// TODO Quadratic formula discriminant:
			// TODO b^2 - 4ac
			// TODO (-b +- sqrt(discriminant)) / (2.0f * a)
			float discriminant = (b * b) - (4.0f * a * c);
			if (discriminant < 0.0f)
				ft_mlx_put_pixel(data, x, HEIGHT - y, vec3_convert_to_rgb((t_vec3){0, 0, 0}));
			else {
				// float t[2];
				// t[0] = (-b - sqrtf(discriminant)) / (2.0f * a);
				// t[1] = (-b + sqrtf(discriminant)) / (2.0f * a);
				// // printf("%f	%f\n", t[0], t[1]);

				// t_vec3 hit_pos[2];
				// t_vec3 normal;
				// for (int i = 0; i < 1; i++) {
				// 	hit_pos[i] = vec3_mul_float(vec3_add(ray_direction, ray_origin), t[i]);
				// 	normal = vec3_sub(hit_pos[i], sphere_origin);
				// }
				
				float t0 = (-b + sqrtf(discriminant)) / (2.0f * a);
				float closest_t = (-b - sqrtf(discriminant)) / (2.0f * a);
				
				t_vec3 hit_pos = vec3_add(ray_origin, vec3_mul_float(ray_direction, closest_t));
				t_vec3 normal = vec3_sub(hit_pos, sphere_origin);
				normal = vec3_normalize(normal);


				float d = max(0.0f, vec3_dot_float(normal, vec3_mul_float(light_dir, -1.0f))); //? == cos(angle)  cos(<90) return negative
				// float d = vec3_dot_float(normal, vec3_mul_float(light_dir, -1.0f)); //? == cos(angle)  cos(<90) return negative

				t_vec3 sphere_color = {1, 0, 1};
			
				//? Sets range to -1 to 1
				// t_vec3 sphere_color = vec3_add_float(vec3_mul_float(normal, 0.5f), 0.5f);
				sphere_color = vec3_mul_float(sphere_color, d);
				uint32_t col = vec3_convert_to_rgb(sphere_color);
				ft_mlx_put_pixel(data, x, HEIGHT - y, col);
				








				
				// for (int i = 0; i < 1; i++) {
				// 	hit_pos[i] = vec3_add(ray_origin, vec3_mul_float(ray_direction, t[i]));
				// 	normal = vec3_sub(hit_pos[i], sphere_origin);
				// }
				// normal = vec3_normalize(normal);
				
				// t_rgba c;
				// c.r = (normal.x * 0.5f + 0.5f) * 255.0f;
				// c.g = (normal.y * 0.5f + 0.5f) * 255.0f;
				// c.b = (normal.z * 0.5f + 0.5f) * 255.0f;
				// c.a = 255;

				// float light = max(0.0f, vec3_dot_float(normal, vec3_mul_float(light_dir, -1.0f)));

				// c.r *= light;
				// c.g *= light;
				// c.b *= light;

				// // ft_mlx_put_pixel(data, x, HEIGHT - y, ft_pixel(c.r, c.g, c.b, c.a));
				
				// t_vec3 c2 = {1, 0, 0};
				// // ft_mlx_put_pixel(data, x, HEIGHT - y, vec3_convert_to_rgb(c2));
			}
			
				
			// uint32_t color = LIGHT_CORAL;
			// color = ft_pixel(r, g, 0, 255);
			// ft_mlx_put_pixel(data, x, HEIGHT - y, color);
		}
	}
	light_dir.z -= 0.03f;
	light_dir.x += 0.03f;
}

void	ft_loop_hook(void *param)
{
	t_fdf	*data;

	data = param;
	cherno(data);
	// mainImage(data);
	// draw_background(data);
}

void	mlx_actions(t_fdf *data)
{

	// draw_background(data);
	// test_map(data);

	// mainImage(data);
	// cherno(data);
	// hello_world(data);
	mlx_key_hook(data->mlx, key_hook, data);
	mlx_loop_hook(data->mlx, ft_loop_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	exit(EXIT_SUCCESS);
}

int32_t	main(int32_t argc, char *argv[])
{
	t_fdf	*data;

	data = ft_calloc(sizeof(t_fdf), 1);
	if (data == NULL)
		exit (EXIT_FAILURE);
	data->mlx = mlx_init(WIDTH, HEIGHT, "Ray Tracer", false);
	if (!data->mlx)
		exit(EXIT_FAILURE);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->image)
	{
		mlx_close_window(data->mlx);
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		exit(EXIT_FAILURE);
	}
	mlx_actions(data);
}
