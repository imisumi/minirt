/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/09 13:54:56 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//?	Camera:
//?		∗ identifier: C
//?		∗ x,y,z coordinates of the view point: -50.0,0,20
//?		∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
//?		  0.0,0.0,1.0
//?		∗ FOV : Horizontal field of view in degrees in range [0,180]: 70


bool	parse_camera(char **split, t_camera *camera)
{
	// printf("Camera parser\n");
	if (ft_split_count(split) != 4)
	{
		print_error("camera arg count");
		return (false);
	}
	if (parse_vec3(split[1], &camera->position) == false)
	{
		print_error("camera position");
		return (false);
	}
	if (parse_vec3_normal(split[2], &camera->dir) == false)
	{
		print_error("camera direction out of range [-1, 1]");
		return (false);
	}
	if (ft_stof(split[3], &camera->vertical_fov) == false)
		return (print_error("camera fov"), false);
	//TODO 0 - 180 weird redshift does 0.2 - 174
	if (camera->vertical_fov < 0.0f || camera->vertical_fov > 180.0f)
		return (print_error("camera fov range"), false);
	return (true);
}
