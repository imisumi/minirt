/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:53:27 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/16 19:54:54 by imisumi-wsl      ###   ########.fr       */
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
