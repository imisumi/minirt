/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:26:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/04/22 19:26:24 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// x = (x < 0) ? 0 : ((x >= tex->width) ? tex->width - 1 : x);
	// y = (y < 0) ? 0 : ((y >= tex->height) ? tex->height - 1 : y);
t_vec3f	sample_texture(mlx_texture_t *tex, const t_barycentric *c, \
			const float *uvs)
{
	t_vec3f		color;
	uint32_t	x;
	uint32_t	y;
	const float	tex_u = c->w * uvs[0] + c->u * uvs[2] + c->v * uvs[4];
	const float	tex_v = c->w * uvs[1] + c->u * uvs[3] + c->v * uvs[5];

	x = (int)(tex_u * (tex->width - 1));
	y = (int)((1 - tex_v) * (tex->height - 1));
	x = x % tex->width;
	y = y % tex->height;
	x = (y * tex->width + x) * tex->bytes_per_pixel;
	color[R] = tex->pixels[x] / 255.0f;
	color[G] = tex->pixels[x + 1] / 255.0f;
	color[B] = tex->pixels[x + 2] / 255.0f;
	color[A] = 1.0f;
	return (color);
}

// mesh_face[0] = mesh index
// mesh_face[1] = face index
void	set_tri_material(t_hitinfo *hitinfo, t_scene *s, \
			int m_f_idx[2], float uv[2])
{
	const uint32_t		mat_index = \
		s->tri_meshes[m_f_idx[0]].mat_idx[m_f_idx[1]];
	const t_barycentric	bary_coords = {uv[0], uv[1], 1.0f - uv[0] - uv[1]};
	const float			uvs[6] = {
		s->tex_coords[s->tri_meshes[m_f_idx[0]].vt_idx[m_f_idx[1]][0] * 2],
		s->tex_coords[s->tri_meshes[m_f_idx[0]].vt_idx[m_f_idx[1]][0] * 2 + 1],
		s->tex_coords[s->tri_meshes[m_f_idx[0]].vt_idx[m_f_idx[1]][1] * 2],
		s->tex_coords[s->tri_meshes[m_f_idx[0]].vt_idx[m_f_idx[1]][1] * 2 + 1],
		s->tex_coords[s->tri_meshes[m_f_idx[0]].vt_idx[m_f_idx[1]][2] * 2],
		s->tex_coords[s->tri_meshes[m_f_idx[0]].vt_idx[m_f_idx[1]][2] * 2 + 1]};
	t_vec3f				normal_color;

	hitinfo->material = s->materials[mat_index];
	if (s->materials[mat_index].normal_tex)
	{
		normal_color = sample_texture(s->materials[mat_index].normal_tex, \
			&bary_coords, uvs);
		normal_color = 2.0f * normal_color - 1.0f;
		hitinfo->normal = vec3f_normalize(hitinfo->normal + normal_color);
	}
	if (s->materials[mat_index].color_tex)
		hitinfo->material.color = sample_texture(\
		s->materials[mat_index].color_tex, &bary_coords, uvs);
}
