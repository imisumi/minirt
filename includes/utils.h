/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/09 14:43:03 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "../includes/minirt.h"

uint32_t ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

float max(float a, float b);

// uint32_t vec4_convert_to_rgba(t_rgba color);
uint32_t vec4_to_int32_color(t_vec4 color);

uint32_t vec3_convert_to_rgb(t_vec3 color);

void	ft_mlx_put_pixel(t_fdf *data, int x, int y, uint32_t color);

#endif
