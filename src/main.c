/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:16:18 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/22 16:50:30 by imisumi          ###   ########.fr       */
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
	[MALLOC_BVH] = "Malloc error in bvh",
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
	vec_free(&scene->spheres);
	vec_free(&scene->inv_planes);
	vec_free(&scene->cylinders);
	vec_free(&scene->point_lights);
}

int32_t main(int32_t argc, char* argv[])
{
	t_data	data;
	(void)argc;
	(void)argv;
	// const char *file = "assets/maps/map1.rt";
	const char *file = "assets/maps/obj.rt";

	*error() = NO_ERROR;
	ft_memset(&data, 0, sizeof(t_data));
	// parse_input(argc, argv, &data);
	// Gotta error check this stuff
	if (data.scene.hdri.rgba == NULL)
		printf("NULL\n");

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

	
	if (parse_map(&data.scene, file) == false)
	{
		// vec_free(&data.scene.spheres);
		print_error("Error");
		cleanup_scene(&data.scene);
		free(data.scene.camera.ray_target);
		free(data.scene.camera.ray_dir);
		free(data.utils.accumulated_data);
		free(data.scene.hdri.rgba);
		return (EXIT_FAILURE);
	}
	if (vec_length(&data.scene.spheres) > 0)
		data.scene.bvh_spheres_f = build_bvh_sphere_f(data.scene.spheres, 0, vec_length(&data.scene.spheres), 100);

	if (data.scene.num_tri_meshes > 0)
	{
		if (build_bvh_triangle(&data.scene) == false)
			exit(1);
	}
	
	// t_aabb temp = data.scene.tri_meshes[0].aabb;
	// printf("aabb min = %f, %f, %f\n", temp.min_f[X], temp.min_f[Y], temp.min_f[Z]);
	// printf("aabb max = %f, %f, %f\n", temp.max_f[X], temp.max_f[Y], temp.max_f[Z]);
	// exit(1);
	printf("check\n");
	int d = vec_length(&data.scene.tri_meshes);
	printf("d = %d\n", d);
	if (*error() == MALLOC_BVH)
	{
		print_error("Error bvh");
		free_bvh_tree(data.scene.bvh_spheres_f);
		cleanup_scene(&data.scene);
		free(data.scene.camera.ray_target);
		free(data.scene.camera.ray_dir);
		free(data.utils.accumulated_data);
		free(data.scene.hdri.rgba);
		return (EXIT_FAILURE);
	}
	*error() = MALLOC_BVH;
	printf("%d\n", *error());
	// printf("start = %d, end = %d\n", data.scene.bvh_spheres_f->start, data.scene.bvh_spheres_f->end);
	// printf("aabb min = %f, %f, %f\n", data.scene.bvh_spheres_f->aabb.min_f[X], data.scene.bvh_spheres_f->aabb.min_f[Y], data.scene.bvh_spheres_f->aabb.min_f[Z]);
	// printf("aabb max = %f, %f, %f\n", data.scene.bvh_spheres_f->aabb.max_f[X], data.scene.bvh_spheres_f->aabb.max_f[Y], data.scene.bvh_spheres_f->aabb.max_f[Z]);
	recalculate_view(&data);
	recalculated_projection(&data);
	recalculat_ray_directions(&data);

	// free_bvh_tree(data.scene.bvh_spheres_f);
	// cleanup_scene(&data.scene);
	// free(data.scene.camera.ray_target);
	// free(data.scene.camera.ray_dir);
	// free(data.utils.accumulated_data);
	// free(data.scene.hdri.rgba);
	// return (EXIT_SUCCESS);

	
	if (setup_mlx(&data) == false)
	{
		print_error("Error");
		return (EXIT_FAILURE);
	}
	mlx_set_window_title(data.mlx, "Testing");
	
	// return (EXIT_SUCCESS);

	// recalculate_view(&data);
	// recalculated_projection(&data);
	// recalculat_ray_directions(&data);

	
	// t_vec3f v = data.scene.spheres[0].pos_f;
	// printf("x = %f, y = %f, z = %f\n", v[X], v[Y], v[Z]);
	// v = data.scene.spheres[0].material.color;
	// printf("x = %f, y = %f, z = %f\n", v[X], v[Y], v[Z]);
	// v = data.scene.camera.position;
	// printf("cam x = %f, y = %f, z = %f\n", v[X], v[Y], v[Z]);


	
	//print ray direction
	// printf("ray dir = %f, %f, %f\n", data.scene.camera.ray_dir[0][X], data.scene.camera.ray_dir[0][Y], data.scene.camera.ray_dir[0][Z]);
	// printf("ray dir = %f, %f, %f\n", data.scene.camera.ray_dir[1][X], data.scene.camera.ray_dir[1][Y], data.scene.camera.ray_dir[1][Z]);

	// mlx_loop_hook(data.mlx, render_loop, &data);


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
