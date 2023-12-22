/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:25:20 by ichiro            #+#    #+#             */
/*   Updated: 2023/12/17 22:30:01 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	resize_window(void *param)
{
	t_data	*data;

	data = param;
	if (PIXEL_SIZE != 1)
		return ;
	if (data->mlx->width == data->img->width && data->mlx->height == data->img->height)
		return ;
	data->utils.accumulated_frames = 1;
	if (!mlx_resize_image(data->img, data->mlx->width, data->mlx->height))
	{
		printf("Error\n");
		exit(1);
	}
	free(data->utils.accumulated_data);
	free(data->scene.camera.ray_target);
	free(data->scene.camera.ray_dir);

	data->utils.width = data->mlx->width;
	data->utils.height = data->mlx->height;

	data->utils.accumulated_data = malloc(sizeof(t_vec4f) * data->utils.width * data->utils.height);
	data->scene.camera.ray_target = malloc(sizeof(t_vec4f) * data->utils.width * data->utils.height);
	data->scene.camera.ray_dir = malloc(sizeof(t_vec3f) * data->utils.width * data->utils.height);

	data->scene.camera.aspectRatio = (float)data->utils.width / (float)data->utils.height;

	recalculate_view(data);
	recalculated_projection(data);
	recalculat_ray_directions(data);
}
