/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:16:18 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/26 01:07:49 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_aabb	calc_tri_aabb(t_vec3ui *tri_idx, uint32_t start, uint32_t end, float *vertices)
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

//TODO: malloc error handling
t_bvh_node	*bvh_triangle(t_vec3ui *tri_indexes, uint32_t start, uint32_t end, uint32_t max_dept, float *vertices)
{
	t_bvh_node	*node;
	uint32_t	mid;

	node = malloc(sizeof(t_bvh_node));
	if (node == NULL)
	{
		*error() = MALLOC_BVH;
		return (NULL);
	}
	bvh_starter_node(node, start, end);
	if (end - start <= MAX_TRIS_LEAF || max_dept == 0)
	{
		node->is_leaf = true;
		node->aabb = calc_tri_aabb(tri_indexes, node->start, node->end, vertices);
	}
	else
	{
		mid = (start + end) / 2;
		node->left = bvh_triangle(tri_indexes, start, mid, max_dept - 1, vertices);
		if (node->left == NULL)
			return (NULL);
		node->right = bvh_triangle(tri_indexes, mid, end, max_dept - 1, vertices);
		if (node->right == NULL)
			return (NULL);
		node->aabb = merge_aabb_f(node->left->aabb, node->right->aabb);
	}
	return (node);
}

//TODO: malloc error handling
t_bvh_node	*build_mesh_bvh(t_tri_mesh *meshes, uint32_t start, uint32_t end, uint32_t max_dept)
{
	t_bvh_node	*node;
	uint32_t	mid;

	node = malloc(sizeof(t_bvh_node));
	if (node == NULL)
	{
		*error() = MALLOC_BVH;
		return (NULL);
	}
	bvh_starter_node(node, start, end);
	if (end - start <= 1 || max_dept == 0)
	{
		node->is_leaf = true;
		node->aabb = meshes[start].aabb;
	}
	else
	{
		mid = (start + end) / 2;
		node->left = build_mesh_bvh(meshes, start, mid, max_dept - 1);
		if (node->left == NULL)
			return (NULL);
		node->right = build_mesh_bvh(meshes, mid, end, max_dept - 1);
		if (node->right == NULL)
			return (NULL);
		node->aabb = merge_aabb_f(node->left->aabb, node->right->aabb);
	}
	return (node);
}

t_aabb	get_tri_aabb(t_scene *scene, uint32_t tris[3])
{
	t_aabb	aabb;
	t_vec3f	vertex;
	int		i;
	int		j;

	i = 0;
	aabb = aabb_infinity();
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			vertex[j] = scene->vertices[tris[i] * 3 + j];
			aabb.min_f[j] = fminf(aabb.min_f[j], vertex[j]);
			aabb.max_f[j] = fmaxf(aabb.max_f[j], vertex[j]);
			j++;
		}
		i++;
	}
	return (aabb);
}

t_aabb	get_mesh_aabb(t_vec3ui *tri_index, int num_tris, t_scene *scene)
{
	int		i;
	int		j;
	t_aabb	aabb;
	t_aabb	temp;

	i = 0;
	aabb = aabb_infinity();
	while (i < num_tris)
	{
		temp = get_tri_aabb(scene, tri_index[i]);
		j = 0;
		while (j < 3)
		{
			aabb.min_f[j] = fminf(aabb.min_f[j], temp.min_f[j]);
			aabb.max_f[j] = fmaxf(aabb.max_f[j], temp.max_f[j]);
			j++;
		}
		i++;
	}
	return (aabb);
}

void	setup_mesh_aabb(t_tri_mesh *meshes, int num_meshes, t_scene *scene)
{
	int	i;

	i = 0;
	while (i < num_meshes)
	{
		meshes[i].aabb = get_mesh_aabb(meshes[i].v_idx, meshes[i].num_faces, scene);
		i++;
	}
}

bool	init_mesh_bvh(t_scene *scene)
{
	int	i;

	i = 0;
	setup_mesh_aabb(scene->tri_meshes, scene->num_tri_meshes, scene);
	while (i < scene->num_tri_meshes)
	{
		scene->tri_meshes[i].bvh = bvh_triangle(scene->tri_meshes[i].v_idx, 0, scene->tri_meshes[i].num_faces, 100, scene->vertices);
		if (scene->tri_meshes[i].bvh == NULL)
			return (false);
		i++;
	}
	scene->bvh_meshes = build_mesh_bvh(scene->tri_meshes, 0, scene->num_tri_meshes, 100);
	if (scene->bvh_meshes == NULL)
		return (false);
	return (true);
}
