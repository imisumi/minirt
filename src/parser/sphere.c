/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/05/02 12:40:56 by imisumi          ###   ########.fr       */
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
	t_sphere		sphere;
	const uint32_t	arg_count = ft_split_count(split);

	if (!BONUS && arg_count != 4)
		return (print_error("sphere arg count"));
	if (arg_count != 4 && arg_count != 12)
		return (print_error("sphere arg count"));
	if (parse_vec3(split[1], &sphere.pos_f) == false)
		return (print_error("sphere position"));
	if (ft_stof(split[2], &sphere.radius) == false)
		return (print_error("sphere radius"));
	if (sphere.radius <= EPSILON)
		return (print_error("sphere radius range"));
	if (parse_material(&sphere.material, &split[3]) == false)
		return (false);
	vec_push(&scene->spheres, &sphere);
	return (true);
}
