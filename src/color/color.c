/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:03:04 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/14 04:49:42 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

uint32_t	ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	vec4f_to_color(t_vec4f c)
{
	const uint32_t	color = ft_pixel(\
		(uint8_t)(c[X] * 255.0), \
		(uint8_t)(c[Y] * 255.0), \
		(uint8_t)(c[Z] * 255.0), \
		255);

	return (color);
}

//TODO use num chanels instead of 4
static t_vec3f	sample_exr_texture(float u, float v, t_hdri *hdri)
{
	t_vec3f	color;
	int		x;
	int		y;
	int		pixel_index;

	u = fmax(0.0f, fmin(1.0f, u));
	v = fmax(0.0f, fmin(1.0f, v));
	x = u * (hdri->width - 1);
	y = v * (hdri->height - 1);
	pixel_index = (x + (hdri->height - 1 - y) * hdri->width) * 4;
	color[X] = hdri->rgba[pixel_index];
	color[Y] = hdri->rgba[pixel_index + 1];
	color[Z] = hdri->rgba[pixel_index + 2];
	return (color);
}

t_vec3f	texture(t_vec3f normal, t_hdri *hdri)
{
	const float		phi = atan2(normal[Z], normal[X]);
	const float		theta = asinf(normal[Y]);
	const float		u = 1.0f - (phi + PI) / TWO_PI;
	const float		v = (theta + PI / 2.0f) / PI;
	const t_vec3f	color = sample_exr_texture(u, v, hdri);

	return (color);
}
