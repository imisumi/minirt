/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:26:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/13 19:42:56 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define E1 0
#define E2 1

t_vec3f	get_tri_from_index(t_scene *scene, int index, int face, int id)
{
	const t_vec3f	tri = {
		scene->vertices[scene->tri_meshes[index].v_idx[face][id] * 3],
		scene->vertices[scene->tri_meshes[index].v_idx[face][id] * 3 + 1],
		scene->vertices[scene->tri_meshes[index].v_idx[face][id] * 3 + 2]};

	return (tri);
}

void	set_tri_hitinfo(t_hitinfo *hitinfo, t_rayf ray, \
	float t, const t_vec3f edge[2])
{
	hitinfo->hit = true;
	hitinfo->position = ray[ORIGIN] + ray[DIR] * t;
	hitinfo->normal = vec3f_normalize(vec3f_cross(edge[E1], edge[E2]));
	hitinfo->distance = t;
}

void	set_point_and_edge(t_scene *scene, t_vec3f tri[3], \
	int mesh_face[2], t_vec3f edge[2])
{
	tri[0] = get_tri_from_index(scene, mesh_face[0], mesh_face[1], 0);
	tri[1] = get_tri_from_index(scene, mesh_face[0], mesh_face[1], 1);
	tri[2] = get_tri_from_index(scene, mesh_face[0], mesh_face[1], 2);
	edge[E1] = tri[1] - tri[0];
	edge[E2] = tri[2] - tri[0];
}
