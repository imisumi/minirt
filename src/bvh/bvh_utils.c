/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:53:27 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/23 02:18:17 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_aabb	aabb_infinity(void)
{
	const t_aabb	aabb = {
		.min_f = {INFINITY, INFINITY, INFINITY},
		.max_f = {-INFINITY, -INFINITY, -INFINITY}
	};

	return (aabb);
}

void	bvh_starter_node(t_bvh_node *node, uint32_t start, uint32_t end)
{
	node->start = start;
	node->end = end;
	node->left = NULL;
	node->right = NULL;
	node->is_leaf = false;
}

void	free_bvh_tree(t_bvh_node* node)
{
	if (node == NULL)
		return;
	free_bvh_tree(node->left);
	free_bvh_tree(node->right);
	free(node);
}
