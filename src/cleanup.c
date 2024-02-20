/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:16:18 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/20 17:01:31 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cleanup_scene(t_scene *scene)
{
	vec_free(&scene->spheres);
	vec_free(&scene->inv_planes);
	// vec_free(&scene->cylinders);
	vec_free(&scene->point_lights);
}

void	free_parser(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->num_materials)
	{
		if (scene->materials[i].color_tex)
			mlx_delete_texture(scene->materials[i].color_tex);
		if (scene->materials[i].normal_tex)
			mlx_delete_texture(scene->materials[i].normal_tex);
		i++;
	}
	free(scene->materials);
	i = 0;
	while (i < scene->num_tri_meshes)
	{
		free(scene->tri_meshes[i].v_idx);
		free(scene->tri_meshes[i].vt_idx);
		free(scene->tri_meshes[i].mat_idx);
		i++;
	}

	free(scene->vertices);
	free(scene->tex_coords);

	vec_free(&scene->spheres);
	vec_free(&scene->inv_planes);
	vec_free(&scene->point_lights);
	vec_free(&scene->tri_meshes);
	free(scene->hdri.rgba);
}
