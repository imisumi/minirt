/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/09 13:54:38 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


//?	Sphere:
//?		∗ identifier: sp
//?		∗ x,y,z coordinates of the sphere center: 0.0,0.0,20.6
//?		∗ the sphere d̶i̶a̶m̶e̶t̶e̶r radius: 12.6
//?		∗ R,G,B colors in range [0-255]: 10, 0, 255

bool	parse_sphere(t_scene *scene, char **split)
{
	t_sphere	sphere;

	if (ft_split_count(split) != 4)
	{
		print_error("sphere arg count");
		return (false);
	}
	if (parse_vec3(split[1], &sphere.pos_f) == false)
	{
		print_error("sphere position");
		return (false);
	}
	if (ft_stof(split[2], &sphere.radius) == false)
	{
		print_error("sphere radius");
		return (false);
	}
	t_material	material;
	if (parse_8bit_color(split[3], &material.color) == false)
	{
		print_error("sphere color");
		return (false);
	}
	sphere.material = material;
	array_push(&scene->spheres, &sphere);
	return (true);
}

	// printf("--------------\n");
	// printf("%f, %f, %f\n", sphere.pos_f[X], sphere.pos_f[Y], sphere.pos_f[Z]);
	// printf("%f\n", sphere.radius);
	// printf("%f, %f, %f\n", material.color[R], material.color[G], material.color[B]);
