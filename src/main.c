/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:16:18 by ichiro            #+#    #+#             */
/*   Updated: 2023/12/20 17:26:52 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int32_t main(int32_t argc, char* argv[])
{
	t_data	data;
	(void)argc;
	(void)argv;

	ft_memset(&data, 0, sizeof(t_data));
	// parse_input(argc, argv, &data);
	// Gotta error check this stuff
	bool resizeble = false;
	if (PIXEL_SIZE == 1)
		resizeble = true;
	data.mlx = mlx_init(WIDTH * PIXEL_SIZE, HEIGHT * PIXEL_SIZE, "Ray Tracer", resizeble);
	if (data.mlx == NULL)
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	data.img = mlx_new_image(data.mlx, data.mlx->width, data.mlx->height);
	if (data.img == NULL)
	{
		mlx_close_window(data.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(data.mlx, data.img, 0, 0) == -1)
	{
		mlx_close_window(data.mlx);
		exit(EXIT_FAILURE);
	}
	data.utils.accumulated_frames = 1;
	data.utils.accumulated_data = malloc(sizeof(t_vec4f) * WIDTH * HEIGHT);
	data.scene.camera.ray_target = malloc(sizeof(t_vec4f) * WIDTH * HEIGHT);
	data.scene.camera.ray_dir = malloc(sizeof(t_vec3f) * WIDTH * HEIGHT);
	mlx_set_window_title(data.mlx, "Testing");

	data.utils.width = WIDTH;
	data.utils.height = HEIGHT;

	init_scene(&data.scene);
	// int x = array_length(&data.scene.spheres);
	// printf("x = %d\n", x);

	
	init_camera(&data.scene.camera);

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

	mlx_loop_hook(data.mlx, render_loop, &data);


	// char *skybox = "./assets/hdri/industrial_sunset_puresky_2k.exr";
	char *skybox = "./assets/hdri/empty_workshop_2k.exr";
	t_hdri hdri;
	// char *skybox = "testing3.exr";
	int w;
	int h;
	const char* err;
	int ret = LoadEXR(&hdri.rgba, &hdri.width, &hdri.height, skybox, &err);
	printf("w: %d\n", w);
	printf("h: %d\n", h);
	data.scene.hdri = hdri;
	// return 1;
	
	
	// mlx_loop_hook(data.mlx, frame_times, &data);

	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
