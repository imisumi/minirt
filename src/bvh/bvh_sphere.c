/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:53:27 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/17 01:56:33 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_aabb	calculate_sphere_aabb_f(t_sphere *spheres, uint32_t start, uint32_t end)
{
	t_aabb	aabb;
	t_vec3f	temp;

	aabb.min_f = spheres[start].pos_f;
	aabb.max_f = spheres[start].pos_f;
	while (start < end && start < array_length(&spheres))
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

t_aabb	merge_aabb_f(t_aabb a, t_aabb b)
{
	t_aabb	result;

	result.min_f[X] = fminf(a.min_f[X], b.min_f[X]);
	result.min_f[Y] = fminf(a.min_f[Y], b.min_f[Y]);
	result.min_f[Z] = fminf(a.min_f[Z], b.min_f[Z]);
	result.max_f[X] = fmaxf(a.max_f[X], b.max_f[X]);
	result.max_f[Y] = fmaxf(a.max_f[Y], b.max_f[Y]);
	result.max_f[Z] = fmaxf(a.max_f[Z], b.max_f[Z]);
	return (result);
}

void	free_bvh_tree(t_bvh_node* node)
{
	if (node == NULL)
		return;
	// if (!node->is_leaf)
	// {
	// 	free_bvh_tree(node->left);
	// 	free_bvh_tree(node->right);
	// }
	free_bvh_tree(node->left);
	free_bvh_tree(node->right);
	free(node);
}

//TODO: malloc protection
t_bvh_node	*build_bvh_sphere_f(t_sphere *spheres, uint32_t start, \
				uint32_t end, uint32_t max_depth)
{
	t_bvh_node	*node;
	uint32_t	mid;
	static int mal = 0;

	node = malloc(sizeof(t_bvh_node));
	if (node == NULL)
	{
		*error() = MALLOC_BVH;
		return (NULL);
	}
	node->start = start;
	node->end = end;
	node->left = NULL;
	node->right = NULL;
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
		node->is_leaf = false;
	}
	mal++;
	// printf("malloc = %d\n", mal);
	return (node);
}

