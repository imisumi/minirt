/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:26:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/13 19:53:53 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_hitinfo	mesh_is_leaf(t_rayf ray, t_hitinfo hitinfo, \
	t_bvh_node *node, t_scene *scene)
{
	int		i;

	i = node->start;
	while (i < node->end)
	{
		hitinfo = triangle_bvh_intersection(ray, hitinfo, \
			scene->tri_meshes[i].bvh, scene, i);
		i++;
	}
	return (hitinfo);
}

t_hitinfo	mesh_bvh_intersection(t_rayf ray, t_hitinfo hitinfo, \
	t_bvh_node *node, t_scene *scene)
{
	float		t;
	t_hitinfo	left;
	t_hitinfo	right;

	t = aabb_intersection_f(ray, node->aabb);
	if (!t)
		return (hitinfo);
	if (node->is_leaf == true)
		return (mesh_is_leaf(ray, hitinfo, node, scene));
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
