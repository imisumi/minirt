/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/10 15:14:54 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "../includes/minirt.h"

void camera(t_fdf *data, float verticalFOV, float nearClip, float farClip);
void on_update(t_fdf *data);

int gauss_jordan(t_mat4 mat, t_mat4 inv);
t_mat4 perspective(float fov, float width, float height, float nearclip, float farclip);


#endif
