/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/10 16:45:37 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_material	default_material(void)
{
	t_material	material;

	material.color = (t_vec3f){1.0f, 0.0f, 1.0f, 0.0f};
	material.roughness = 1.0f;
	return (material);
}

bool	parse_material(t_material *mat, char **split)
{
	printf("Material parser\n");
	// print split
	// printf("split count: %ld\n", ft_split_count(split));
	// for (int i = 0; split[i]; i++)
	// 	printf("split[%d]: %s\n", i, split[i]);

	*mat = default_material();
	if (!BONUS)
		return (true);
	// return (true);

	if (parse_8bit_color(split[0], &mat->color) == false)
	{
		print_error("sphere color");
		return (false);
	}
	if (ft_stof(split[1], &mat->roughness) == false)
	{
		print_error("sphere roughness");
		return (false);
	}
	if (mat->roughness < 0.0f || mat->roughness > 1.0f)
	{
		print_error("sphere roughness range");
		return (false);
	}
	return (true);
}
