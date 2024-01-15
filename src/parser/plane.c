/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/15 15:10:15 by imisumi          ###   ########.fr       */
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

	int arg_count = ft_split_count(split);
	if (arg_count != 4 && arg_count != 6)
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
	// t_material	material;
	// if (parse_8bit_color(split[3], &material.color) == false)
	// {
	// 	print_error("plane color");
	// 	return (false);
	// }
	// plane.material = material;
	if (arg_count == 4)
	{
		plane.material = default_material();
		parse_8bit_color(split[3], &plane.material.color);
	}
	else if (parse_material(&plane.material, &split[3]) == false)
		return (false);
	array_push(&scene->inv_planes, &plane);
	return (true);
}
