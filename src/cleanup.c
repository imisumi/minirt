/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:16:18 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/16 19:22:35 by imisumi-wsl      ###   ########.fr       */
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

void	free_all_data(t_data *data)
{
	free(data->scene.camera.ray_dir);
	free(data->utils.accumulated_data);


	//? free scene
	free(data->scene.vertices);
	free(data->scene.tex_coords);
	//TODO free materials

	for (int i = 0; i < data->scene.num_materials; i++)
	{
		t_material *mat = &data->scene.materials[i];

		if (mat->color_tex)
		{
			free(mat->color_tex->pixels);
			free(mat->color_tex);
		}
		if (mat->normal_tex)
		{
			free(mat->normal_tex->pixels);
			free(mat->normal_tex);
		}
	}
	free(data->scene.materials);
	
	vec_free(&data->scene.spheres);

	free_bvh_tree(data->scene.bvh_spheres_f);
	free_bvh_tree(data->scene.bvh_meshes);
	
	for (int i = 0; i < data->scene.num_tri_meshes; i++)
	{
		t_tri_mesh *mesh = &data->scene.tri_meshes[i];
		free(mesh->v_idx);
		free(mesh->vt_idx);
		free(mesh->mat_idx);
		free_bvh_tree(mesh->bvh);
	}
	vec_free(&data->scene.tri_meshes);
	vec_free(&data->scene.inv_planes);
	// vec_free(&data->scene.cylinders);
	vec_free(&data->scene.point_lights);
	free(data->scene.hdri.rgba);
}


// void	free_all_data(t_data *data)
// {
// 	free(data->scene.camera.ray_target);
// 	free(data->scene.camera.ray_dir);
// 	free(data->utils.accumulated_data);


// 	//? free scene
// 	free(data->scene.vertices);
// 	free(data->scene.tex_coords);
// 	//TODO free materials

// 	for (int i = 0; i < data->scene.num_materials; i++)
// 	{
// 		t_material *mat = &data->scene.materials[i];

// 		if (mat->color_tex)
// 		{
// 			free(mat->color_tex->pixels);
// 			free(mat->color_tex);
// 		}
// 		if (mat->normal_tex)
// 		{
// 			free(mat->normal_tex->pixels);
// 			free(mat->normal_tex);
// 		}
// 	}
// 	free(data->scene.materials);
	
// 	vec_free(&data->scene.spheres);
// 	printf("%p\n", data->scene.bvh_spheres_f);
// 	// free_bvh_tree(data->scene.bvh_spheres_f);
// 	// free_bvh_tree(data->scene.bvh_meshes);
// 	for (int i = 0; i < data->scene.num_tri_meshes; i++)
// 	{
// 		t_tri_mesh *mesh = &data->scene.tri_meshes[i];
// 		free(mesh->v_idx);
// 		free(mesh->vt_idx);
// 		free(mesh->mat_idx);
// 		free_bvh_tree(mesh->bvh);
// 	}
// 	vec_free(&data->scene.tri_meshes);
// 	vec_free(&data->scene.inv_planes);
// 	vec_free(&data->scene.cylinders);
// 	vec_free(&data->scene.point_lights);
// 	free(data->scene.hdri.rgba);
// }