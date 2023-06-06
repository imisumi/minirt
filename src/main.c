/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:16:03 by imisumi           #+#    #+#             */
/*   Updated: 2023/06/07 00:31:01 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// void	ft_mlx_put_pixel(t_fdf *data, int x, int y, uint32_t color)
// {
// 	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
// 		mlx_put_pixel(data->image, x, y, color);
// }

// void	draw_background(t_fdf *data)
// {
// 	for (int y = 0; y < HEIGHT; y++)
// 		for (int x = 0; x < WIDTH; x++)
// 			ft_mlx_put_pixel(data, x, y, SKY_BLUE);
// }

// void	ft_loop_hook(void *param)
// {
// 	t_fdf	*data;

// 	data = param;
// 	draw_background(data);
// }

// void	mlx_actions(t_fdf *data)
// {
// 	mlx_key_hook(data->mlx, key_hook, data);
// 	mlx_loop_hook(data->mlx, ft_loop_hook, data);
// 	mlx_loop(data->mlx);
// 	mlx_terminate(data->mlx);
// 	exit(EXIT_SUCCESS);
// }

// int32_t	main(int32_t argc, char *argv[])
// {
// 	t_fdf	*data;

// 	data = ft_calloc(sizeof(t_fdf), 1);
// 	if (data == NULL)
// 		exit (EXIT_FAILURE);
// 	data->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
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

typedef struct {
    double x;
    double y;
    double z;
} Vec3;

typedef struct {
    Vec3 center;
    double radius;
} Sphere;

typedef struct {
    Vec3 origin;
    Vec3 direction;
} Ray;

void rayColor(const Ray *ray, const Sphere *sphere, unsigned char *color) {
    Vec3 oc = {ray->origin.x - sphere->center.x, ray->origin.y - sphere->center.y, ray->origin.z - sphere->center.z};
    double a = ray->direction.x * ray->direction.x + ray->direction.y * ray->direction.y + ray->direction.z * ray->direction.z;
    double b = 2.0 * (oc.x * ray->direction.x + oc.y * ray->direction.y + oc.z * ray->direction.z);
    double c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - sphere->radius * sphere->radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        double t = (-b - sqrt(discriminant)) / (2.0 * a);
        if (t > 0.001) {
            Vec3 hitPoint = {ray->origin.x + t * ray->direction.x, ray->origin.y + t * ray->direction.y,
                             ray->origin.z + t * ray->direction.z};
            color[0] = (unsigned char) (255.0 * hitPoint.x);
            color[1] = (unsigned char) (255.0 * hitPoint.y);
            color[2] = (unsigned char) (255.0 * hitPoint.z);
            return;
        }
    }

    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
}

void render(const Sphere *sphere, int width, int height, t_fdf *d) {
    // unsigned char *buffer = mlx_get_data_addr(img, &(int){0}, &(int){0}, &(int){0});
	// // d->image->pixels
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Ray ray;
            ray.origin.x = 0.0;
            ray.origin.y = 0.0;
            ray.origin.z = 0.0;
            ray.direction.x = (2.0 * x - width) / width;
            ray.direction.y = (height - 2.0 * y) / height;
            ray.direction.z = -1.0;
            unsigned char color[3];
            rayColor(&ray, sphere, color);
            int index = (y * width + x) * 4;
            uint8_t r = color[2];  // Blue
            uint8_t g = color[1];  // Green
            uint8_t b = color[0];  // Red
            uint8_t a = 0;         // Alpha (transparency)
			mlx_put_pixel(d->image, x, y, \
					((r << 24) | (g << 16) | (b << 8) | a));
        }
    }
}

void	ft_mlx_put_pixel(t_fdf *data, int x, int y, uint32_t color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		mlx_put_pixel(data->image, x, y, color);
}

void draw_background(t_fdf *d) {
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            ft_mlx_put_pixel(d, x, y, SKY_BLUE);
}

void ft_loop_hook(void *param) {
	t_fdf	*data;

	data = param;
	
    draw_background(data);

    Sphere sphere;
    sphere.center.x = 0.0;
    sphere.center.y = 0.0;
    sphere.center.z = -5.0;
    sphere.radius = 1.0;

    render(&sphere, WIDTH, HEIGHT, data);
}

void mlx_actions(t_fdf *data) {
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
