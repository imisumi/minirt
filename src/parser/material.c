/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/13 00:00:52 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_material	default_material(void)
{
	t_material	material;

	material.color = (t_vec3f){1.0f, 0.0f, 1.0f, 0.0f};
	material.roughness = 1.0f;
	material.emission_strength = 0.0f;
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
	//? color
	if (parse_8bit_color(split[0], &mat->color) == false)
	{
		print_error("sphere color");
		return (false);
	}
	//? roughness
	if (ft_stof(split[1], &mat->roughness) == false)
	{
		print_error("sphere roughness");
		return (false);
	}

	//? specular
	if (ft_stof(split[2], &mat->specular) == false)
	{
		print_error("sphere emission strength");
		return (false);
	}

	//? specular_color
	if (parse_8bit_color(split[3], &mat->specular_color) == false)
	{
		print_error("sphere emission strength");
		return (false);
	}

	//? ior
	if (ft_stof(split[4], &mat->ior) == false)
	{
		print_error("sphere emission strength");
		return (false);
	}

	//? refraction
	if (ft_stof(split[5], &mat->refraction) == false)
	{
		print_error("sphere emission strength");
		return (false);
	}

	//? refraction_roughness
	if (ft_stof(split[6], &mat->refraction_roughness) == false)
	{
		print_error("sphere emission strength");
		return (false);
	}
	
	//? refraction_color
	if (parse_8bit_color(split[7], &mat->refraction_color) == false)
	{
		print_error("sphere emission strength");
		return (false);
	}

	
	//? emission
	if (ft_stof(split[8], &mat->emission_strength) == false)
	{
		print_error("sphere emission strength");
		return (false);
	}

	return (true);
}
