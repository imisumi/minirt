/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:23:41 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/12 16:21:47 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// uint32_t	global_frame = 1;

void	frame_times(void *param)
{
	t_data	*data;

	data = param;
	double currentTime = glfwGetTime();
	double deltaTime = currentTime - data->utils.prev_frame;
	double frameTimeMs = deltaTime * 1000.0;
	double fps = 1000.0 / frameTimeMs;
	// printf("\rframeTimeMs: %.2f ms    frames: %d", frameTimeMs, global_frame);
	char output[50];
	snprintf(output, 50, "%.2f", fps);
	mlx_set_window_title(data->mlx, output);
	fflush(stdout);
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

void	render_loop(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		return (mlx_close_window(data->mlx));
	resize_window(data);
	movement(data);
	if (render_zone(data) == false)
		return ;
	if (BONUS)
		frame_times(param);
	if (data->utils.global_frame % 100 == 0)
	{
		screenshot(data);
	}
	data->utils.accumulated_frames++;
	data->utils.global_frame ++;
}
