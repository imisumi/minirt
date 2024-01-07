/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/06 15:45:00 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// extern uint32_t accumulated_frames;

extern int	total_frames;

extern uint32_t	global_frame;

t_vec2f	get_pixel_coord(uint32_t width, uint32_t height, uint32_t x, uint32_t y)
{
	t_vec2f	coord;

	coord[X] = (float)x / (float)(width);
	coord[Y] = (float)y / (float)(height);
	return (coord);
}

void	recalculat_ray_directions(t_data *d)
{
	t_vec2f	coordf;
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < d->utils.height)
	{
		x = 0;
		while (x < d->utils.width)
		{
			coordf = (get_pixel_coord(d->utils.width, d->utils.height, x, y) * 2.0f) - 1.0f;
			
			t_vec4f target = mat4_mul_vec4f(d->scene.camera.inv_projection, (t_vec4f){coordf[X], coordf[Y], 1.0f, 1.0f});
			t_vec3f t = (t_vec3f){target[X], target[Y], target[Z], 0.0f} / target[W];
			target = vec4f_normalize((t_vec4f){-t[X], t[Y], -t[Z], 0.0f});
			target = mat4_mul_vec4f(d->scene.camera.inv_view, target);
			d->scene.camera.ray_target[x + y * d->utils.width] = target;
			//! dont think I need this
			//? - Left handed coordinate system -target.x
			// t_vec3 rayDirection = vec3_new(target.x, target.y, target.z);

			target[Y] = 0.0f;
			d->scene.camera.ray_dir[x + y * d->utils.width] = target;
			x++;
		}
		y++;
	}
}

// cam->position = (t_vec3f){6.0f, 2.0, 30.0f, 0.0f};
// cam->dir = (t_vec3f){0.0, 0.2, -1.0, 0.0};
// cam->vertical_fov = 60.0f;
void	init_camera(t_camera *cam)
{
	cam->position = (t_vec3f){0.0f, 2.0, 5.0f, 0.0f};
	cam->dir = (t_vec3f){0.0, 0.0, -1.0, 0.0};
	cam->mouse_delta[X] = 0;
	cam->mouse_delta[Y] = 0;
	cam->projection = mat4_identity();
	cam->inv_projection = mat4_identity();
	cam->view = mat4_identity();
	cam->inv_view = mat4_identity();
	cam->aspectRatio = (float)WIDTH / (float)HEIGHT;
	cam->vertical_fov = 60.0f;
	cam->zNear = 0.1f;
	cam->zFar = 1000.0f;
	cam->prev_mouse_pos[X] = -1;
	cam->prev_mouse_pos[Y] = -1;
}

void	recalculate_view(t_data *d)
{
	const t_vec3f	pos = d->scene.camera.position;
	const t_vec3f	dir = d->scene.camera.dir;

	d->scene.camera.view = mat4_look_at_f(pos, pos + dir, \
							(t_vec3f){0.0f, 1.0f, 0.0f, 0.0f});
	d->scene.camera.inv_view = mat4_inverse(d->scene.camera.view);
}

void	recalculated_projection(t_data *d)
{
	d->scene.camera.projection = mat4_perspective(fov_radians(d->scene.camera.vertical_fov), \
								d->scene.camera.aspectRatio, \
								d->scene.camera.zNear, d->scene.camera.zFar);
	d->scene.camera.inv_projection = mat4_inverse(d->scene.camera.projection);
}
