/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:16:03 by imisumi           #+#    #+#             */
/*   Updated: 2023/06/09 14:44:17 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/minirt.h"
#include "../includes/utils.h"

uint32_t ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

float max(float a, float b) {
    return (a > b) ? a : b;
}

// uint32_t vec4_convert_to_rgba(t_rgba color)
// {
// 	uint8_t r = color.r * 255;
// 	uint8_t g = color.g * 255;
// 	uint8_t b = color.b * 255;
// 	uint8_t a = color.a * 255;
// 	uint32_t res = ft_pixel(r, g, b, a);
// 	return (res);
// }

uint32_t vec4_to_int32_color(t_vec4 color)
{
	uint8_t r = color.x * 255;
	uint8_t g = color.y * 255;
	uint8_t b = color.z * 255;
	uint8_t a = color.w * 255;
	uint32_t res = ft_pixel(r, g, b, a);
	return (res);
}

uint32_t vec3_convert_to_rgb(t_vec3 color)
{
	uint8_t r = color.x * 255;
	uint8_t g = color.y * 255;
	uint8_t b = color.z * 255;
	uint8_t a = 255;
	uint32_t res = ft_pixel(r, g, b, a);
	return (res);
}

void	ft_mlx_put_pixel(t_fdf *data, int x, int y, uint32_t color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		mlx_put_pixel(data->image, x, y, color);
}