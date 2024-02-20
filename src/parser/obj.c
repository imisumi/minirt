/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:16:18 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/20 17:11:40 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FAST_OBJ_IMPLEMENTATION
#include "fast_obj.h"

#include "minirt.h"

static bool	load_mesh_materials(t_scene *scene, fastObjMesh *mesh)
{
	scene->num_materials = mesh->material_count;
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

//TODO: other matrial properties
static bool	get_mesh_materials(t_scene *scene, fastObjMesh *mesh)
{
	int				i;
	fastObjMaterial	mat;

	i = 0;
	while (i < mesh->material_count)
	{
		mat = mesh->materials[i];
		scene->materials[i] = default_material();
		scene->materials[i].color = (t_vec3f) \
			{mat.Kd[0], mat.Kd[1], mat.Kd[2]};
		scene->materials[i].emission_color = (t_vec3f) \
			{mat.Ke[0], mat.Ke[1], mat.Ke[2]};
		if (mat.Ke[0] > 0.0f || mat.Ke[1] > 0.0f || mat.Ke[2] > 0.0f)
			scene->materials[i].emission_strength = 10.0f;
		if (load_texture(&scene->materials[i].color_tex, mesh->materials[i].map_Kd.path) == false)
			return (false);
		if (load_texture(&scene->materials[i].normal_tex, mesh->materials[i].map_bump.path) == false)
			return (false);
		i++;
	}
	return (true);
}

// mesh->face_vertices should be 3
static void	load_faces(int faces, int face_mat_offset[2], \
	fastObjMesh *mesh, t_tri_mesh tri_mesh)
{
	int	i;
	int	j;
	int	index;

	i = 0;
	while (i < faces)
	{
		j = 0;
		while (j < 3)
		{
			index = mesh->indices[face_mat_offset[0] + i * 3 + j].p;
			tri_mesh.v_idx[i][j] = index;
			index = mesh->indices[face_mat_offset[0] + i * 3 + j].t;
			tri_mesh.vt_idx[i][j] = index;
			j++;
		}
		if (mesh->material_count > 0)
		{
			index = mesh->face_materials[face_mat_offset[1] + i];
			tri_mesh.mat_idx[i] = index;
		}
		i++;
	}
}

static void	parse_objects(t_scene *scene, fastObjMesh *mesh)
{
	int			face_offset;
	int			mat_offset;
	int			obj;
	int			faces;
	t_tri_mesh	tri_mesh;

	obj = 0;
	face_offset = 0;
	mat_offset = 0;
	while (obj < mesh->object_count)
	{
		faces = mesh->objects[obj].face_count;
		tri_mesh.mat_idx = malloc(sizeof(uint32_t) * faces);
		tri_mesh.v_idx = malloc(sizeof(t_vec3ui) * faces);
		tri_mesh.vt_idx = malloc(sizeof(t_vec3ui) * faces);
		if (!tri_mesh.mat_idx || !tri_mesh.v_idx || !tri_mesh.vt_idx)
			exit_error(MALLOC, "obj index");
		load_faces(faces, (int []){face_offset, mat_offset}, mesh, tri_mesh);
		tri_mesh.num_faces = faces;
		vec_push(&scene->tri_meshes, &tri_mesh);
		face_offset += mesh->objects[obj].face_count * 3;
		mat_offset += mesh->objects[obj].face_count;
		obj++;
	}
}

// print_mesh_data(mesh);
bool	parse_obj(t_scene *scene, const char *filename)
{
	fastObjMesh	*mesh;
	static int	obj_count = 0;

	if (obj_count > 0)
		return (print_warning("Only one obj file is supported"));
	obj_count++;
	printf("Parsing obj file: %s\n", filename);
	mesh = fast_obj_read(filename);
	if (!mesh)
		exit_error(OBJ_LOAD, "fast_obj_read");
	if (load_mesh_materials(scene, mesh) == false)
		exit_error(MALLOC, "load mesh materials");
	if (get_mesh_materials(scene, mesh) == false)
		exit_error(TEXTURE_LOAD, "get mesh materials");
	scene->num_tri_meshes = mesh->object_count;
	scene->vertices = copy_float_array(mesh->positions, \
		mesh->position_count * 3);
	scene->tex_coords = copy_float_array(mesh->texcoords, \
		mesh->texcoord_count * 2);
	parse_objects(scene, mesh);
	fast_obj_destroy(mesh);
	return (true);
}
