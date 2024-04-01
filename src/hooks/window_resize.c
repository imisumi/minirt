/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:25:20 by ichiro            #+#    #+#             */
/*   Updated: 2024/03/28 15:36:54 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	realloc_buffers(t_data *data)
{
	free(data->utils.accumulated_data);
	free(data->scene.camera.ray_dir);
	data->utils.accumulated_data = malloc(sizeof(t_vec4f) * \
		data->utils.width * data->utils.height);
	data->scene.camera.ray_dir = malloc(sizeof(t_vec3f) * \
		data->utils.width * data->utils.height);
	if (!data->utils.accumulated_data || !data->scene.camera.ray_dir)
		exit_error(MALLOC, "resize window");
}

void	resize_window(t_data *data)
{
	if (PIXEL_SIZE != 1)
		return ;
	if (data->mlx->width == (int32_t)data->img->width && \
		data->mlx->height == (int32_t)data->img->height)
		return ;
	data->utils.accumulated_frames = 1;
	if (!mlx_resize_image(data->img, data->mlx->width, data->mlx->height))
		exit_error(MLX_IMG, "resize window");
	data->utils.width = data->mlx->width;
	data->utils.height = data->mlx->height;
	realloc_buffers(data);
	data->scene.camera.aspectRatio = (float)data->utils.width / \
		(float)data->utils.height;
	recalculate_view(data);
	recalculated_projection(data);
	recalculat_ray_directions(data);
}
