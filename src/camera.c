/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/25 21:38:35 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/camera.h"

// void recalculate_view(t_mlx *d)
// {
// 	// print_mat4(d->scene.camera.projection);
// 	// printf("%f %f %f\n", d->scene.camera.position.x, d->scene.camera.position.y, d->scene.camera.position.z);
// 	// printf("%f %f %f\n\n", d->scene.camera.direction.x, d->scene.camera.direction.y, d->scene.camera.direction.z);

// 	d->scene.camera.view = mat4_look_at(d->scene.camera.position, \
// 							vec3_add(d->scene.camera.position, d->scene.camera.direction), \
// 							vec3_create(0.0f, 1.0f, 0.0f));
// 	d->scene.camera.inv_view = mat4_inverse(d->scene.camera.view);
// 	// print_mat4(d->scene.camera.view);
// 	// print_mat4(d->scene.camera.inv_view);

// }
