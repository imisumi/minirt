/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/16 19:33:32 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3f	get_camera_target(t_mat4 inv_projection, t_mat4 inv_view, \
	t_vec2f coord)
{
	t_vec4f		target;
	t_vec3f		t;

	target = mat4_mul_vec4f(inv_projection, \
		(t_vec4f){coord[X], coord[Y], 1.0f, 1.0f});
	t = (t_vec3f){target[X], target[Y], target[Z], 0.0f} / target[W];
	target = vec4f_normalize((t_vec4f){-t[X], t[Y], -t[Z], 0.0f});
	target = mat4_mul_vec4f(inv_view, target);
	return (target);
}

void	recalculat_ray_directions(t_data *d)
{
	uint32_t	x;
	uint32_t	y;
	t_vec2f		coord;
	t_vec4f		target;

	y = 0;
	while (y < d->utils.height)
	{
		x = 0;
		while (x < d->utils.width)
		{
			coord = (t_vec2f){(float)x / (float)(d->utils.width), \
				(float)y / (float)(d->utils.height)};
			coord = (coord * 2.0f) - 1.0f;
			target = get_camera_target(d->scene.camera.inv_projection, \
				d->scene.camera.inv_view, coord);
			d->scene.camera.ray_dir[x + y * d->utils.width] = target;
			x++;
		}
		y++;
	}
}

void	recalculate_view(t_data *d)
{
	const t_vec3f	camposf = d->scene.camera.position;
	const t_vec3f	camdirf = d->scene.camera.dir;

	d->scene.camera.view = mat4_look_at_f(camposf, \
							camposf + camdirf, \
							(t_vec3f){0.0f, 1.0f, 0.0f, 0.0f});
	d->scene.camera.inv_view = mat4_inverse(d->scene.camera.view);
}

void	recalculated_projection(t_data *d)
{
	d->scene.camera.projection = mat4_perspective(\
		fov_radians(d->scene.camera.vertical_fov), \
		(float)d->utils.width / (float)d->utils.height, \
		d->scene.camera.zNear, d->scene.camera.zFar);
	d->scene.camera.inv_projection = mat4_inverse(d->scene.camera.projection);
}

t_vec3f	aa_update_dir(t_data *data, uint32_t *rng, uint32_t x, uint32_t y)
{
	t_vec3f			new_dir;
	const t_vec3f	cam_right_f = {
		data->scene.camera.view.m[0][0], data->scene.camera.view.m[1][0],
		data->scene.camera.view.m[2][0], 0.0f};
	const t_vec3f	cam_up_f = {
		data->scene.camera.view.m[0][1], data->scene.camera.view.m[1][1],
		data->scene.camera.view.m[2][1], 0.0f};
	const float		off_1 = (random_float(rng) - 0.5f) / data->utils.width;
	const float		off_2 = (random_float(rng) - 0.5f) / data->utils.height;

	new_dir = data->scene.camera.ray_dir[x + y * data->utils.width] + \
				(cam_right_f * off_1) + (cam_up_f * off_2);
	return (vec3f_normalize(new_dir));
}
