/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/20 14:56:46 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//?	Ambient lightning:
//?		∗ identifier: A
//?		∗ ambient lighting ratio in range [0.0,1.0]: 0.2
//?		∗ R,G,B colors in range [0-255]: 255, 255, 255

bool	parse_ambient_light(char **split, t_scene *scene)
{
	// printf("Ambient light parser\n");
	if (ft_split_count(split) != 3)
	{
		print_error("ambient light arg count");
		return (false);
	}
	if (ft_stof(split[1], &scene->ambient_light) == false)
	{
		print_error("ambient light intensity");
		return (false);
	}
	if (scene->ambient_light < 0.0f || scene->ambient_light > 1.0f)
	{
		print_error("ambient light intensity range");
		return (false);
	}
	if (parse_8bit_color(split[2], &scene->ambient_color) == false)
	{
		print_error("ambient light color");
		return (false);
	}
	return (true);
}

//?	Light:
//?		∗ identifier: L
//?		∗ x,y,z coordinates of the light point: -40.0,50.0,0.0
//!		∗ the light brightness ratio in range [0.0,1.0]: 0.6
//?		∗ the light brightness ratio: 25.5f
//?		∗ (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255

bool	parse_light(char **split, t_scene *scene)
{
	t_point_light	point_light;

	// printf("Light parser\n");
	if (ft_split_count(split) != 4)
	{
		print_error("light arg count");
		return (false);
	}
	if (parse_vec3(split[1], &point_light.position) == false)
	{
		print_error("light position");
		return (false);
	}
	if (ft_stof(split[2], &point_light.intensity) == false)
	{
		print_error("light brightness");
		return (false);
	}
	if (parse_8bit_color(split[3], &point_light.color) == false)
	{
		print_error("light color");
		return (false);
	}
	vec_push(&scene->point_lights, &point_light);
	return (true);
}

	// printf("--------------\n");
	// printf("%f, %f, %f\n", point_light.position[X], \
//		point_light.position[Y], point_light.position[Z]);
	// printf("%f\n", point_light.intensity);
	// printf("%f, %f, %f\n", point_light.color[R], point_light.color[G], \
//		point_light.color[B]);


bool	parse_load_hdri(const char *path, t_hdri *hdri)
{
	int			ret;
	int			width;
	int			height;
	const char*	err;

	ret = LoadEXR(&hdri->rgba, &hdri->width, &hdri->height, path, NULL);
	if (ret != 0)
	{
		printf("Error: %s\n", err);
		return (false);
	}
	printf("w: %d\n", hdri->width);
	printf("h: %d\n", hdri->height);
	return (true);
}


bool	parse_hdri(char **split, t_scene *scene)
{
	t_hdri		hdri;
	static bool	once = false;

	// printf("HDRI parser\n");
	if (once == true)
	{
		printf("Warning: hdri already defined, only first definition will be used\n");
		return (true);
	}
	if (ft_split_count(split) != 2)
	{
		print_error("hdri arg count");
		return (false);
	}
	printf("split[1]: %s\n", split[1]);
	if (parse_load_hdri(split[1], &hdri) == false)
	{
		print_error("hdri path");
		return (false);
	}
	once = true;
	scene->hdri = hdri;
	return (true);
}
