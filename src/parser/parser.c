/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/05 21:14:23 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define AMBIENT   "A"
#define CAMERA    "C"
#define LIGHT     "L"
#define SPHERE    "sp"
#define PLANE     "pl"
#define CYLINDER  "cy"

t_error	*error(void)
{
	static t_error	error;

	return (&error);
}



void	print_error(const char *msg)
{
	const char	*error_strings[ERROR_COUNT] = {
	[NO_ERROR] = "NO_ERROR",
	[STOF] = "String to float error",
	[VEC3_NAN] = "Vec3 is not a number",
	[VEC3_INF] = "Vec3 is infinite",
	};

	if (msg && *error() == NO_ERROR)
		printf("%s\n", msg);
	else
		printf("%s: ", msg);
	if (*error() != NO_ERROR)
		printf("%s\n", error_strings[*error()]);
}

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
	// printf("--------------\n");
	return (true);
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
	vec_init(&scene->inv_planes, 1, sizeof(t_inv_plane));
	vec_init(&scene->cylinders, 1, sizeof(t_cylinder));
	vec_init(&scene->point_lights, 1, sizeof(t_point_light));
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
			return (close(fd), false);
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
	close(fd);
	return (valid);
}