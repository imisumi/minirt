/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/03/28 16:31:33 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_material	default_material(void)
{
	const t_material	material = {
		.color = (t_vec3f){1.0f, 0.0f, 1.0f, 0.0f},
		.roughness = 1.0f,
		.specular = 0.0f,
		.specular_color = (t_vec3f){1.0f, 1.0f, 1.0f, 0.0f},
		.ior = 1.4f,
		.refraction = 0.0f,
		.refraction_roughness = 0.0f,
		.refraction_color = (t_vec3f){1.0f, 1.0f, 1.0f, 0.0f},
		.emission_strength = 0.0f};

	return (material);
}

//TODO bounds check
bool	parse_material(t_material *mat, char **split)
{
	*mat = default_material();
	if (parse_8bit_color(split[0], &mat->color) == false)
		return (print_error("sphere color"));
	if (!BONUS)
		return (true);
	if (ft_split_count(split) != 9)
		return (true);
	if (ft_stof(split[1], &mat->roughness) == false)
		return (print_error("sphere roughness"));
	if (ft_stof(split[2], &mat->specular) == false)
		return (print_error("sphere specular"));
	if (parse_8bit_color(split[3], &mat->specular_color) == false)
		return (print_error("sphere specular color"));
	if (ft_stof(split[4], &mat->ior) == false)
		return (print_error("sphere ior"));
	if (ft_stof(split[5], &mat->refraction) == false)
		return (print_error("sphere refraction"));
	if (ft_stof(split[6], &mat->refraction_roughness) == false)
		return (print_error("sphere refraction roughness"));
	if (parse_8bit_color(split[7], &mat->refraction_color) == false)
		return (print_error("sphere refraction color"));
	if (ft_stof(split[8], &mat->emission_strength) == false)
		return (print_error("sphere emission strength"));
	return (true);
}
