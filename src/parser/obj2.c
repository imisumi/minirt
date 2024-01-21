/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:16:18 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/21 16:45:43 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#define FAST_OBJ_IMPLEMENTATION
#include "fast_obj.h"

#include "minirt.h"

bool	parse_obj(t_scene *scene, const char *filename)
{
	printf("Parsing obj file: %s\n", filename);
	fastObjMesh *mesh = fast_obj_read(filename);
	int len = mesh->object_count;
	// printf("Mesh has %d groups\n", len);

	int i = mesh->position_count;
	printf("Mesh has %d vertices\n", i);
	i = mesh->normal_count;
	printf("Mesh has %d normals\n", i);
	i = mesh->face_count;
	printf("Mesh has %d faces\n", i);

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
	// t_tri	*tris = malloc(sizeof(t_tri) * faces);
	t_tri	tri;
	// for (int i = 0; i < faces; i++)
	// {
	// 	for (int j = 0; j < 3; j++)
	// 	{
	// 		int index = mesh->indices[i * 3 + j].p;
	// 		// printf("%d\n", index);
	// 		tri.v[j][0] = mesh->positions[index * 3 + 0];
	// 		tri.v[j][1] = mesh->positions[index * 3 + 1];
	// 		tri.v[j][2] = mesh->positions[index * 3 + 2];
	// 		// printf("%f %f %f\n", tri.v[j][0], tri.v[j][1], tri.v[j][2]);
	// 		// exit(1);
	// 	}
	// 	tris[i] = tri;
	// 	// exit(1);
	// }
	// tri_mesh.num_faces = faces;
	// tri_mesh.tris = tris;
	// tri_mesh.material = default_material();
	// vec_push(&scene->tri_meshes, &tri_mesh);

	int face_offset = 0;
	int	mat_offset = 0;
	int num_shapes = mesh->object_count;
	for (int current = 0; current < num_shapes; current++)
	{
		faces = mesh->objects[current].face_count;
		t_tri	*tris = malloc(sizeof(t_tri) * faces);
		for (int i = 0; i < faces; i++)
		{
			// mesh->face_vertices should be 3
			for (int j = 0; j < 3; j++)
			{
				int index = mesh->indices[face_offset + i * 3 + j].p;
				tri.v[j][0] = mesh->positions[index * 3 + 0];
				tri.v[j][1] = mesh->positions[index * 3 + 1];
				tri.v[j][2] = mesh->positions[index * 3 + 2];
			}
			if (mesh->material_count > 0)
			{
				tri.material = default_material();
				int mat_idx = mesh->face_materials[mat_offset + i];
				fastObjMaterial mat = mesh->materials[mat_idx];
				tri.material.color[R] = mat.Kd[0];
				tri.material.color[G] = mat.Kd[1];
				tri.material.color[B] = mat.Kd[2];
			}
			tris[i] = tri;
		}
		tri_mesh.num_faces = faces;
		tri_mesh.tris = tris;
		tri_mesh.material = default_material();
		tri_mesh.material.color[R] = 0.8f;
		tri_mesh.material.color[G] = 0.2f;
		tri_mesh.material.color[B] = 0.2f;
		vec_push(&scene->tri_meshes, &tri_mesh);
		face_offset += mesh->objects[current].face_count * 3;
		mat_offset += mesh->objects[current].face_count;
	}



	return (true);
	// exit(1);
}
