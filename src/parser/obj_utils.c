/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/06/03 12:36:33 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "fast_obj.h"

// copy float array
float	*copy_float_array(float *arr, uint32_t len)
{
	uint32_t	i;
	float		*new_arr;

	new_arr = malloc(sizeof(float) * len);
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_arr[i] = arr[i];
		i++;
	}
	return (new_arr);
}

// void	print_mesh_data(fastObjMesh *mesh)
// {
// 	printf("----------------------------------\n");
// 	printf("Mesh has %d objects\n", mesh->object_count);
// 	printf("Mesh has %d indices\n", mesh->index_count);
// 	printf("Mesh has %d vertices\n", mesh->position_count);
// 	printf("Mesh has %d texcoords\n", mesh->texcoord_count);
// 	printf("Mesh has %d normals\n", mesh->normal_count);
// 	printf("Mesh has %d faces\n", mesh->face_count);
// 	printf("Mesh has %d materials\n", mesh->material_count);
// 	printf("----------------------------------\n");
// }

bool	load_texture(mlx_texture_t **tex, const char *path)
{
	if (!path)
	{
		*tex = NULL;
		return (true);
	}
	*tex = mlx_load_png(path);
	if (!*tex)
		return (false);
	return (true);
}
