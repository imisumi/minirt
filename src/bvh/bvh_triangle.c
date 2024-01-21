/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:16:18 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/21 20:15:36 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_aabb	get_tri_aabb(t_vec3f *vertices)
{
	int		i;
	t_aabb	aabb;

	i = 0;
	aabb.min_f = (t_vec3f){INFINITY, INFINITY, INFINITY};
	aabb.max_f = (t_vec3f){-INFINITY, -INFINITY, -INFINITY};
	while (i < 3)
	{
		aabb.min_f[X] = fminf(aabb.min_f[X], vertices[i][X]);
		aabb.min_f[Y] = fminf(aabb.min_f[Y], vertices[i][Y]);
		aabb.min_f[Z] = fminf(aabb.min_f[Z], vertices[i][Z]);
		aabb.max_f[X] = fmaxf(aabb.max_f[X], vertices[i][X]);
		aabb.max_f[Y] = fmaxf(aabb.max_f[Y], vertices[i][Y]);
		aabb.max_f[Z] = fmaxf(aabb.max_f[Z], vertices[i][Z]);
		i++;
	}
	return (aabb);
}

t_aabb	get_mesh_aabb(t_tri *tris, int num_tris)
{
	int		i;
	t_aabb	aabb;

	i = 0;
	aabb.min_f = (t_vec3f){INFINITY, INFINITY, INFINITY};
	aabb.max_f = (t_vec3f){-INFINITY, -INFINITY, -INFINITY};
	while (i < num_tris)
	{
		aabb.min_f[X] = fminf(aabb.min_f[X], tris[i].aabb.min_f[X]);
		aabb.min_f[Y] = fminf(aabb.min_f[Y], tris[i].aabb.min_f[Y]);
		aabb.min_f[Z] = fminf(aabb.min_f[Z], tris[i].aabb.min_f[Z]);
		aabb.max_f[X] = fmaxf(aabb.max_f[X], tris[i].aabb.max_f[X]);
		aabb.max_f[Y] = fmaxf(aabb.max_f[Y], tris[i].aabb.max_f[Y]);
		aabb.max_f[Z] = fmaxf(aabb.max_f[Z], tris[i].aabb.max_f[Z]);
		i++;
	}
	return (aabb);
}

void	setup_mesh_aabb(t_tri_mesh *meshes, int num_meshes)
{
	// meshes[0].aabb.min_f = (t_vec3f){1.0f, 2.0f, 3.0f};
	int	i;
	int	j;

	i = 0;
	while (i < num_meshes)
	{
		j = 0;
		while (j < meshes[i].num_faces)
		{
			meshes[i].tris[j].aabb = get_tri_aabb(meshes[i].tris[j].v);
			j++;
		}
		meshes[i].aabb = get_mesh_aabb(meshes[i].tris, meshes[i].num_faces);
		i++;
	}
}

t_aabb	calc_tri_aabb(t_tri *tris, uint32_t start, uint32_t end)
{
	t_aabb	aabb;
	t_vec3f	temp;
	int		i;

	aabb.min_f = (t_vec3f){INFINITY, INFINITY, INFINITY};
	aabb.max_f = (t_vec3f){-INFINITY, -INFINITY, -INFINITY};
	while (start < end)
	{
		i = 0;
		while (i < 3)
		{
			aabb.min_f[X] = fminf(aabb.min_f[X], tris[start].v[i][X]);
			aabb.min_f[Y] = fminf(aabb.min_f[Y], tris[start].v[i][Y]);
			aabb.min_f[Z] = fminf(aabb.min_f[Z], tris[start].v[i][Z]);

			aabb.max_f[X] = fmaxf(aabb.max_f[X], tris[start].v[i][X]);
			aabb.max_f[Y] = fmaxf(aabb.max_f[Y], tris[start].v[i][Y]);
			aabb.max_f[Z] = fmaxf(aabb.max_f[Z], tris[start].v[i][Z]);
			i++;
		}
		start++;
	}
	return (aabb);
}

