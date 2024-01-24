/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:16:18 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/24 01:56:16 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#define FAST_OBJ_IMPLEMENTATION
#include "fast_obj.h"

#include "minirt.h"

// copy float array
float *copy_float_array(float *arr, int len)
{
	float *new_arr = malloc(sizeof(float) * len);
	for (int i = 0; i < len; i++)
		new_arr[i] = arr[i];
	return (new_arr);
}

bool	parse_obj(t_scene *scene, const char *filename)
{
	printf("Parsing obj file: %s\n", filename);
	fastObjMesh *mesh = fast_obj_read(filename);
	int len = mesh->object_count;
	// printf("Mesh has %d groups\n", len);

	int i = mesh->position_count;
	printf("Mesh has %d vertices\n", i);
	i = mesh->texcoord_count;
	printf("Mesh has %d texcoords\n", i);
	i = mesh->normal_count;
	printf("Mesh has %d normals\n", i);
	i = mesh->face_count;
	printf("Mesh has %d faces\n", i);
	i = mesh->material_count;
	printf("Mesh has %d materials\n", i);

	if (mesh->material_count > 0)
	{
		scene->materials = malloc(sizeof(t_material) * mesh->material_count);
	}
	else
	{
		scene->materials = malloc(sizeof(t_material));
		scene->materials[0] = default_material();
	}
	for (int i = 0; i < mesh->material_count; i++)
	{
		fastObjMaterial mat = mesh->materials[i];
		scene->materials[i] = default_material();
		scene->materials[i].color[R] = mat.Kd[0];
		scene->materials[i].color[G] = mat.Kd[1];
		scene->materials[i].color[B] = mat.Kd[2];

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
	t_vec3f m = scene->materials[0].color;
	printf("Material color: %f %f %f\n", m[0], m[1], m[2]);

	int faces = mesh->face_count;
	// for (int i = 0; i < faces; i++)
	// {
		
	// }


	int pos = mesh->position_count;
	for (int i = 0; i < pos; i++)
	{
		// printf("Vertex %d: %f %f %f\n", i, mesh->positions[i * 3 + 0], mesh->positions[i * 3 + 1], mesh->positions[i * 3 + 2]);
	}
	int index = mesh->index_count;
	printf("Mesh has %d indices\n", index);
	// for (int i = 0; i < index; i++)
	// {
	// 	fastObjIndex id = mesh->indices[i];
	// 	printf("%d %d %d     ", id.p, id.t, id.n);
	// 	if (i % 3 == 2)
	// 		printf("\n");
	// }

	int count = mesh->object_count;
	printf("Mesh has %d objects\n", count);
	scene->num_tri_meshes = count;

	t_tri_mesh tri_mesh;
	scene->vertices = copy_float_array(mesh->positions, mesh->position_count * 3);
	scene->tex_coords = copy_float_array(mesh->texcoords, mesh->texcoord_count * 2);

	int face_offset = 0;
	int	mat_offset = 0;
	int num_shapes = mesh->object_count;
	for (int current = 0; current < num_shapes; current++)
	{
		faces = mesh->objects[current].face_count;
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
	return (true);
}
