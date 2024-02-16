/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:16:18 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/16 19:51:43 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_aabb	calc_tri_aabb(t_vec3ui *tri_idx, uint32_t start, \
	uint32_t end, float *vertices)
{
	t_aabb	aabb;
	int		i;
	int		j;
	float	vertex;

	i = 0;
	aabb = aabb_infinity();
	while (start < end)
	{
		i = 0;
		while (i < 3)
		{
			j = 0;
			while (j < 3)
			{
				vertex = vertices[tri_idx[start][i] * 3 + j];
				aabb.min_f[j] = fminf(aabb.min_f[j], vertex);
				aabb.max_f[j] = fmaxf(aabb.max_f[j], vertex);
				j++;
			}
			i++;
		}
		start++;
	}
	return (aabb);
}

t_bvh_node	*bvh_triangle(t_vec3ui *tri_indexes, uint32_t start_end[2], \
	uint32_t max_dept, float *vertices)
{
	t_bvh_node	*node;
	uint32_t	mid;

	node = malloc(sizeof(t_bvh_node));
	if (node == NULL)
		exit_error(MALLOC, "build bvh triangle");
	bvh_starter_node(node, start_end[0], start_end[1]);
	if (start_end[1] - start_end[0] <= MAX_TRIS_LEAF || max_dept == 0)
	{
		node->is_leaf = true;
		node->aabb = calc_tri_aabb(tri_indexes, node->start, \
			node->end, vertices);
	}
	else
	{
		mid = (start_end[0] + start_end[1]) / 2;
		node->left = bvh_triangle(tri_indexes, (uint32_t [2]){start_end[0], \
			mid}, max_dept - 1, vertices);
		node->right = bvh_triangle(tri_indexes, (uint32_t [2]){mid, \
			start_end[1]}, max_dept - 1, vertices);
		node->aabb = merge_aabb_f(node->left->aabb, node->right->aabb);
	}
	return (node);
}
