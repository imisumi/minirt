/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:16:18 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/18 03:33:48 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	setup_mlx(t_data *data)
{
	bool	resizeble;

	resizeble = false;
	if (PIXEL_SIZE == 1)
		resizeble = true;
	data->mlx = mlx_init(WIDTH * PIXEL_SIZE, HEIGHT * PIXEL_SIZE, \
		"Ray Tracer", resizeble);
	if (data->mlx == NULL)
	{
		*error() = MLX_INIT;
		return (false);
	}
	data->img = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height);
	if (data->img == NULL)
	{
		*error() = MLX_IMG;
		mlx_close_window(data->mlx);
		return (false);
	}
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		*error() = MLX_IMG_TO_WIN;
		mlx_close_window(data->mlx);
		return (false);
	}
	return (true);
}

bool	run_mlx(t_data *data)
{
	if (setup_mlx(data) == false)
	{
		print_error("Error");
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(data->mlx, render_loop, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (true);
}
