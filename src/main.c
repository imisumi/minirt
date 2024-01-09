/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:16:18 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/09 14:24:12 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_error	*error(void)
{
	static t_error	error;

	return (&error);
}

void	print_error(const char *msg)
{
	const char	*error_strings[ERROR_COUNT] = {
	[NO_ERROR] = "NO_ERROR",
	[STOF] = "String to float error",
	[VEC3_NAN] = "Vec3 is not a number",
	[VEC3_INF] = "Vec3 is infinite",
	[MLX_INIT] = "Mlx init error",
	[MLX_IMG] = "Mlx new image error",
	[MLX_IMG_TO_WIN] = "Mlx image to window error",
	[MAP_INV_TYPE] = "Invalid type in map",
	};

	if (msg && *error() == NO_ERROR)
		printf("%s\n", msg);
	else
		printf("%s: ", msg);
	if (*error() != NO_ERROR)
		printf("%s\n", error_strings[*error()]);
}

bool	setup_mlx(t_data *data)
{
	bool	resizeble;

	resizeble = false;
	if (PIXEL_SIZE == 1)
		resizeble = true;
	data->mlx = mlx_init(WIDTH * PIXEL_SIZE, HEIGHT * PIXEL_SIZE, "Ray Tracer", resizeble);
	if (data->mlx == NULL)
	{
		*error() = MLX_INIT;
		return (false);
	}
	data->img = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height);
	if (data->img == NULL)
	{
		*error() = MLX_IMG;
		mlx_close_window(data->mlx);
		return (false);
	}
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		*error() = MLX_IMG_TO_WIN;
		mlx_close_window(data->mlx);
		return (false);
	}
	return (true);
}

void	cleanup_scene(t_scene *scene)
{
	array_free(&scene->spheres);
	array_free(&scene->inv_planes);
	array_free(&scene->cylinders);
	array_free(&scene->point_lights);
}

int32_t main(int32_t argc, char* argv[])
{
	t_data	data;
	(void)argc;
	(void)argv;
	const char *file = "assets/maps/map1.rt";

	*error() = NO_ERROR;
	ft_memset(&data, 0, sizeof(t_data));
	// parse_input(argc, argv, &data);
	// Gotta error check this stuff


	init_camera(&data.scene.camera);
	data.utils.accumulated_frames = 1;
	data.utils.accumulated_data = malloc(sizeof(t_vec4f) * WIDTH * HEIGHT);
	data.scene.camera.ray_target = malloc(sizeof(t_vec4f) * WIDTH * HEIGHT);
	data.scene.camera.ray_dir = malloc(sizeof(t_vec3f) * WIDTH * HEIGHT);

	data.utils.width = WIDTH;
	data.utils.height = HEIGHT;
	// recalculate_view(&data);
	// recalculated_projection(&data);
	// recalculat_ray_directions(&data);


	// init_scene(&data.scene);
	if (parse_map(&data.scene, file) == false)
	{
		print_error("Error");
		cleanup_scene(&data.scene);
		return (EXIT_FAILURE);
	}
	
	if (setup_mlx(&data) == false)
	{
		print_error("Error");
		return (EXIT_FAILURE);
	}
	mlx_set_window_title(data.mlx, "Testing");

	recalculate_view(&data);
	recalculated_projection(&data);
	recalculat_ray_directions(&data);

	
	t_vec3f v = data.scene.spheres[0].pos_f;
	printf("x = %f, y = %f, z = %f\n", v[X], v[Y], v[Z]);
	v = data.scene.spheres[0].material.color;
	printf("x = %f, y = %f, z = %f\n", v[X], v[Y], v[Z]);
	v = data.scene.camera.position;
	printf("cam x = %f, y = %f, z = %f\n", v[X], v[Y], v[Z]);


	data.scene.bvh_spheres_f = build_bvh_sphere_f(data.scene.spheres, 0, array_length(&data.scene.spheres), 10);
	printf("start = %d, end = %d\n", data.scene.bvh_spheres_f->start, data.scene.bvh_spheres_f->end);
	printf("aabb min = %f, %f, %f\n", data.scene.bvh_spheres_f->aabb.min_f[X], data.scene.bvh_spheres_f->aabb.min_f[Y], data.scene.bvh_spheres_f->aabb.min_f[Z]);
	printf("aabb max = %f, %f, %f\n", data.scene.bvh_spheres_f->aabb.max_f[X], data.scene.bvh_spheres_f->aabb.max_f[Y], data.scene.bvh_spheres_f->aabb.max_f[Z]);

	//print ray direction
	printf("ray dir = %f, %f, %f\n", data.scene.camera.ray_dir[0][X], data.scene.camera.ray_dir[0][Y], data.scene.camera.ray_dir[0][Z]);
	printf("ray dir = %f, %f, %f\n", data.scene.camera.ray_dir[1][X], data.scene.camera.ray_dir[1][Y], data.scene.camera.ray_dir[1][Z]);

	// mlx_loop_hook(data.mlx, render_loop, &data);


	// char *skybox = "./assets/hdri/industrial_sunset_puresky_2k.exr";
	char *skybox = "./assets/hdri/empty_workshop_2k.exr";
	// char *skybox = "./assets/hdri/chinese_garden_4k.exr";
	t_hdri hdri;
	// char *skybox = "testing3.exr";
	int w;
	int h;
	const char* err;
	int ret = LoadEXR(&hdri.rgba, &hdri.width, &hdri.height, skybox, &err);
	printf("w: %d\n", hdri.width);
	printf("h: %d\n", hdri.height);
	data.scene.hdri = hdri;
	// return 1;
	
	
	// mlx_loop_hook(data.mlx, frame_times, &data);

	mlx_loop_hook(data.mlx, render_loop, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	
	cleanup_scene(&data.scene);
	free(data.scene.camera.ray_target);
	free(data.scene.camera.ray_dir);
	free(data.utils.accumulated_data);
	free(data.scene.hdri.rgba);
	
	return (EXIT_SUCCESS);
}
