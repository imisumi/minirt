/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:23:41 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/16 20:40:36 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	frame_times(void *param)
{
	t_data	*data;
	double	delta_time;
	double	frame_time_ms;
	double	fps;
	char	output[50];

	if (!BONUS)
		return ;
	data = param;
	delta_time = glfwGetTime() - data->utils.prev_frame;
	frame_time_ms = delta_time * 1000.0;
	fps = 1000.0 / frame_time_ms;
	snprintf(output, 50, "%.2f", fps);
	mlx_set_window_title(data->mlx, output);
}

static void	movement(t_data *data)
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
