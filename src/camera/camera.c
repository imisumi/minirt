/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/12 16:28:18 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// extern uint32_t accumulated_frames;

// extern int	total_frames;

// extern uint32_t	global_frame;


// void recalculat_ray_directions(t_data *d)
// {
// 	for (uint32_t y = 0; y < d->utils.height; y++)
// 	{
// 		for (uint32_t x = 0; x < d->utils.width; x++)
// 		{
// 			t_vec2f coordf = {(float)x / (float)(d->utils.width), (float)y / (float)(d->utils.height)};
// 			coordf = (coordf * 2.0f) - 1.0f;
// 			t_vec4f target = mat4_mul_vec4f(d->scene.camera.inv_projection, (t_vec4f){coordf[X], coordf[Y], 1.0f, 1.0f});
// 			t_vec3f t = (t_vec3f){target[X], target[Y], target[Z], 0.0f} / target[W];
// 			target = vec4f_normalize((t_vec4f){-t[X], t[Y], -t[Z], 0.0f});
// 			target = mat4_mul_vec4f(d->scene.camera.inv_view, target);
// 			d->scene.camera.ray_target[x + y * d->utils.width] = target;
// 			//! dont think I need this
// 			//? - Left handed coordinate system -target.x
// 			// t_vec3 rayDirection = vec3_new(target.x, target.y, target.z);
// 			t_vec3f rayDirectionf = {target[X], target[Y], target[Z], 0.0f};
// 			d->scene.camera.ray_dir[x + y * d->utils.width] = rayDirectionf;
// 		}
// 	}
// }

// void init_camera(t_camera *cam)
// {

// 	cam->position = (t_vec3f){6.0f, 2.0, 30.0f, 0.0f};
// 	cam->dir = (t_vec3f){0.0, 0.2, -1.0, 0.0};

// 	// cam->position = (t_vec3f){0.0f, 2.0, 5.0f, 0.0f};
// 	// cam->dir = (t_vec3f){0.0, 0.0, -1.0, 0.0};

// 	// cam->ray_dir = malloc(sizeof(t_vec3) * WIDTH * HEIGHT);

// 	cam->mouse_delta[X] = 0;
// 	cam->mouse_delta[Y] = 0;

// 	cam->projection = mat4_identity();
// 	cam->inv_projection = mat4_identity();
// 	cam->view = mat4_identity();
// 	cam->inv_view = mat4_identity();

// 	cam->vertical_fov = 45.0f;
// 	cam->aspectRatio = (float)WIDTH / (float)HEIGHT;
// 	cam->zNear = 0.1f;
// 	cam->zFar = 1000.0f;

// 	cam->prev_mouse_pos[X] = -1;
// 	cam->prev_mouse_pos[Y] = -1;
// }

// void recalculate_view(t_data *d)
// {
// 	t_vec3 campos;
// 	campos.x = d->scene.camera.position[X];
// 	campos.y = d->scene.camera.position[Y];
// 	campos.z = d->scene.camera.position[Z];
	
// 	t_vec3 camdir;
// 	camdir.x = d->scene.camera.dir[X];
// 	camdir.y = d->scene.camera.dir[Y];
// 	camdir.z = d->scene.camera.dir[Z];

// 	d->scene.camera.view = mat4_look_at(campos, \
// 							vec3_add(campos, camdir), \
// 							vec3_new(0.0f, 1.0f, 0.0f));
// 	d->scene.camera.inv_view = mat4_inverse(d->scene.camera.view);
// }

// void recalculated_projection(t_data *d)
// {
// 	d->scene.camera.projection = mat4_perspective(fov_radians(d->scene.camera.vertical_fov), \
// 								(float)d->utils.width / (float)d->utils.height, \
// 								d->scene.camera.zNear, d->scene.camera.zFar);
// 	d->scene.camera.inv_projection = mat4_inverse(d->scene.camera.projection);
// }



void recalculat_ray_directions(t_data *d)
{
	for (uint32_t y = 0; y < d->utils.height; y++)
	{
		for (uint32_t x = 0; x < d->utils.width; x++)
		{
			t_vec2f coordf = {(float)x / (float)(d->utils.width), (float)y / (float)(d->utils.height)};
			coordf = (coordf * 2.0f) - 1.0f;
			t_vec4f target = mat4_mul_vec4f(d->scene.camera.inv_projection, (t_vec4f){coordf[X], coordf[Y], 1.0f, 1.0f});
			t_vec3f t = (t_vec3f){target[X], target[Y], target[Z], 0.0f} / target[W];
			target = vec4f_normalize((t_vec4f){-t[X], t[Y], -t[Z], 0.0f});
			target = mat4_mul_vec4f(d->scene.camera.inv_view, target);
			d->scene.camera.ray_target[x + y * d->utils.width] = target;
			//! dont think I need this
			//? - Left handed coordinate system -target.x
			t_vec3f rayDirectionf = {target[X], target[Y], target[Z], 0.0f};
			d->scene.camera.ray_dir[x + y * d->utils.width] = rayDirectionf;
		}
	}
}

void init_camera(t_camera *cam)
{

	cam->position = (t_vec3f){6.0f, 2.0, 30.0f, 0.0f};
	cam->dir = (t_vec3f){0.0, 0.2, -1.0, 0.0};

	// cam->position = (t_vec3f){0.0f, 2.0, 5.0f, 0.0f};
	// cam->dir = (t_vec3f){0.0, 0.0, -1.0, 0.0};

	// cam->ray_dir = malloc(sizeof(t_vec3) * WIDTH * HEIGHT);

	cam->mouse_delta[X] = 0;
	cam->mouse_delta[Y] = 0;

	cam->projection = mat4_identity();
	cam->inv_projection = mat4_identity();
	cam->view = mat4_identity();
	cam->inv_view = mat4_identity();

	cam->vertical_fov = 45.0f;
	cam->aspectRatio = (float)WIDTH / (float)HEIGHT;
	cam->zNear = 0.1f;
	cam->zFar = 1000.0f;

	cam->prev_mouse_pos[X] = -1;
	cam->prev_mouse_pos[Y] = -1;
}

void recalculate_view(t_data *d)
{
	const t_vec3f camposf = d->scene.camera.position;
	const t_vec3f camdirf = d->scene.camera.dir;

	d->scene.camera.view = mat4_look_at_f(camposf, \
							camposf + camdirf, \
							(t_vec3f){0.0f, 1.0f, 0.0f, 0.0f});
	d->scene.camera.inv_view = mat4_inverse(d->scene.camera.view);
}

void recalculated_projection(t_data *d)
{
	d->scene.camera.projection = mat4_perspective(fov_radians(d->scene.camera.vertical_fov), \
								(float)d->utils.width / (float)d->utils.height, \
								d->scene.camera.zNear, d->scene.camera.zFar);
	d->scene.camera.inv_projection = mat4_inverse(d->scene.camera.projection);
}
