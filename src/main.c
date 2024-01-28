/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:16:18 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/29 00:42:44 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	init_buffers(t_data *data)
{
	data->utils.width = WIDTH;
	data->utils.height = HEIGHT;
	data->utils.accumulated_frames = 1;
	data->utils.accumulated_data = malloc(sizeof(t_vec4f) * WIDTH * HEIGHT);
	if (data->utils.accumulated_data == NULL)
	{
		free_all_data(data);
		return (false);
	}
	data->scene.camera.ray_target = malloc(sizeof(t_vec4f) * WIDTH * HEIGHT);
	if (data->scene.camera.ray_target == NULL)
	{
		free_all_data(data);
		return (false);
	}
	data->scene.camera.ray_dir = malloc(sizeof(t_vec3f) * WIDTH * HEIGHT);
	if (data->scene.camera.ray_dir == NULL)
	{
		free_all_data(data);
		return (false);
	}
	return (true);
}

bool	init_bvh(t_data *data)
{
	// *error() = MALLOC_BVH;
	// return false;
	if (!BONUS || !USE_BVH)
		return (print_warning("to use bvh, define BONUS and USE_BVH"));
	if (vec_length(&data->scene.spheres) > 0)
	{
		data->scene.bvh_spheres_f = build_bvh_sphere_f(data->scene.spheres, 0, \
			vec_length(&data->scene.spheres), 1000);
		if (data->scene.bvh_spheres_f == NULL)
		{
			*error() = MALLOC_BVH;
			return (false);
		}
	}
	if (data->scene.num_tri_meshes > 0)
	{
		if (init_mesh_bvh(&data->scene) == false)
		{
			*error() = MALLOC_BVH;
			return (false);
		}
	}
	return (true);
}

bool	valid_input(int argc, char *argv[])
{
	//TODO: 
	return (true);
}

const char *file = "assets/maps/obj.rt";
// const char *file = "assets/maps/map1.rt";

void	temp(t_data *data)
{
	free_bvh_tree(data->scene.bvh_spheres_f);
}

int32_t main(int32_t argc, char* argv[])
{
	t_data	data;

	if (valid_input(argc, argv) == false)
		return (print_error("Error"));
	*error() = NO_ERROR;
	ft_memset(&data, 0, sizeof(t_data));
	init_camera(&data.scene.camera);
	init_buffers(&data);
	if (parse_map(&data.scene, file) == false)
	{
		free_all_data(&data);
		return (print_error("Error"));
	}
	if (init_bvh(&data) == false)
	{
		free_all_data(&data);
		return (print_error("Error"));
	}
	// return (EXIT_SUCCESS);
	if (*error() == MALLOC_BVH)
	{
		free_all_data(&data);
		return (print_error("Error bvh"));
	}
	recalculate_view(&data);
	recalculated_projection(&data);
	recalculat_ray_directions(&data);
	if (run_mlx(&data) == false)
		return (print_error("Error"));
	free_all_data(&data);
	return (EXIT_SUCCESS);
}
