/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/03/28 15:38:57 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//?	Ambient lightning:
//?		∗ identifier: A
//?		∗ ambient lighting ratio in range [0.0,1.0]: 0.2
//?		∗ R,G,B colors in range [0-255]: 255, 255, 255

bool	parse_ambient_light(char **split, t_scene *scene)
{
	if (ft_split_count(split) != 3)
		return (print_error("ambient light arg count"));
	if (ft_stof(split[1], &scene->ambient_light) == false)
		return (print_error("ambient light intensity"));
	if (scene->ambient_light < 0.0f || scene->ambient_light > 1.0f)
		return (print_error("ambient light intensity range"));
	if (parse_8bit_color(split[2], &scene->ambient_color) == false)
		return (print_error("ambient light color"));
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

	if (ft_split_count(split) != 4)
		return (print_error("light arg count"));
	if (parse_vec3(split[1], &point_light.position) == false)
		return (print_error("light position"));
	if (ft_stof(split[2], &point_light.intensity) == false)
		return (print_error("light intensity"));
	if (parse_8bit_color(split[3], &point_light.color) == false)
		return (print_error("light color"));
	vec_push(&scene->point_lights, &point_light);
	return (true);
}

bool	parse_load_hdri(const char *path, t_hdri *hdri)
{
	int			ret;
	const char	*err;

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

	if (once == true)
	{
		print_warning("hdri already defined,\
			only first definition will be used");
		return (true);
	}
	if (ft_split_count(split) != 2)
		return (print_error("hdri arg count"));
	printf("split[1]: %s\n", split[1]);
	if (parse_load_hdri(split[1], &hdri) == false)
		return (print_error("hdri path"));
	once = true;
	scene->hdri = hdri;
	return (true);
}