t_bvh_node	*bvh_triangle(t_tri *tris, uint32_t start, uint32_t end, uint32_t max_dept)
{
	t_bvh_node	*node;
	uint32_t	mid;

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
	node->is_leaf = false;
	if (end - start <= MAX_TRIS_LEAF || max_dept == 0)
	{
		node->is_leaf = true;
		node->aabb = calc_tri_aabb(tris, node->start, node->end);
	}
	else
	{
		mid = (start + end) / 2;
		node->left = bvh_triangle(tris, start, mid, max_dept - 1);
		node->right = bvh_triangle(tris, mid, end, max_dept - 1);
		node->aabb = merge_aabb_f(node->left->aabb, node->right->aabb);
		node->is_leaf = false;
	}
	return (node);
}

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
	node->start = start;
	node->end = end;
	node->left = NULL;
	node->right = NULL;
	node->is_leaf = false;
	if (end - start <= 1 || max_dept == 0)
	{
		node->is_leaf = true;
		node->aabb = meshes[start].aabb;
	}
	else
	{
		mid = (start + end) / 2;
		node->left = build_mesh_bvh(meshes, start, mid, max_dept - 1);
		node->right = build_mesh_bvh(meshes, mid, end, max_dept - 1);
		node->aabb = merge_aabb_f(node->left->aabb, node->right->aabb);
		node->is_leaf = false;
	}
	return (node);
}


bool	build_bvh_triangle(t_scene *scene)
{
	printf("Building BVH for triangles\n");
	int meshs = scene->num_tri_meshes;
	printf("Scene has %d meshes\n", meshs);
	setup_mesh_aabb(scene->tri_meshes, meshs);
	// scene->tri_meshes->bvh = bvh_triangle(scene->tri_meshes[0].tris, 0, scene->tri_meshes[0].num_faces, 100);
	// t_aabb temp = scene->tri_meshes->bvh->aabb;
	// printf("aabb min = %f, %f, %f\n", temp.min_f[X], temp.min_f[Y], temp.min_f[Z]);
	// printf("aabb max = %f, %f, %f\n", temp.max_f[X], temp.max_f[Y], temp.max_f[Z]);
	int	i;

	i = 0;
	while (i < scene->num_tri_meshes)
	{
		scene->tri_meshes[i].bvh = bvh_triangle(scene->tri_meshes[i].tris, 0, scene->tri_meshes[i].num_faces, 100);
		i++;
	}
	t_aabb temp = scene->tri_meshes->bvh->aabb;
	printf("aabb min = %f, %f, %f\n", temp.min_f[X], temp.min_f[Y], temp.min_f[Z]);
	printf("aabb max = %f, %f, %f\n", temp.max_f[X], temp.max_f[Y], temp.max_f[Z]);
	

	scene->bvh_meshes = build_mesh_bvh(scene->tri_meshes, 0, scene->num_tri_meshes, 100);
	
	// exit(0);
	return (true);
}


// t_bvh_node	*build_bvh_mesh(t_tri_mesh *meshes, uint32_t start, uint32_t end, uint32_t max_depth)
// {
// 	t_bvh_node	*node;
// 	uint32_t	mid;
// 	static int mal = 0;

// 	node = malloc(sizeof(t_bvh_node));
// 	if (node == NULL)
// 	{
// 		*error() = MALLOC_BVH;
// 		return (NULL);
// 	}
// 	node->start = start;
// 	node->end = end;
// 	node->left = NULL;
// 	node->right = NULL;
// 	if (end - start <= MAX_SPHERES_LEAF || max_depth == 0)
// 	{
// 		node->is_leaf = true;
// 		node->aabb = calculate_sphere_aabb_f(spheres, node->start, node->end);
// 	}
// 	else
// 	{
// 		mid = (start + end) / 2;
// 		node->left = build_bvh_sphere_f(spheres, start, mid, max_depth - 1);
// 		node->right = build_bvh_sphere_f(spheres, mid, end, max_depth - 1);
// 		node->aabb = merge_aabb_f(node->left->aabb, node->right->aabb);
// 		node->is_leaf = false;
// 	}
// 	mal++;
// 	// printf("malloc = %d\n", mal);
// 	return (node);
// }