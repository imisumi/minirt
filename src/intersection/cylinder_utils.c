/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:36:28 by ichiro            #+#    #+#             */
/*   Updated: 2024/03/08 03:47:11 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	angle_between_vec3(t_vec3f v1, t_vec3f v2)
{
	return (acos(vec3f_dot(v1, v2) / (vec3f_length(v1) * vec3f_length(v2))));
}

t_vec3f	create_rotation_axis(t_vec3f normal, t_vec3f up)
{
	return (vec3f_normalize(vec3f_cross(normal, up)));
}

void	apply_cap_hitinfo(t_hitinfo *hitinfo, t_vec3f hitpoint, \
	float distance, t_cylinder *cylinder)
{
	hitinfo->hit = true;
	hitinfo->distance = distance;
	hitinfo->position = hitpoint;
	hitinfo->normal = cylinder->normal;
	hitinfo->material = cylinder->material;
}
