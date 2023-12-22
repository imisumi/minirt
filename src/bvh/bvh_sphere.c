/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:53:27 by ichiro            #+#    #+#             */
/*   Updated: 2023/12/18 23:36:30 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_aabb	calculate_sphere_aabb(t_sphere *spheres, uint32_t start, uint32_t end)
{
	t_aabb	aabb;
	t_vec3	temp;

	aabb.min = spheres[start].position;
	aabb.max = spheres[start].position;
	while (start < end && start < array_length(&spheres))
	{
		temp = vec3_addf(spheres[start].position, spheres[start].radius);
		aabb.max.x = fmaxf(temp.x, aabb.max.x);
		aabb.max.y = fmaxf(temp.y, aabb.max.y);
		aabb.max.z = fmaxf(temp.z, aabb.max.z);
		temp = vec3_subf(spheres[start].position, spheres[start].radius);
		aabb.min.x = fminf(temp.x, aabb.min.x);
		aabb.min.y = fminf(temp.y, aabb.min.y);
		aabb.min.z = fminf(temp.z, aabb.min.z);
		start++;
	}
	return (aabb);
}

t_aabb	merge_aabb(t_aabb a, t_aabb b)
{
	t_aabb	result;

	result.min.x = fminf(a.min.x, b.min.x);
	result.min.y = fminf(a.min.y, b.min.y);
	result.min.z = fminf(a.min.z, b.min.z);
	result.max.x = fmaxf(a.max.x, b.max.x);
	result.max.y = fmaxf(a.max.y, b.max.y);
	result.max.z = fmaxf(a.max.z, b.max.z);
	return (result);
}

t_bvh_node	*build_bvh_sphere(t_sphere *spheres, uint32_t start, uint32_t end, uint32_t max_depth)
{
	t_bvh_node	*node;
	uint32_t	mid;

	node = malloc(sizeof(t_bvh_node));
	node->start = start;
	node->end = end;
	if (end - start <= MAX_SPHERES_LEAF || max_depth == 0)
	{
		node->is_leaf = true;
		node->aabb = calculate_sphere_aabb(spheres, node->start, node->end);
	}
	else
	{
		// printf("start = %d, end = %d\n", start, end);
		mid = (start + end) / 2;
		node->left = build_bvh_sphere(spheres, start, mid, max_depth - 1);
		node->right = build_bvh_sphere(spheres, mid, end, max_depth - 1);
		node->aabb = merge_aabb(node->left->aabb, node->right->aabb);
		node->is_leaf = false;
	}
	return (node);
}




t_aabb	calculate_sphere_aabb_f(t_sphere *spheres, uint32_t start, uint32_t end)
{
	t_aabb	aabb;
	t_vec3f	temp;

	aabb.min_f = spheres[start].pos_f;
	aabb.max_f = spheres[start].pos_f;
	while (start < end && start < array_length(&spheres))
	{
		// temp = vec3_addf(spheres[start].position, spheres[start].radius);
		temp = spheres[start].pos_f + spheres[start].radius;
		aabb.max_f[X] = fmaxf(temp[X], aabb.max_f[X]);
		aabb.max_f[Y] = fmaxf(temp[Y], aabb.max_f[Y]);
		aabb.max_f[Z] = fmaxf(temp[Z], aabb.max_f[Z]);
		// temp = vec3_subf(spheres[start].position, spheres[start].radius);
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

t_bvh_node	*build_bvh_sphere_f(t_sphere *spheres, uint32_t start, uint32_t end, uint32_t max_depth)
{
	t_bvh_node	*node;
	uint32_t	mid;

	node = malloc(sizeof(t_bvh_node));
	node->start = start;
	node->end = end;

	static int spehres = 0;
	if (end - start <= MAX_SPHERES_LEAF || max_depth == 0)
	{
		node->is_leaf = true;
		node->aabb = calculate_sphere_aabb_f(spheres, node->start, node->end);
		printf("spehres = %d\n", spehres++);
	}
	else
	{
		// printf("start = %d, end = %d\n", start, end);
		mid = (start + end) / 2;
		node->left = build_bvh_sphere_f(spheres, start, mid, max_depth - 1);
		node->right = build_bvh_sphere_f(spheres, mid, end, max_depth - 1);
		node->aabb = merge_aabb_f(node->left->aabb, node->right->aabb);
		node->is_leaf = false;
	}
	return (node);
}
