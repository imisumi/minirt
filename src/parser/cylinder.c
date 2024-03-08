/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/03/08 03:48:42 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//?	cyliner:
//?	∗ identifier: cy
//?	∗ x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
//?	∗ 3d normalized vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
//?	∗ the cylinder radius: 5.0
//?	∗ the cylinder height: 21.3
//?	∗ R,G,B colors in range [0-255]: 0,0,225
//TODO: bonus materials
bool	parse_cylinder(char **split, t_scene *scene)
{
	t_cylinder		cylinder;
	const uint32_t	arg_count = ft_split_count(split);

	if (arg_count != 6)
		return (print_error("cylinder arg count"));
	if (parse_vec3(split[1], &cylinder.position) == false)
		return (print_error("cylinder position"));
	if (parse_vec3_normal(split[2], &cylinder.normal) == false)
		return (print_error("cylinder normal out of range [-1, 1]"));
	if (ft_stof(split[3], &cylinder.radius) == false)
		return (print_error("cylinder radius"));
	if (ft_stof(split[4], &cylinder.height) == false)
		return (print_error("cylinder height"));
	if (cylinder.radius < 0 || cylinder.height < 0)
		return (print_error("cylinder radius or height"));
	cylinder.material = default_material();
	if (parse_8bit_color(split[5], &cylinder.material.color) == false)
		return (print_error("cylinder color"));
	vec_push(&scene->cylinders, &cylinder);
	return (true);
}
