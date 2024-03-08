/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/03/07 18:08:07 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//?	plane:
//?	∗ identifier: pl
//?	∗ x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
//?	∗ 3d normalized vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
//?	∗ R,G,B colors in range [0-255]: 0,0,225

bool	parse_plane(char **split, t_scene *scene)
{
	t_inv_plane		plane;
	const uint32_t	arg_count = ft_split_count(split);

	if (arg_count != 4 && arg_count != 6)
		return (print_error("plane arg count"));
	if (parse_vec3(split[1], &plane.position) == false)
		return (print_error("plane position"));
	if (parse_vec3_normal(split[2], &plane.normal) == false)
		return (print_error("plane normal out of range [-1, 1]"));
	if (arg_count == 4)
	{
		plane.material = default_material();
		parse_8bit_color(split[3], &plane.material.color);
	}
	else if (parse_material(&plane.material, &split[3]) == false)
		return (false);
	vec_push(&scene->inv_planes, &plane);
	return (true);
}
