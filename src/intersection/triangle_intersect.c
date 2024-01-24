/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:26:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/24 01:47:15 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


#define E1 0
#define E2 1



typedef struct {
    float u, v, w;
} BarycentricCoords;

// t_vec3f sampleTexture(const uint8_t *rgba, int width, int height, const BarycentricCoords* baryCoords, float *uvs)
t_vec3f	sampleTexture(mlx_texture_t *tex, const BarycentricCoords* baryCoords, float *uvs)
{
	int width = tex->width;
	int height = tex->height;
	uint8_t *rgba = tex->pixels;

    // Calculate the texture coordinates based on barycentric coordinates
    // float texU = baryCoords->u * uvs[0] + baryCoords->v * uvs[2] + baryCoords->w * uvs[4];
    // float texV = baryCoords->u * uvs[1] + baryCoords->v * uvs[3] + baryCoords->w * uvs[5];
	float texU = baryCoords->w * uvs[0] + baryCoords->u * uvs[2] + baryCoords->v * uvs[4];
    float texV = baryCoords->w * uvs[1] + baryCoords->u * uvs[3] + baryCoords->v * uvs[5];
	texV = 1 - texV;
    // Convert floating-point texture coordinates to integer indices
    int x = (int)(texU * (width - 1));
    int y = (int)(texV * (height - 1));

    // Ensure indices are within bounds
    x = (x < 0) ? 0 : ((x >= width) ? width - 1 : x);
    y = (y < 0) ? 0 : ((y >= height) ? height - 1 : y);

    // Calculate the offset into the RGBA buffer
    int offset = (y * width + x) * 4;

    // Sample the RGBA values from the buffer
    uint8_t red = rgba[offset];
    uint8_t green = rgba[offset + 1];
    uint8_t blue = rgba[offset + 2];
    uint8_t alpha = rgba[offset + 3];
	alpha = 255;

	t_vec3f color;
	color[R] = red / 255.0f;
	color[G] = green / 255.0f;
	color[B] = blue / 255.0f;
	color[A] = 1.0f;
    // Combine the sampled values into a 32-bit color value
    // return (alpha << 24) | (red << 16) | (green << 8) | blue;
	return (color);
}

t_vec3f	get_tri_from_index(t_scene *scene, int index, int face, int id)
{
	const t_vec3f	tri = {
		scene->vertices[scene->tri_meshes[index].v_idx[face][id] * 3],
		scene->vertices[scene->tri_meshes[index].v_idx[face][id] * 3 + 1],
		scene->vertices[scene->tri_meshes[index].v_idx[face][id] * 3 + 2]};

	return (tri);
}

// void	apply_tri_material(t_hitinfo *hitinfo, t_scene *scene, )
// {
// 	int mat_index = scene->tri_meshes[index].mat_idx[face];
// 	hitinfo->material = scene->materials[mat_index];
// 	if (scene->materials[mat_index].color_tex)
// 	{
// 		BarycentricCoords baryCoords = {u, v, 1.0f - u - v};
// 		float uvs[6];
// 		uvs[0] = scene->tex_coords[scene->tri_meshes[index].vt_idx[face][0] * 2];
// 		uvs[1] = scene->tex_coords[scene->tri_meshes[index].vt_idx[face][0] * 2 + 1];
		
// 		uvs[2] = scene->tex_coords[scene->tri_meshes[index].vt_idx[face][1] * 2];
// 		uvs[3] = scene->tex_coords[scene->tri_meshes[index].vt_idx[face][1] * 2 + 1];

// 		uvs[4] = scene->tex_coords[scene->tri_meshes[index].vt_idx[face][2] * 2];
// 		uvs[5] = scene->tex_coords[scene->tri_meshes[index].vt_idx[face][2] * 2 + 1];
// 		hitinfo->material.color =  sampleTexture(scene->materials[mat_index].color_tex, &baryCoords, uvs);
// 	}
// }

	// if (u < 0 || u > 1 || v < 0 || u + v > 1)
	// 	return (false);
	// if ((u < 0) | (u > 1) | (v < 0) | (u + v > 1))
	// 	return (false);
// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
bool	single_triangle_intersection(t_rayf ray, uint32_t face_idx, t_hitinfo *hitinfo, t_scene *scene, int mesh_idx)
{
	const t_vec3f	tri[3] = {
		get_tri_from_index(scene, mesh_idx, face_idx, 0),
		get_tri_from_index(scene, mesh_idx, face_idx, 1),
		get_tri_from_index(scene, mesh_idx, face_idx, 2)};
	const t_vec3f edge[2] = {tri[1] - tri[0], tri[2] - tri[0]};
	
	t_vec3f ray_cross_e2 = vec3f_cross(ray[DIR], edge[E2]);

	float det = vec3f_dot(edge[E1], ray_cross_e2);

	if (BACK_FACE_CULLING && det < 0)
		return (false);
	else if (det > -EPSILON && det < EPSILON)
		return (false);

	float inv_det = 1.0f / det;
	t_vec3f s = ray[ORIGIN] - tri[0];
	float u = inv_det * vec3f_dot(s, ray_cross_e2);

	if (u < 0.0f || u > 1.0f)
		return (false);

	t_vec3f s_cross_e1 = vec3f_cross(s, edge[E1]);
	float v = inv_det * vec3f_dot(ray[DIR], s_cross_e1);

	if (v < 0.0f || u + v > 1.0f)
		return (false);
	float t = inv_det * vec3f_dot(edge[E2], s_cross_e1);
	if (t > EPSILON && t < hitinfo->distance)
	{
		hitinfo->hit = true;
		hitinfo->position = ray[ORIGIN] + ray[DIR] * t;
		hitinfo->normal = vec3f_normalize(vec3f_cross(edge[E1], edge[E2]));
		hitinfo->distance = t;
		
		int mat_index = scene->tri_meshes[mesh_idx].mat_idx[face_idx];
		hitinfo->material = scene->materials[mat_index];

		BarycentricCoords baryCoords = {u, v, 1.0f - u - v};

		float uvs[6];

		uvs[0] = scene->tex_coords[scene->tri_meshes[mesh_idx].vt_idx[face_idx][0] * 2];
		uvs[1] = scene->tex_coords[scene->tri_meshes[mesh_idx].vt_idx[face_idx][0] * 2 + 1];
		
		uvs[2] = scene->tex_coords[scene->tri_meshes[mesh_idx].vt_idx[face_idx][1] * 2];
		uvs[3] = scene->tex_coords[scene->tri_meshes[mesh_idx].vt_idx[face_idx][1] * 2 + 1];

		uvs[4] = scene->tex_coords[scene->tri_meshes[mesh_idx].vt_idx[face_idx][2] * 2];
		uvs[5] = scene->tex_coords[scene->tri_meshes[mesh_idx].vt_idx[face_idx][2] * 2 + 1];

		t_vec3f normal_color;
		if (scene->materials[mat_index].normal_tex)
		{
			normal_color = sampleTexture(scene->materials[mat_index].normal_tex, &baryCoords, uvs);
			t_vec3f normal_map_offset;
			normal_map_offset[X] = 2.0f * normal_color[R] - 1.0f;
			normal_map_offset[Y] = 2.0f * normal_color[G] - 1.0f;
			normal_map_offset[Z] = 2.0f * normal_color[B] - 1.0f;

			hitinfo->normal = vec3f_normalize(hitinfo->normal + normal_map_offset);
		}

		if (scene->materials[mat_index].color_tex)
			hitinfo->material.color =  sampleTexture(scene->materials[mat_index].color_tex, &baryCoords, uvs);

	}
	return (hitinfo->hit);
}

bool triangle_intersection(t_rayf ray, t_scene *scene, uint32_t mesh_idx, t_hitinfo *hitinfo)
{
	int	i;

	i = 0;
	while (i < scene->tri_meshes[mesh_idx].num_faces)
	{
		single_triangle_intersection(ray, i, hitinfo, scene, mesh_idx);
		i++;
	}
	return (hitinfo->hit);
}

//TODO check this
bool	tri_mesh_intersection(t_rayf ray, t_scene *scene, t_hitinfo *hitinfo)
{
	int	i;

	i = 0;
	while (i < vec_length(&scene->tri_meshes))
	{
		triangle_intersection(ray, scene, i, hitinfo);
		i++;
	}
	return (hitinfo->hit);
}


t_hitinfo	triangle_bvh_intersection(t_rayf ray, t_hitinfo hitinfo, t_bvh_node *node, t_scene *scene, int index)
{
	float	t;

	t = aabb_intersection_f(ray, node->aabb);
	if (!t)
		return (hitinfo);
	if (node->is_leaf == true)
	{
		if (RENDER_BVH && t > EPSILON && t < hitinfo.distance)
		{
			hitinfo.hit = true;
			hitinfo.material.color = (t_vec3f){1, 0, 1};
			hitinfo.distance = t;
			return (hitinfo);
		}
		for (int i = node->start; i < node->end; i++)
			single_triangle_intersection(ray, i, &hitinfo, scene, index);
		return (hitinfo);
	}
	else
	{
		t_hitinfo left = triangle_bvh_intersection(ray, hitinfo, node->left, scene, index);
		t_hitinfo right = triangle_bvh_intersection(ray, hitinfo, node->right, scene, index);
		if (left.hit && !right.hit)
			return (left);
		else if (!left.hit && right.hit)
			return (right);
		else if (left.hit && right.hit)
		{
			if (left.distance < right.distance)
				return (left);
			else
				return (right);
		}
	}
	return (hitinfo);
}

t_hitinfo	mesh_bvh_intersection(t_rayf ray, t_hitinfo hitinfo, t_bvh_node *node, t_scene *scene)
{
	float	t;

	t = aabb_intersection_f(ray, node->aabb);
	if (!t)
		return (hitinfo);
	if (node->is_leaf == true)
	{
		for (int i = node->start; i < node->end; i++)
			hitinfo = triangle_bvh_intersection(ray, hitinfo, scene->tri_meshes[i].bvh, scene, i);
		return (hitinfo);
	}
	else
	{
		t_hitinfo left = mesh_bvh_intersection(ray, hitinfo, node->left, scene);
		t_hitinfo right = mesh_bvh_intersection(ray, hitinfo, node->right, scene);
		if (left.hit && !right.hit)
			return (left);
		else if (!left.hit && right.hit)
			return (right);
		else if (left.hit && right.hit)
		{
			if (left.distance < right.distance)
				return (left);
			else
				return (right);
		}
	}
	return (hitinfo);
}
