/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:16:18 by ichiro            #+#    #+#             */
/*   Updated: 2024/03/07 18:25:02 by imisumi-wsl      ###   ########.fr       */
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

//TODO
bool	valid_input(int argc, char *argv[])
{
	return (true);
}

void	null_init(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->utils.accumulated_data = NULL;
	data->scene.vertices = NULL;
	data->scene.tex_coords = NULL;
	data->scene.materials = NULL;
	data->scene.spheres = NULL;
	data->scene.inv_planes = NULL;
	data->scene.bvh_spheres_f = NULL;
	data->scene.bvh_meshes = NULL;
	data->scene.tri_meshes = NULL;
	data->scene.point_lights = NULL;
	data->scene.hdri.rgba = NULL;
	data->scene.num_materials = 0;
	//TODO - implement in parser
	data->scene.sky = RENDER_SKYBOX;
}

const char	*get_path(void)
{
	
	const char	*file1 = "assets/maps/fresnel.rt"; // render skybox - false
	const char	*file2 = "assets/maps/obj.rt";
	const char	*file3 = "assets/maps/owl.rt";
	const char	*file4 = "assets/maps/map1.rt";
	const char	*file5 = "assets/maps/uv.rt";
	const char	*file6 = "assets/maps/cy.rt";
	return (file6);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (valid_input(argc, argv) == false)
		return (print_error("Error"));
	null_init(&data);
	init_camera(&data.scene.camera);
	if (parse_map(&data.scene, get_path()) == false)
	{
		free_parser(&data.scene);
		exit_error(*error(), "parse map");
	}
	init_buffers(&data);
	init_bvh(&data);
	recalculate_view(&data);
	recalculated_projection(&data);
	recalculat_ray_directions(&data);
	if (run_mlx(&data) == false)
		return (print_error("Error"));
	return (EXIT_SUCCESS);
}
