/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 20:36:00 by ichiro            #+#    #+#             */
/*   Updated: 2023/12/17 21:49:57 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_cam_pos(t_data *data, t_vec3f v, bool *moved)
{
	data->scene.camera.position += v;
	*moved = true;
}

void	detect_cam_movement(t_data *data, t_vec3f right_dir, bool *moved)
{
	const float		speed = time_delta(data->utils.prev_frame) * 10.0f;
	const t_vec3f	up_direction = {0.0f, 1.0f, 0.0f, 0.0f};

	data->utils.prev_frame = glfwGetTime();
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		update_cam_pos(data, data->scene.camera.dir * speed, moved);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		update_cam_pos(data, -data->scene.camera.dir * speed, moved);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		update_cam_pos(data, -right_dir * speed, moved);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		update_cam_pos(data, right_dir * speed, moved);
	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
		update_cam_pos(data, up_direction * speed, moved);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT))
		update_cam_pos(data, -up_direction * speed, moved);
}

void	calculate_new_cam_dir(t_data *data, t_vec3f up_dir, t_vec3f right_dir)
{
	const float		pitch = data->scene.camera.mouse_delta[Y] * -0.01f;
	const float		yaw = data->scene.camera.mouse_delta[X] * 0.01f;
	const t_quat	pitch_rotation = quat_angle_axis_f(-pitch, right_dir);
	const t_quat	yaw_rotation = quat_angle_axis_f(-yaw, up_dir);
	const t_quat	q = quat_normalize(quat_cross(pitch_rotation, \
													yaw_rotation));

	data->scene.camera.dir = quat_rotate_f(q, data->scene.camera.dir);
	data->scene.camera.mouse_delta[X] = 0;
	data->scene.camera.mouse_delta[Y] = 0;
}

void	detect_cam_rotation(t_data *data, bool *rotated, t_vec3f right_dir)
{
	int				x;
	int				y;
	t_vec2f			mouse_pos;
	const t_vec3f	up_dir = {0.0f, 1.0f, 0.0f, 0.0f};
	const t_vec2f	prev_m_pos = data->scene.camera.prev_mouse_pos;

	mouse_pos = data->scene.camera.mouse_pos;
	if (prev_m_pos[X] >= 0 && prev_m_pos[Y] >= 0)
	{
		mlx_get_mouse_pos(data->mlx, &x, &y);
		mouse_pos = prev_m_pos - (t_vec2f){(float)x, (float)y};
		if (mouse_pos[X] != prev_m_pos[X] && mouse_pos[Y] != prev_m_pos[Y])
		{
			data->scene.camera.mouse_delta[X] += -mouse_pos[X] * 0.12f;
			data->scene.camera.mouse_delta[Y] += mouse_pos[Y] * 0.12f;
		}
	}
	mlx_get_mouse_pos(data->mlx, &x, &y);
	data->scene.camera.prev_mouse_pos = (t_vec2f){(float)x, (float)y};
	if (data->scene.camera.mouse_delta[X] != 0 || \
			data->scene.camera.mouse_delta[Y] != 0)
	{
		calculate_new_cam_dir(data, up_dir, right_dir);
		*rotated = true;
	}
}

void	handle_input(t_data *d)
{
	bool			moved;
	bool			rotated;
	const t_vec3f	up_dir = {0.0f, 1.0f, 0.0f, 0.0f};
	const t_vec3f	right_dir = vec3f_cross(d->scene.camera.dir, up_dir);

	moved = false;
	rotated = false;
	detect_cam_movement(d, right_dir, &moved);
	detect_cam_rotation(d, &rotated, right_dir);
	if (moved || rotated)
	{
		d->utils.accumulated_frames = 1;
		recalculate_view(d);
		if (rotated)
			recalculat_ray_directions(d);
	}
}

void	movement(t_data *data)
{
	if (!mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		data->scene.camera.mouse_lock = false;
		data->scene.camera.prev_mouse_pos[X] = -1;
		data->scene.camera.prev_mouse_pos[Y] = -1;
		data->scene.camera.mouse_pos[X] = 0;
		data->scene.camera.mouse_pos[Y] = 0;
		data->utils.prev_frame = glfwGetTime();
		return ;
	}
	handle_input(data);
}
