/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:16:18 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/19 03:16:02 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	init_buffers(t_data *data)
{
	data->utils.width = WIDTH;
	data->utils.height = HEIGHT;
	data->utils.global_frame = 1;
	data->utils.accumulated_frames = 1;
	data->scene.camera.ray_dir = malloc(sizeof(t_vec3f) * WIDTH * HEIGHT);
	data->utils.accumulated_data = malloc(sizeof(t_vec4f) * WIDTH * HEIGHT);
	if (!data->utils.accumulated_data || !data->scene.camera.ray_dir)
		exit_error(MALLOC, "init buffers");
	return (true);
}

bool	init_bvh(t_data *data)
{
	if (!BONUS || !USE_BVH)
		return (print_warning("to use bvh, define BONUS and USE_BVH"));
	if (vec_length(&data->scene.spheres) > 0)
	{
		data->scene.bvh_spheres_f = build_bvh_sphere_f(data->scene.spheres, 0, \
			vec_length(&data->scene.spheres), 1000);
		if (data->scene.bvh_spheres_f == NULL)
			exit_error(MALLOC, "init bvh spheres");
	}
	if (data->scene.num_tri_meshes > 0)
	{
		if (init_mesh_bvh(&data->scene) == false)
			exit_error(MALLOC, "init bvh mesh");
	}
	return (true);
}

bool	valid_input(int argc, char *argv[])
{
	//TODO: 
	return (true);
}

// const char *file = "assets/maps/fresnel.rt";
// const char *file = "assets/maps/obj.rt";
// const char *file = "assets/maps/map1.rt";
const char *file = "assets/maps/uv.rt";

void	temp(t_data *data)
{
	// free_bvh_tree(data->scene.bvh_spheres_f);
}

void	free_data(t_data *data)
{
	//? utils
	free(data->utils.accumulated_data);

	//? scene
	free(data->scene.vertices);
	free(data->scene.tex_coords);
	// free(data->scene.materials);
	int i = 0;
	while (i < data->scene.num_materials)
	{
		mlx_delete_texture(data->scene.materials[i].color_tex);
		mlx_delete_texture(data->scene.materials[i].normal_tex);
		i++;
	}

	vec_free(&data->scene.spheres);
	vec_free(&data->scene.inv_planes);
	
	
	
	// free(data->scene.camera.ray_dir);
	// free(data->utils.accumulated_data);
	// free(data->scene.materials);
	// free(data->scene.point_lights);
	// free(data->scene.inv_planes);
	// free(data->scene.spheres);
	// free(data->scene.tri_meshes);
	// free(data->scene.bvh_spheres_f);
	// free(data->scene.bvh_tri_meshes);
}

int32_t main(int32_t argc, char* argv[])
{
	t_data	data;

	if (valid_input(argc, argv) == false)
		return (print_error("Error"));
	ft_memset(&data, 0, sizeof(t_data));
	init_buffers(&data);
	init_camera(&data.scene.camera);
	if (parse_map(&data.scene, file) == false)
	{
		free_all_data(&data);
		return (print_error("Error"));
	}
	init_bvh(&data);
	recalculate_view(&data);
	recalculated_projection(&data);
	recalculat_ray_directions(&data);
	if (run_mlx(&data) == false)
		return (print_error("Error"));
	free_all_data(&data);
	return (EXIT_SUCCESS);
}
