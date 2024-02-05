/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/04 19:20:44 by imisumi-wsl      ###   ########.fr       */
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



// bool	parse_sphere(t_scene *scene, char **split)
// {
// 	// if (ft_split_count(split) != 4)
// 	// 	return (false);
// 	// printf("split count: %ld\n", ft_split_count(split));
// 	t_vec3f		center;
// 	t_sphere	sphere;
// 	if (parse_vec3(&sphere.pos_f, split[1]) == false)
// 	{
// 		print_error("sphere position");
// 		return (false);
// 	}
// 	// sphere.pos_f = center;

// 	// printf("%f, %f, %f\n", center[X], center[Y], center[Z]);
// 	printf("%f, %f, %f\n", sphere.pos_f[X], sphere.pos_f[Y], sphere.pos_f[Z]);
// }

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



// bool	parse_map(t_scene *scene, const char *file)
// {
// 	int		fd;
// 	char	*line;
// 	char	**split;
// 	bool	valid;

// 	fd = open(file, O_RDONLY);
// 	if (fd == -1)
// 		exit(1);
// 	init_scene_vec(scene);
// 	valid = true;
// 	while (valid)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 		{
// 			close(fd);
// 			return (false);
// 		}
// 		if (line[0] == '#' || line[0] == '\n')
// 			continue ;
// 		line = str_replace_char(line, '\t', ' ');
// 		line = str_replace_char(line, '\n', '\0');
// 		split = ft_split(line, ' ');
// 		free(line);
// 		if (split == NULL)
// 			continue ;
// 		if (check_type(scene, split) == false)
// 			valid = false;
// 		ft_split_free(split);
// 	}
// 	close(fd);
// 	return (valid);
// }

void	init_scene_vec(t_scene *scene)
{
	vec_init(&scene->spheres, 1, sizeof(t_sphere));
	vec_init(&scene->inv_planes, 8, sizeof(t_inv_plane));
	// vec_init(&scene->cylinders, 8, sizeof(t_cylinder));
	vec_init(&scene->point_lights, 8, sizeof(t_point_light));
	vec_init(&scene->tri_meshes, 8, sizeof(t_tri_mesh));
	// vec_clear(&scene->spheres);
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
				return (free(line), false);
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
