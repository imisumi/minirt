/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/06 17:06:11 by imisumi-wsl      ###   ########.fr       */
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
	// if (ft_split_count(split) != 4)
	// 	return (false);
	// printf("split count: %ld\n", ft_split_count(split));
	t_sphere	sphere;
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
	// printf("--------------\n");
	// printf("%f, %f, %f\n", sphere.pos_f[X], sphere.pos_f[Y], sphere.pos_f[Z]);
	// printf("%f\n", sphere.radius);
	// printf("%f, %f, %f\n", material.color[R], material.color[G], material.color[B]);
	
	sphere.material = material;
	array_push(&scene->spheres, &sphere);
	return (true);
}
