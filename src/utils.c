/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:03:04 by ichiro            #+#    #+#             */
/*   Updated: 2024/04/22 21:54:28 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <GLFW/glfw3.h>

void	put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color)
{
	if (x < image->width && y < image->height)
		mlx_put_pixel(image, x, y, color);
}

double	time_delta(double prev_frame)
{
	return (glfwGetTime() - prev_frame);
}

float	fov_radians(float fov)
{
	return (fov * (M_PI / 180.0f));
}
