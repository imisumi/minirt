/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:53:27 by ichiro            #+#    #+#             */
/*   Updated: 2024/03/28 15:35:52 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_aabb	calculate_sphere_aabb_f(t_sphere *spheres, uint32_t start, \
	uint32_t end)
{
	t_aabb	aabb;
	t_vec3f	temp;

	aabb.min_f = spheres[start].pos_f;
	aabb.max_f = spheres[start].pos_f;
	while (start < end && start < (uint32_t)vec_length(&spheres))
	{
		temp = spheres[start].pos_f + spheres[start].radius;
		aabb.max_f[X] = fmaxf(temp[X], aabb.max_f[X]);
		aabb.max_f[Y] = fmaxf(temp[Y], aabb.max_f[Y]);
		aabb.max_f[Z] = fmaxf(temp[Z], aabb.max_f[Z]);
		temp = spheres[start].pos_f - spheres[start].radius;
		aabb.min_f[X] = fminf(temp[X], aabb.min_f[X]);
		aabb.min_f[Y] = fminf(temp[Y], aabb.min_f[Y]);
		aabb.min_f[Z] = fminf(temp[Z], aabb.min_f[Z]);
		start++;
	}
	return (aabb);
}

t_bvh_node	*build_bvh_sphere_f(t_sphere *spheres, uint32_t start, \
	uint32_t end, uint32_t max_depth)
{
	t_bvh_node	*node;
	uint32_t	mid;

	node = malloc(sizeof(t_bvh_node));
	if (node == NULL)
		exit_error(MALLOC, "build bvh sphere");
	bvh_starter_node(node, start, end);
	if (end - start <= MAX_SPHERES_LEAF || max_depth == 0)
	{
		node->is_leaf = true;
		node->aabb = calculate_sphere_aabb_f(spheres, node->start, node->end);
	}
	else
	{
		mid = (start + end) / 2;
		node->left = build_bvh_sphere_f(spheres, start, mid, max_depth - 1);
		node->right = build_bvh_sphere_f(spheres, mid, end, max_depth - 1);
		node->aabb = merge_aabb_f(node->left->aabb, node->right->aabb);
	}
	return (node);
}
