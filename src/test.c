/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:25:59 by ichiro            #+#    #+#             */
/*   Updated: 2023/12/11 14:03:14 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_vec3	default_sky(t_vec3 direction)
// {
// 	t_vec3	sky;
// 	float	t;

// 	t = 0.5f * (vec3_normalize(direction).y + 1.0f);
// 	sky = vec3_add(vec3_mulf((t_vec3){1.0f, 1.0f, 1.0f}, 1.0f - t), \
// 					vec3_mulf((t_vec3){0.5f, 0.7f, 1.0f}, t));
// 	return (sky);
// }

// uint32_t	get_rngstate(t_data *data, uint32_t x, uint32_t y)
// {
// 	t_vec2		coord;
// 	t_vec2		num_pixels;
// 	uint32_t	pixel_index;

// 	coord = (t_vec2){(float)x / (float)(data->utils.width), (float)y / (float)(data->utils.height)};
// 	num_pixels = (t_vec2){(float)data->utils.width, (float)data->utils.height};
// 	coord = vec2_mul(coord, num_pixels);
// 	pixel_index = coord.x + coord.y * num_pixels.x;
// 	return (pixel_index + global_frame * 719393);
// }
