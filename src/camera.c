/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:16:03 by imisumi           #+#    #+#             */
/*   Updated: 2023/06/10 04:32:48 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "stdbool.h"

void camera(t_fdf *data, float verticalFOV, float nearClip, float farClip)
{
	data->camera.vertical_fov = verticalFOV;
	data->camera.near_clip = nearClip;
	data->camera.far_clip = farClip;
	
	data->camera.for_dir = (t_vec3){0.0f, 0.0f, -1.0f};
	data->camera.pos = (t_vec3){0.0f, 0.0f, 3.0f};
}

void recalculate_view(t_fdf *data)
{
	t_vec3 up = { 0.0f, 1.0f, 0.0f };
	
	data->camera.view = mat4_lookAt(data->camera.pos, vec3_add(data->camera.pos, data->camera.for_dir), up);
	data->camera.inv_view = inverse_mat4(data->camera.view);

	print_matrix(data->camera.inv_view);
	// print_matrix(mat4_mul_mat4(data->camera.view, data->camera.inv_view));
	// t_mat4 temp;
	// temp.m[0][0] = 1.0f;
	// temp.m[0][1] = 1.0f;
	// temp.m[0][2] = 1.0f;
	// temp.m[0][3] = -1.0f;

	// temp.m[1][0] = 1.0f;
	// temp.m[1][1] = 1.0f;
	// temp.m[1][2] = -1.0f;
	// temp.m[1][3] = 1.0f;

	// temp.m[2][0] = 5.0f;
	// temp.m[2][1] = -1.0f;
	// temp.m[2][2] = 1.0f;
	// temp.m[2][3] = 1.0f;

	// temp.m[3][0] = -1.0f;
	// temp.m[3][1] = 1.0f;
	// temp.m[3][2] = 1.0f;
	// temp.m[3][3] = 1.0f;


	// data->camera.inv_view = inverse_mat4(temp);
	// t_mat4 t = mat4_mul_mat4(temp, data->camera.inv_view);
	// print_matrix(data->camera.inv_view);
	// print_matrix(t);
}

void on_update(t_fdf *data)
{
	// camera(data, 45.0f, 0.1f, 100.0f);
	t_vec2 mous_pos = (t_vec2){data->mouse.x, data->mouse.y};
	t_vec2 delta = (t_vec2){data->mouse.x - data->mouse.x_prev, data->mouse.y - data->mouse.y_prev};
	delta = vec2_mul_float(delta, 0.002f);
	if (data->mouse.button != 1 || data->mouse.action != 1) {
		return;
	}

	bool moved = false;

	t_vec3 up_dir = (t_vec3){0.0f, 1.0f, 0.0f};
	t_vec3 right_dir = vec3_cross(data->camera.for_dir, up_dir);
	// printf("right_dir: %f, %f, %f\n", right_dir.x, right_dir.y, right_dir.z);

	float speed = 0.5f;
	float ts = 0.1f;

	// TODO Movement
	//! forward - backward
	if (mlx_is_key_down(data->mlx, MLX_KEY_W)) {
		data->camera.pos = vec3_add(data->camera.pos , vec3_mul_float(data->camera.for_dir, (speed * ts)));
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S)) {
		data->camera.pos = vec3_sub(data->camera.pos , vec3_mul_float(data->camera.for_dir, (speed * ts)));
	}
	//! left - right
	if (mlx_is_key_down(data->mlx, MLX_KEY_A)) {
		data->camera.pos = vec3_sub(data->camera.pos , vec3_mul_float(right_dir, (speed * ts)));
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D)) {
		data->camera.pos = vec3_add(data->camera.pos , vec3_mul_float(right_dir, (speed * ts)));
	}
	//! up - down
	if (mlx_is_key_down(data->mlx, MLX_KEY_Q)) {
		data->camera.pos = vec3_sub(data->camera.pos , vec3_mul_float(up_dir, (speed * ts)));
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_E)) {
		data->camera.pos = vec3_add(data->camera.pos , vec3_mul_float(up_dir, (speed * ts)));
	}

	// TODO Rotation
	if (delta.x != 0.0f || delta.y != 0.0f) {
		float pitch_detla = delta.y * data->camera.rotation_speed;
		float yaw_delta = delta.x * data->camera.rotation_speed;

		t_vec3 angle_1 = vec3_angle_axis(-pitch_detla, right_dir);
		t_vec3 angle_2 = vec3_angle_axis(-yaw_delta, (t_vec3){0.0f, 1.0f, 0.0f});
		t_vec3 quat = vec3_cross(angle_1, angle_2);
		quat = vec3_normalize(quat);

		data->camera.for_dir = vec3_rotate(data->camera.for_dir, quat);
	}

	recalculate_view(data);
	// recalculate_ray_dir(data);


	
	printf("pos: %f, %f, %f\n", data->camera.pos.x, data->camera.pos.y, data->camera.pos.z);

	if (moved) {
		// recalculate_view();
		// recalculate_ray_dir();
	}

	// printf("mouse pos: %f, %f\n", mous_pos.x, mous_pos.y);
	// printf("delta: %f, %f\n", delta.x, delta.y);
	// printf("%d	%d\n", data->mouse.button, data->mouse.action);
}