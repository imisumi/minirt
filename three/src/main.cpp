#include <iostream>
#include "../includes/ray.hpp"
# include "../../lib/MLX42/include/MLX42/MLX42.h"

#define WIDTH 800
#define HEIGHT 400

typedef struct s_fdf
{
	mlx_t		*mlx;
	mlx_image_t	*image;
}	t_fdf;

void	ft_mlx_put_pixel(t_fdf *data, int x, int y, uint32_t color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		mlx_put_pixel(data->image, x, y, color);
}

vec3 color(const ray& r) {
	vec3 unit_dir = unit_vector(r.direction());
	float t = 0.5*(unit_dir.y() + 1.0);
	return (1.0-t)*vec3(1.0,1.0,1.0)+t*vec3(0.5,0.7,1.0);
}

void draw_sky(t_fdf *data)
{
	int yy = 0;
	std::cout << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";
	vec3 lower_left_corner(-2.0,-1.0,-1.0);
	vec3 horizontal(4.0,0.0,0.0);
	vec3 vertical(0.0,2.0,0.0);
	vec3 origin(0.0,0.0,0.0);
	for(int y=HEIGHT-1; y>=00; y--) {
		for(int x=0; x<WIDTH; x++) {
			float u = float(x) / float(WIDTH);
			float v = float(y) / float(HEIGHT);
			ray r(origin, lower_left_corner + u*horizontal + v*vertical);
			vec3 col = color(r);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			std::cout << ir << " " << ig << " " << ib << "\n";
			ft_mlx_put_pixel(data, x, yy, (ir << 24) | (ig << 16) | (ib << 8) | 255);
		}
		yy++;
	}
}

void	key_hook(mlx_key_data_t key, void *param)
{
	t_fdf* data = static_cast<t_fdf*>(param);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->mlx);
		exit(EXIT_SUCCESS);
	}
}

void	mlx_actions(t_fdf *data)
{
	draw_sky(data);
	mlx_key_hook(data->mlx, key_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	exit(EXIT_SUCCESS);
}

int main() {
	t_fdf	data;

	data.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
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
	// draw_sky(&data);
	mlx_actions(&data);
	return 0;
}
