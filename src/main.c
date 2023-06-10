/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:16:03 by imisumi           #+#    #+#             */
/*   Updated: 2023/06/09 20:53:54 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
// #include "../includes/shader.h"
#include <math.h>

#include <sys/time.h>

float change = 0;


void rainbow(t_fdf *data)
{
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
			fragColor.r = (uint8_t)(col.x * 255.0);
            fragColor.g = (uint8_t)(col.y * 255.0);
            fragColor.b = (uint8_t)(col.z * 255.0);
            fragColor.a = 255;
			ft_mlx_put_pixel(data, x, yy, ft_pixel(fragColor.r, fragColor.g, fragColor.b, 255));
        }
		yy++;
    }
	change += 0.05;
}

t_vec4 trace_ray(t_vec2 coord)
{
	t_vec3 ray_origin = {0.0f, 0.0f, 1.0f};
	t_vec3 ray_direction = {coord.x * ASPECT_RATIO, coord.y, -1.0f};
	// ray_direction.x *= ASPECT_RATIO;
	t_vec3 sphere_origin = {0.0f, 0.0f, 0.0f};
	t_vec3 light_dir = {-1.0f, -1.0f, -1.0f};
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
	if (discriminant < 0.0f) {
		return (t_vec4){0, 0, 0, 1};
	}
	else {
		float t0 = (-b + sqrtf(discriminant)) / (2.0f * a);
		float closest_t = (-b - sqrtf(discriminant)) / (2.0f * a);
		
		t_vec3 hit_pos = vec3_add(ray_origin, vec3_mul_float(ray_direction, closest_t));
		t_vec3 normal = vec3_normalize(vec3_sub(hit_pos, sphere_origin));

		float d = max(0.0f, vec3_dot_float(normal, vec3_mul_float(light_dir, -1.0f))); //? == cos(angle)  cos(<90) return negative
	
		//? Sets range to -1 to 1
		t_vec3 sphere_color = vec3_add_float(vec3_mul_float(normal, 0.5f), 0.5f);
		sphere_color = vec3_mul_float(sphere_color, d);
		return vec3_to_vec4(sphere_color, 1.0f);
	}
}

void cherno(t_fdf *data)
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {

			t_vec2 coord = {(float)x / (float)WIDTH, (float)y / (float)HEIGHT};
			//! 0 - 1 -> -1 to 1
			coord.x = (coord.x * 2.0f) - 1.0f;
			coord.y = (coord.y * 2.0f) - 1.0f;
			
			t_vec4 color = trace_ray(coord);
			ft_mlx_put_pixel(data, x, HEIGHT - y, vec4_to_int32_color(color));
		}
	}
}


// void mlx_get_mouse_pos(mlx_t* mlx, int32_t* x, int32_t* y)
// void cursor_test(t_fdf *data)
// {
// 	uint32_t x;
// 	uint32_t y;
// 	mlx_get_mouse_pos(data->mlx, &x, &y);
// 	printf("x: %d, y: %d\n", x, y);

	
// }

void	set_mouse_param(mouse_key_t button, action_t action, \
	modifier_key_t mods, void *param)
{
	t_fdf *data;
	// int x;
	// int y;

	data = param;
	// data->mouse.x_prev = data->mouse.x;
	// data->mouse.y_prev = data->mouse.y;
	// mlx_get_mouse_pos(data->mlx, &(data->mouse.x), &(data->mouse.y));
	data->mouse.button = button;
	data->mouse.action = action;
	data->mouse.mods = mods;
}

void test(t_fdf *data)
{
	// data->mouse.x = 0;
	// data->mouse.y = 0;

	
	// printf("%d	%d\n", data->mouse.x, data->mouse.x_prev);
	// printf("%d	%d\n", data->mouse.button, data->mouse.action);
}

void	ft_loop_hook(void *param)
{
	t_fdf	*data;
	int x, y;
	
	data = param;
	data->mouse.x_prev = data->mouse.x;
	data->mouse.y_prev = data->mouse.y;
	mlx_get_mouse_pos(data->mlx, &(data->mouse.x), &(data->mouse.y));
	cherno(data);
	test(data);
	on_update(data);
	// cursor_test(data);
	// rainbow(data);
}

void	mlx_actions(t_fdf *data)
{
	camera(data, 45.0f, 0.1f, 100.0f);
	mlx_key_hook(data->mlx, key_hook, data);
	mlx_mouse_hook(data->mlx, set_mouse_param, data);
	mlx_loop_hook(data->mlx, ft_loop_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	exit(EXIT_SUCCESS);
}

// int32_t	main(int32_t argc, char *argv[])
// {
// 	t_fdf	data;

// 	// data = ft_calloc(sizeof(t_fdf), 1);
// 	// if (data == NULL)
// 	// 	exit (EXIT_FAILURE);

// 	// data->mouse->x = malloc(sizeof(int) * 1);
// 	// data->mouse->y = malloc(sizeof(int) * 1);
// 	data->mlx = mlx_init(WIDTH, HEIGHT, "Ray Tracer", false);
// 	if (!data->mlx)
// 		exit(EXIT_FAILURE);
// 	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
// 	if (!data->image)
// 	{
// 		mlx_close_window(data->mlx);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
// 	{
// 		mlx_close_window(data->mlx);
// 		exit(EXIT_FAILURE);
// 	}
// 	mlx_actions(data);
// }

void setup(t_fdf *data)
{
	data->camera.projection = create_mat4(1.0f);
	data->camera.view = create_mat4(1.0f);
	data->camera.inv_projection = create_mat4(1.0f);
	data->camera.inv_projection = create_mat4(1.0f);

	data->camera.vertical_fov = 45.0f;
	data->camera.near_clip = 0.1f;
	data->camera.far_clip = 100.0f;

	data->camera.rotation_speed = 0.3f;
	
	data->camera.pos = (t_vec3){0.0f, 0.0f, 0.0f};
	data->camera.for_dir = (t_vec3){0.0f, 0.0f, 0.0f};
}

int32_t	main(int32_t argc, char *argv[])
{
	t_fdf	data;

	setup(&data);

	// data = ft_calloc(sizeof(t_fdf), 1);
	// if (data == NULL)
	// 	exit (EXIT_FAILURE);

	// data->mouse->x = malloc(sizeof(int) * 1);
	// data->mouse->y = malloc(sizeof(int) * 1);
	data.mlx = mlx_init(WIDTH, HEIGHT, "Ray Tracer", false);
	if (!data.mlx)
		exit(EXIT_FAILURE);
	data.image = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	if (!data.image)
	{
		mlx_close_window(data.mlx);
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(data.mlx, data.image, 0, 0) == -1)
	{
		mlx_close_window(data.mlx);
		exit(EXIT_FAILURE);
	}
	mlx_actions(&data);
}
