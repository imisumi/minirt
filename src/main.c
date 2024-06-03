/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:16:18 by ichiro            #+#    #+#             */
/*   Updated: 2024/06/03 12:24:34 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_file_extension(const char *file, const char *ext)
{
	size_t	i;
	size_t	len;
	size_t	ext_len;

	len = ft_strlen(file);
	ext_len = ft_strlen(ext);
	if (len < ext_len)
		return (false);
	i = 0;
	while (i < ext_len)
	{
		if (file[len - ext_len + i] != ext[i])
			return (false);
		i++;
	}
	return (true);
}

bool	valid_input(int argc, char **argv)
{
	if (argc != 2)
	{
		*error() = ARGC;
		return (false);
	}
	if (check_file_extension(argv[1], ".rt") == false)
	{
		*error() = FILE_EXT;
		return (false);
	}
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
	data->scene.sky = RENDER_SKYBOX;
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (valid_input(argc, argv) == false)
		return (print_error("Error"));
	null_init(&data);
	init_camera(&data.scene.camera);
	if (parse_map(&data.scene, argv[1]) == false)
		exit_error(*error(), "parse map");
	init_buffers(&data);
	init_bvh(&data);
	recalculate_view(&data);
	recalculated_projection(&data);
	recalculat_ray_directions(&data);
	if (run_mlx(&data) == false)
		return (print_error("Error"));
	return (EXIT_SUCCESS);
}
