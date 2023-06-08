/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:16:03 by imisumi           #+#    #+#             */
/*   Updated: 2023/06/08 17:35:06 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/shader.h"

#include <sys/time.h>

float change = 0;

// float iTime = gettimeofday(NULL, NULL);

uint32_t ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
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

void	ft_loop_hook(void *param)
{
	t_fdf	*data;

	data = param;
	mainImage(data);
	// draw_background(data);
}

void	mlx_actions(t_fdf *data)
{
	// struct timeval currentTime;
    // gettimeofday(&currentTime, NULL);
	// long int time = currentTime.tv_usec;
    // printf("%ld\n", time);

    // sleep(1);

    // gettimeofday(&currentTime, NULL);
	// float iTime = time - currentTime.tv_usec;
    // // printf("%ld\n", currentTime.tv_usec);
	// printf("%f\n", iTime);

	// printf("%ld\n", currentTime.tv_usec);

	// struct timeval start, end;
    // double elapsed_time;

    // // Start measuring time
    // gettimeofday(&start, NULL);

    // // Call your function
    // sleep(1);

    // // Stop measuring time
    // gettimeofday(&end, NULL);

    // // Calculate the elapsed time in seconds
    // elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    // printf("Elapsed time: %f seconds\n", elapsed_time);


	
	// draw_background(data);
	// test_map(data);

	// mainImage(data);

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
	data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
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
