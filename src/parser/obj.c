/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:16:18 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/24 15:11:30 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#define FAST_OBJ_IMPLEMENTATION
#include "fast_obj.h"

#include "minirt.h"

// copy float array
float	*copy_float_array(float *arr, int len)
{
	int		i;
	float	*new_arr;

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

void	print_mesh_data(fastObjMesh *mesh)
{
	printf("----------------------------------\n");
	printf("Mesh has %d objects\n", mesh->object_count);
	printf("Mesh has %d indices\n", mesh->index_count);
	printf("Mesh has %d vertices\n", mesh->position_count);
	printf("Mesh has %d texcoords\n", mesh->texcoord_count);
	printf("Mesh has %d normals\n", mesh->normal_count);
	printf("Mesh has %d faces\n", mesh->face_count);
	printf("Mesh has %d materials\n", mesh->material_count);
	printf("----------------------------------\n");
}

bool	load_mesh_materials(t_scene *scene, fastObjMesh *mesh)
{
	if (mesh->material_count > 0)
	{
		scene->materials = malloc(sizeof(t_material) * mesh->material_count);
		if (!scene->materials)
			return (false);
	}
	else
	{
		scene->materials = malloc(sizeof(t_material));
		if (!scene->materials)
			return (false);
		scene->materials[0] = default_material();
	}
	
	
	return (true);
}

bool	parse_obj(t_scene *scene, const char *filename)
{
	static int	obj_count = 0;
	if (obj_count > 0)
		return (false);
	printf("Parsing obj file: %s\n", filename);
	fastObjMesh *mesh = fast_obj_read(filename);
	if (!mesh)
	{
		printf("Error: failed to load obj file\n");
		return (false);
	}

	print_mesh_data(mesh);

	if (load_mesh_materials(scene, mesh) == false)
		return (false);

	for (int i = 0; i < mesh->material_count; i++)
	{
		fastObjMaterial mat = mesh->materials[i];
		scene->materials[i] = default_material();
		scene->materials[i].color[R] = mat.Kd[0];
		scene->materials[i].color[G] = mat.Kd[1];
		scene->materials[i].color[B] = mat.Kd[2];

		scene->materials[i].emission_color[R] = mat.Ke[0];
		scene->materials[i].emission_color[G] = mat.Ke[1];
		scene->materials[i].emission_color[B] = mat.Ke[2];
		if (mat.Ke[0] > 0.0f || mat.Ke[1] > 0.0f || mat.Ke[2] > 0.0f)
			scene->materials[i].emission_strength = 10.0f;

		// if (scene->materials[i].color_tex == NULL)
		// 	exit(1);

		char *mat_name = mesh->materials[i].map_Kd.name;
		char *mat_path = mesh->materials[i].map_Kd.path;
		printf("Material name: %s, %s\n", mat_name, mat_path);
		if (mat_path)
			scene->materials[i].color_tex = mlx_load_png(mat_path);
		mlx_texture_t *tex = scene->materials[i].color_tex;
		if (tex)
			printf("Texture size: %d %d\n", tex->width, tex->height);
		
		char *mat_normal = mesh->materials[i].map_bump.name;
		char *mat_normal_path = mesh->materials[i].map_bump.path;
		printf("Material normal: %s, %s\n", mat_normal, mat_normal_path);
		
		if (mat_normal_path)
			scene->materials[i].normal_tex = mlx_load_png(mat_normal_path);
		// char *normal = "assets/obj/tex/normal.png";
		// scene->materials[i].normal_tex = mlx_load_png(normal);
	}



	scene->num_tri_meshes = mesh->object_count;

	t_tri_mesh tri_mesh;
	scene->vertices = copy_float_array(mesh->positions, mesh->position_count * 3);
	scene->tex_coords = copy_float_array(mesh->texcoords, mesh->texcoord_count * 2);

	int face_offset = 0;
	int	mat_offset = 0;
	int num_shapes = mesh->object_count;
	for (int current = 0; current < num_shapes; current++)
	{
		int faces = mesh->objects[current].face_count;
		tri_mesh.mat_idx = malloc(sizeof(uint32_t) * faces);
		tri_mesh.v_idx = malloc(sizeof(t_vec3ui) * faces);
		tri_mesh.vt_idx = malloc(sizeof(t_vec3ui) * faces);
		for (int i = 0; i < faces; i++)
		{
			// mesh->face_vertices should be 3
			for (int j = 0; j < 3; j++)
			{
				int index = mesh->indices[face_offset + i * 3 + j].p;
				
				tri_mesh.v_idx[i][j] = index;
				// printf("%d/", index);
				index = mesh->indices[face_offset + i * 3 + j].t;
				tri_mesh.vt_idx[i][j] = index;
				// printf("%d\t", index);
			}
			// printf("\n");
			if (mesh->material_count > 0)
			{
				int mat_idx = mesh->face_materials[mat_offset + i];
				tri_mesh.mat_idx[i] = mat_idx;
				// printf("mat_idx = %d\n", mat_idx);
			}
		}
		tri_mesh.num_faces = faces;
		vec_push(&scene->tri_meshes, &tri_mesh);
		face_offset += mesh->objects[current].face_count * 3;
		mat_offset += mesh->objects[current].face_count;
	}


	// for (int i = 2; i < mesh->texcoord_count * 2; i+=2)
	// {
	// 	printf("Texcoord %d: %f %f\n", i, scene->tex_coords[i], scene->tex_coords[i + 1]);
	// 	if (i % 3 == 2)
	// 		printf("\n");
	// }
	obj_count++;
	return (true);
}
