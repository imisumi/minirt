/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:26:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/26 00:23:58 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define E1 0
#define E2 1

t_vec3f	get_tri_from_index(t_scene *scene, int index, int face, int id)
{
	const t_vec3f	tri = {
		scene->vertices[scene->tri_meshes[index].v_idx[face][id] * 3],
		scene->vertices[scene->tri_meshes[index].v_idx[face][id] * 3 + 1],
		scene->vertices[scene->tri_meshes[index].v_idx[face][id] * 3 + 2]};

	return (tri);
}

void	set_tri_hitinfo(t_hitinfo *hitinfo, t_rayf ray, float t, const t_vec3f edge[2])
{
	hitinfo->hit = true;
	hitinfo->position = ray[ORIGIN] + ray[DIR] * t;
	hitinfo->normal = vec3f_normalize(vec3f_cross(edge[E1], edge[E2]));
	hitinfo->distance = t;
}



void	set_point_and_edge(t_scene *scene, t_vec3f tri[3], int mesh_face[2], t_vec3f edge[2])
{
	tri[0] = get_tri_from_index(scene, mesh_face[0], mesh_face[1], 0);
	tri[1] = get_tri_from_index(scene, mesh_face[0], mesh_face[1], 1);
	tri[2] = get_tri_from_index(scene, mesh_face[0], mesh_face[1], 2);
	edge[E1] = tri[1] - tri[0];
	edge[E2] = tri[2] - tri[0];
}

// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
bool	single_triangle_intersection(t_rayf ray, uint32_t face_idx, t_hitinfo *hitinfo, t_scene *scene, int mesh_idx)
{
	t_vec3f	tri[3];
	t_vec3f	edge[2];
	t_tri_vecs v;
	t_tri_floats f;

	set_point_and_edge(scene, tri, (int[2]){mesh_idx, face_idx}, edge);
	v.ray_cross_e2 = vec3f_cross(ray[DIR], edge[E2]);
	f.det = vec3f_dot(edge[E1], v.ray_cross_e2);
	if ((BACK_FACE_CULLING && f.det < 0) || (f.det > -EPSILON && f.det < EPSILON))
		return (false);
	f.inv_det = 1.0f / f.det;
	v.s = ray[ORIGIN] - tri[0];
	f.u = f.inv_det * vec3f_dot(v.s, v.ray_cross_e2);
	if (f.u < 0.0f || f.u > 1.0f)
		return (false);
	v.s_cross_e1 = vec3f_cross(v.s, edge[E1]);
	f.v = f.inv_det * vec3f_dot(ray[DIR], v.s_cross_e1);
	if (f.v < 0.0f || f.u + f.v > 1.0f)
		return (false);
	f.t = f.inv_det * vec3f_dot(edge[E2], v.s_cross_e1);
	if (f.t < EPSILON || f.t > hitinfo->distance)
		return (false);
	set_tri_hitinfo(hitinfo, ray, f.t, edge);
	set_tri_material(hitinfo, scene, (int[2]){mesh_idx, face_idx}, (float[2]){f.u, f.v});
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
	int			i;
	float		t;
	t_hitinfo	left;
	t_hitinfo	right;

	t = aabb_intersection_f(ray, node->aabb);
	if (!t)
		return (hitinfo);
	if (node->is_leaf == true)
	{
		i = node->start - 1;
		while (++i < node->end)
			single_triangle_intersection(ray, i, &hitinfo, scene, index);
		return (hitinfo);
	}
	else
	{
		left = triangle_bvh_intersection(ray, hitinfo, node->left, scene, index);
		right = triangle_bvh_intersection(ray, hitinfo, node->right, scene, index);
		if (left.hit && (!right.hit || left.distance < right.distance))
			return (left);
		else if (right.hit)
			return (right);
	}
	return (hitinfo);
}

// static t_hitinfo	mesh_intersect_range(t_rayf ray, )
// {
	
// }

t_hitinfo	mesh_bvh_intersection(t_rayf ray, t_hitinfo hitinfo, t_bvh_node *node, t_scene *scene)
{
	int			i;
	float		t;
	t_hitinfo	left;
	t_hitinfo	right;

	t = aabb_intersection_f(ray, node->aabb);
	if (!t)
		return (hitinfo);
	if (node->is_leaf == true)
	{
		i = node->start - 1;
		while (++i < node->end)
			hitinfo = triangle_bvh_intersection(ray, hitinfo, scene->tri_meshes[i].bvh, scene, i);
		return (hitinfo);
	}
	else
	{
		left = mesh_bvh_intersection(ray, hitinfo, node->left, scene);
		right = mesh_bvh_intersection(ray, hitinfo, node->right, scene);
		if (left.hit && (!right.hit || left.distance < right.distance))
			return (left);
		else if (right.hit)
			return (right);
	}
	return (hitinfo);
}
