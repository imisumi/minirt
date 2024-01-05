/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/05 20:58:03 by imisumi-wsl      ###   ########.fr       */
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
	printf("Camera parser\n");
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
	{
		print_error("camera fov");
		return (false);
	}
	if (camera->vertical_fov < 0.0f || camera->vertical_fov > 180.0f)
	{
		print_error("camera fov range");
		return (false);
	}
	// scene->camera = camera;
	return (true);
}
