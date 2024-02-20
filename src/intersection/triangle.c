/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:26:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/20 15:41:10 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define E1 0
#define E2 1

bool	single_triangle_intersection(t_rayf ray, t_hitinfo *hitinfo, \
	t_scene *scene, int mesh_face[2])
{
	t_vec3f			tri[3];
	t_vec3f			edge[2];
	t_tri_vecs		v;
	t_tri_floats	f;

	set_point_and_edge(scene, tri, mesh_face, edge);
	v.ray_cross_e2 = vec3f_cross(ray[DIR], edge[E2]);
	f.det = vec3f_dot(edge[E1], v.ray_cross_e2);
	if ((BACK_FACE_CULL && f.det < 0) || (f.det > -EPSILON && f.det < EPSILON))
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
	set_tri_material(hitinfo, scene, mesh_face, (float [2]){f.u, f.v});
	return (hitinfo->hit);
}

static bool	triangle_intersection(t_rayf ray, t_scene *scene, \
	uint32_t mesh_idx, t_hitinfo *hitinfo)
{
	int	face;

	face = 0;
	while (face < scene->tri_meshes[mesh_idx].num_faces)
	{
		single_triangle_intersection(ray, hitinfo, scene, \
			(int [2]){mesh_idx, face});
		face++;
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

//? faster but not norm
// t_hitinfo	triangle_bvh_intersection(t_rayf ray, t_hitinfo hitinfo, 
// t_bvh_node *node, t_scene *scene, int index)
// {
// 	int			face;
// 	float		t;
// 	t_hitinfo	left;
// 	t_hitinfo	right;

// 	t = aabb_intersection_f(ray, node->aabb);
// 	if (!t)
// 		return (hitinfo);
// 	if (node->is_leaf == true)
// 	{
// 		face = node->start - 1;
// 		while (++face < node->end)
// 			single_triangle_intersection(ray, &hitinfo, scene, 
// (int [2]){index, face});
// 		return (hitinfo);
// 	}
// 	else
// 	{
// 		left = triangle_bvh_intersection(ray, hitinfo, node->left, 
//scene, index);
// 		right = triangle_bvh_intersection(ray, hitinfo, node->right, 
//scene, index);
// 		if (left.hit && (!right.hit || left.distance < right.distance))
// 			return (left);
// 		else if (right.hit)
// 			return (right);
// 	}
// 	return (hitinfo);
// }

static t_hitinfo	traverse_tree(t_rayf ray, t_mesh_utils u, \
	t_bvh_node *node, t_scene *scene)
{
	const t_hitinfo	l = triangle_bvh_intersection(ray, u, node->left, scene);
	const t_hitinfo	r = triangle_bvh_intersection(ray, u, node->right, scene);

	if (l.hit && (!r.hit || l.distance < r.distance))
		return (l);
	else if (r.hit)
		return (r);
	return (u.hitinfo);
}

t_hitinfo	triangle_bvh_intersection(t_rayf ray, t_mesh_utils u, \
	t_bvh_node *node, t_scene *scene)
{
	int			face;
	float		t;

	if (!node)
		return (u.hitinfo);
	t = aabb_intersection_f(ray, node->aabb);
	if (!t)
		return (u.hitinfo);
	if (node->is_leaf == true)
	{
		face = node->start - 1;
		while (++face < node->end)
		{
			single_triangle_intersection(ray, &u.hitinfo, scene, \
				(int [2]){u.index, face});
		}
		return (u.hitinfo);
	}
	else
		return (traverse_tree(ray, u, node, scene));
}
