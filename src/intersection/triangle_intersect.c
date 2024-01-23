/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:26:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/23 02:27:44 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
bool	single_triangle_intersection(t_rayf ray, uint32_t i, t_hitinfo *hitinfo, t_scene *scene, int index)
{
	const t_vec3f tri_a = {
		scene->vertices[scene->tri_meshes[index].v_idx[i][0] * 3],
		scene->vertices[scene->tri_meshes[index].v_idx[i][0] * 3 + 1],
		scene->vertices[scene->tri_meshes[index].v_idx[i][0] * 3 + 2]};
	const t_vec3f tri_b = {
		scene->vertices[scene->tri_meshes[index].v_idx[i][1] * 3],
		scene->vertices[scene->tri_meshes[index].v_idx[i][1] * 3 + 1],
		scene->vertices[scene->tri_meshes[index].v_idx[i][1] * 3 + 2]};
	const t_vec3f tri_c= {
		scene->vertices[scene->tri_meshes[index].v_idx[i][2] * 3],
		scene->vertices[scene->tri_meshes[index].v_idx[i][2] * 3 + 1],
		scene->vertices[scene->tri_meshes[index].v_idx[i][2] * 3 + 2]};
	
	t_vec3f e1 = tri_b - tri_a;
	t_vec3f e2 = tri_c - tri_a;
	
	t_vec3f ray_cross_e2 = vec3f_cross(ray[DIR], e2);

	float det = vec3f_dot(e1, ray_cross_e2);

	if (BACK_FACE_CULLING && det < 0)
		return (false);
	else if (det > -EPSILON && det < EPSILON)
		return (false); // This ray is parallel to this triangle.

	float inv_det = 1.0f / det;
	t_vec3f s = ray[ORIGIN] - tri_a;
	float u = inv_det * vec3f_dot(s, ray_cross_e2);

	if (u < 0.0f || u > 1.0f)
		return (false);

	t_vec3f s_cross_e1 = vec3f_cross(s, e1);
	float v = inv_det * vec3f_dot(ray[DIR], s_cross_e1);

	if (v < 0.0f || u + v > 1.0f)
		return (false);

	// if (u < 0 || u > 1 || v < 0 || u + v > 1)
	// 	return (false);
	// if ((u < 0) | (u > 1) | (v < 0) | (u + v > 1))
	// 	return (false);

	// At this stage we can compute t to find out where the intersection point is on the line.
	float t = inv_det * vec3f_dot(e2, s_cross_e1);
	
	if (t > EPSILON && t < hitinfo->distance)
	{
		hitinfo->hit = true;
		hitinfo->position = ray[ORIGIN] + ray[DIR] * t;
		hitinfo->normal = vec3f_normalize(vec3f_cross(e1, e2));
		hitinfo->distance = t;
		
		int mat_index = scene->tri_meshes[index].mat_idx[i];
		hitinfo->material = scene->materials[mat_index];
		return (true);
	}
	return (false);
}

bool triangle_intersection(t_rayf ray, t_scene *scene, uint32_t index, t_hitinfo *obj_hit)
{
	int	i;

	i = 0;
	while (i < scene->tri_meshes[index].num_faces)
	{
		// if (i == 2)
		// 	break ;
		single_triangle_intersection(ray, i, obj_hit, scene, index);
		// t_tri tri = scene->tri_meshes[index].tris[i];
		// printf("%f %f %f\n", tri.vertices[0], tri.vertices[1], tri.vertices[2]);
		i++;
	}
	// exit(0);
	return (true);
}

//TODO check this
// bool	tri_mesh_intersection(t_rayf ray, t_scene *scene, t_hitinfo *obj_hit)
// {
// 	int	i;

// 	i = 0;
// 	while (i < vec_length(&scene->tri_meshes))
// 	{
// 		triangle_intersection(ray, scene, i, obj_hit);
// 		// break ;
// 		i++;
// 	}
// 	return (true);
// }


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
