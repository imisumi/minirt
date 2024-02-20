/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/20 16:48:18 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define AMBIENT   "A"
#define CAMERA    "C"
#define LIGHT     "L"
#define SPHERE    "sp"
#define PLANE     "pl"
#define CYLINDER  "cy"
#define HDRI      "HDRI"
#define OBJ       "OBJ"

bool	check_type(t_scene *scene, char **type)
{
	if (ft_strcmp(type[0], SPHERE))
		return (parse_sphere(scene, type));
	else if (ft_strcmp(type[0], LIGHT))
		return (parse_light(type, scene));
	else if (ft_strcmp(type[0], AMBIENT))
		return (parse_ambient_light(type, scene));
	else if (ft_strcmp(type[0], CAMERA))
		return (parse_camera(type, &scene->camera));
	else if (ft_strcmp(type[0], PLANE))
		return (parse_plane(type, scene));
	else if (BONUS && ft_strcmp(type[0], HDRI))
		return (parse_hdri(type, scene));
	else if (BONUS && ft_strcmp(type[0], OBJ))
		return (parse_obj(scene, type[1]));
	*error() = MAP_INV_TYPE;
	return (false);
}

void	init_scene_vec(t_scene *scene)
{
	vec_init(&scene->spheres, 1, sizeof(t_sphere));
	vec_init(&scene->inv_planes, 8, sizeof(t_inv_plane));
	vec_init(&scene->point_lights, 8, sizeof(t_point_light));
	vec_init(&scene->tri_meshes, 8, sizeof(t_tri_mesh));
}

bool	parse_map(t_scene *scene, const char *file)
{
	int		fd;
	char	*line;
	char	**split;
	bool	valid;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (false);
	init_scene_vec(scene);
	valid = true;
	while (valid)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (close(fd), true);
		if (line[0] != '#' && line[0] != '\n')
		{
			line = str_replace_char(line, '\t', ' ');
			line = str_replace_char(line, '\n', '\0');
			split = ft_split(line, ' ');
			if (split == NULL)
			{
				free(line);
				valid = false;
				break ;
			}
			if (check_type(scene, split) == false)
				valid = false;
			ft_split_free(split);
		}
		free(line);
	}
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		free(line);
	}
	close(fd);
	return (valid);
}
