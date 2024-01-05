/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/05 20:55:12 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//?	Sphere:
//?		∗ identifier: pl
//?		∗ x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
//?		∗ 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
//?		∗ R,G,B colors in range [0-255]: 0,0,225


bool	parse_plane(char **split, t_scene *scene)
{
	t_inv_plane	plane;

	if (ft_split_count(split) != 4)
	{
		print_error("plane arg count");
		return (false);
	}
	if (parse_vec3(split[1], &plane.position) == false)
	{
		print_error("plane position");
		return (false);
	}
	if (parse_vec3_normal(split[2], &plane.normal) == false)
	{
		print_error("plane normal out of range [-1, 1]");
		return (false);
	}
	t_material	material;
	if (parse_8bit_color(split[3], &material.color) == false)
	{
		print_error("plane color");
		return (false);
	}
	plane.material = material;
	array_push(&scene->inv_planes, &plane);
	return (true);
}
