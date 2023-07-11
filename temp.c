/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:59:02 by imisumi           #+#    #+#             */
/*   Updated: 2023/06/27 01:58:02 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include <GLFW/glfw3.h>
# include "lib/MLX42/include/MLX42/MLX42.h"

# define WIDTH 1200
# define HEIGHT 800

typedef float	t_vec3f __attribute__((vector_size(16)));

typedef struct s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct s_mlx
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}				t_mlx;


uint32_t ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	if (x >= 0 && x < image->width && y >= 0 && y < image->height)
		mlx_put_pixel(image, x, y, color);
}

typedef float	t_vec3f __attribute__((vector_size(16)));

t_vec3 vec3_mul_one(t_vec3 *a, float f)
{
    t_vec3 res;
    res.x = a->x * f;
    res.y = a->y * f;
    res.z = a->z * f;
    return res;
}

t_vec3f vec3_mul_two(t_vec3f a, float f)
{
    t_vec3f res;
    res[0] = a[0] * f;
    res[1] = a[1] * f;
    res[2] = a[2] * f;
    return res;
}

t_vec3f vec3_add_two(t_vec3f a, float f)
{
    t_vec3f res;
    res[0] = a[0] + f;
    res[1] = a[1] + f;
    res[2] = a[2] + f;
    return res;
}


void	sky(t_mlx *d)
{
	uint32_t yy = 0;

	t_vec3 one = { 1.0, 1.0, 1.0 };
	t_vec3f two = { 1.0, 1.0, 1.0 };
	
	for (int y = HEIGHT - 1; y >= 0; y--)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			for (int i = 0; i < 1000; i++)
			{
				// one = vec3_mul_one(&one, 1.0001f);
				
				two = vec3_mul_two(two, 1.0001f);
				two = vec3_add_two(two, 0.0001f);
			}
			put_pixel(d->img, x, yy, ft_pixel(25, 234, 123, 255));
		}
		yy++;
	}
	usleep(10000);
}


double previousTime = 0.0;

void	ft_loop_hook(void *param)
{
	t_mlx	*data;

	data = param;
	double currentTime = glfwGetTime();
    double deltaTime = currentTime - previousTime;
	// usleep(1000);
    double frameTimeMs = deltaTime * 1000.0;
	printf("\rframeTimeMs: %.2f ms    ",frameTimeMs);
	// printf("\rFPS: %.2f ms    ",1000 / frameTimeMs);
    fflush(stdout);
	previousTime = currentTime;

	sky(data);
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

	data.mlx = mlx_init(WIDTH, HEIGHT, "Ray Tracer", false);
	if (!data.mlx)
		exit(EXIT_FAILURE);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
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

	mlx_loop_hook(data.mlx, ft_hook, &data);
	mlx_loop_hook(data.mlx, ft_loop_hook, &data);

	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}








// Cylinder intersection function
bool intersect_cylinder(t_ray ray, t_cylinder cylinder, float t_min, float t_max, t_obj_hit* hit)
{
    t_vec3 oc = vec3_sub(ray.origin, cylinder.center);

    float a = vec3_dot(ray.direction, ray.direction) - pow(vec3_dot(ray.direction, cylinder.axis), 2);
    float b = 2.0f * (vec3_dot(ray.direction, oc) - vec3_dot(ray.direction, cylinder.axis) * vec3_dot(oc, cylinder.axis));
    float c = vec3_dot(oc, oc) - pow(vec3_dot(oc, cylinder.axis), 2) - pow(cylinder.radius, 2);

    float discriminant = pow(b, 2) - 4 * a * c;
    if (discriminant > 0)
    {
        float t1 = (-b - sqrtf(discriminant)) / (2 * a);
        float t2 = (-b + sqrtf(discriminant)) / (2 * a);

        if (t1 > t_min && t1 < t_max)
        {
            hit->hit_distance = t1;
            hit->position = point_at_parameter(ray, t1);
            hit->normal = vec3_sub(vec3_sub(hit->position, cylinder.center), \
				vec3_mul_float(cylinder.axis, vec3_dot(vec3_sub(hit->position, cylinder.center), cylinder.axis)));
            return true;
        }

        if (t2 > t_min && t2 < t_max)
        {
            hit->hit_distance = t2;
            hit->position = point_at_parameter(ray, t2);
            hit->normal = vec3_sub(vec3_sub(hit->position, cylinder.center), \
				vec3_mul_float(cylinder.axis, vec3_dot(vec3_sub(hit->position, cylinder.center), cylinder.axis)));
            return true;
        }
    }

    return false;
}

bool intersect_cylinder(t_ray ray, t_cylinder cylinder, float t_min, float t_max, t_obj_hit* hit)
{
    t_vec3 oc = vec3_sub(ray.origin, cylinder.center);

    float a = vec3_dot(ray.direction, ray.direction) - pow(vec3_dot(ray.direction, cylinder.normal), 2);
    float b = 2.0f * (vec3_dot(ray.direction, oc) - vec3_dot(ray.direction, cylinder.normal) * vec3_dot(oc, cylinder.normal));
    float c = vec3_dot(oc, oc) - pow(vec3_dot(oc, cylinder.normal), 2) - pow(cylinder.radius, 2);

    float discriminant = pow(b, 2) - 4 * a * c;
    if (discriminant > 0)
    {
        float t1 = (-b - sqrtf(discriminant)) / (2 * a);
        float t2 = (-b + sqrtf(discriminant)) / (2 * a);

        if (t1 > t_min && t1 < t_max)
        {
            t_vec3 intersection = point_at_parameter(ray, t1);
            float height_top = cylinder.height / 2.0f;
            float height_bottom = -cylinder.height / 2.0f;

            if (intersection.y >= height_bottom && intersection.y <= height_top)
            {
                hit->hit_distance = t1;
                hit->position = intersection;
                hit->normal = vec3_normalize(vec3_sub(intersection, vec3_add(cylinder.center, vec3_mul_float(cylinder.normal, intersection.y))));
                return true;
            }
        }

        if (t2 > t_min && t2 < t_max)
        {
            t_vec3 intersection = point_at_parameter(ray, t2);
            float height_top = cylinder.height / 2.0f;
            float height_bottom = -cylinder.height / 2.0f;

            if (intersection.y >= height_bottom && intersection.y <= height_top)
            {
                hit->hit_distance = t2;
                hit->position = intersection;
                hit->normal = vec3_normalize(vec3_sub(intersection, vec3_add(cylinder.center, vec3_mul_float(cylinder.normal, intersection.y))));
                return true;
            }
        }
    }

    return false;
}





height
for (int i = 0; i < s.nb_cylinders; i++)
{
    t_vec3 oc = vec3_sub(ray.origin, s.cylinders[i].center);
    
    float a = vec3_dot(ray.direction, ray.direction) - powf(vec3_dot(ray.direction, s.cylinders[i].normal), 2);
    float b = 2 * (vec3_dot(oc, ray.direction) - vec3_dot(oc, s.cylinders[i].normal) * vec3_dot(ray.direction, s.cylinders[i].normal));
    float c = vec3_dot(oc, oc) - powf(vec3_dot(oc, s.cylinders[i].normal), 2) - powf(s.cylinders[i].radius, 2);
    
    float discriminant = b * b - 4 * a * c;
    
    if (discriminant >= 0)
    {
        float t1 = (-b - sqrtf(discriminant)) / (2 * a);
        float t2 = (-b + sqrtf(discriminant)) / (2 * a);
        
        if (t1 > 0 && t1 < hit_distance)
        {
            t_vec3 intersection_point = point_at_parameter(ray, t1);
            
            // Check if the intersection point lies within the height range
            float half_height = s.cylinders[i].height / 2.0f;
            if (intersection_point.y >= (s.cylinders[i].center.y - half_height) &&
                intersection_point.y <= (s.cylinders[i].center.y + half_height))
            {
                hit_distance = t1;
                obj_hit.position = intersection_point;
                obj_hit.hit_distance = hit_distance;
                // closest_cylinder = &s.cylinders[i];
            }
        }
        
        if (t2 > 0 && t2 < hit_distance)
        {
            t_vec3 intersection_point = point_at_parameter(ray, t2);
            
            // Check if the intersection point lies within the height range
            float half_height = s.cylinders[i].height / 2.0f;
            if (intersection_point.y >= (s.cylinders[i].center.y - half_height) &&
                intersection_point.y <= (s.cylinders[i].center.y + half_height))
            {
                hit_distance = t2;
                obj_hit.position = intersection_point;
                obj_hit.hit_distance = hit_distance;
                // closest_cylinder = &s.cylinders[i];
            }
        }
    }
}