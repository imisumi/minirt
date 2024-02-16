/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/16 19:35:45 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_camera(t_camera *cam)
{
	cam->position = (t_vec3f){6.0f, 2.0, 30.0f, 0.0f};
	cam->dir = (t_vec3f){0.0, 0.2, -1.0, 0.0};
	cam->mouse_delta[X] = 0;
	cam->mouse_delta[Y] = 0;
	cam->projection = mat4_identity();
	cam->inv_projection = mat4_identity();
	cam->view = mat4_identity();
	cam->inv_view = mat4_identity();
	cam->vertical_fov = 45.0f;
	cam->aspectRatio = (float)WIDTH / (float)HEIGHT;
	cam->zNear = 0.1f;
	cam->zFar = 1000.0f;
	cam->prev_mouse_pos[X] = -1;
	cam->prev_mouse_pos[Y] = -1;
}
