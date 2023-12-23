/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2023/12/22 23:56:02 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

const char *file = "assets/maps/owl.rt";
// const char *file = "assets/maps/map1.rt";
// const char *file = "assets/maps/lights.rt";

void	parse_test(t_scene *scene)
{
	vec_init(&scene->spheres, 1, sizeof(t_sphere));
	vec_init(&scene->inv_planes, 1, sizeof(t_inv_plane));
	vec_init(&scene->cylinders, 1, sizeof(t_cylinder));
	vec_init(&scene->point_lights, 1, sizeof(t_point_light));

	int fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(1);


	float coordinates[3];
	float value;
	int rgb[3];

	char *line;
	t_sphere sphere;
	t_inv_plane plane;
	t_cylinder cylinder;
	
	// sphere.material.color = (t_vec3){0.0f, 0.0f, 0.0f};
	
	scene->ambient_light = -1.0f;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[0] == 'p' && line[1] == 'l')
		{
			t_vec3 pos;
			t_vec3 normal;
			sscanf(line, "%*s %f,%f,%f %f,%f,%f %d,%d,%d",
							&pos.x, &pos.y, &pos.z,
							&normal.x, &normal.y, &normal.z,
							&rgb[0], &rgb[1], &rgb[2]);
			plane.material.color[R] = rgb[0] / 255.0f;
			plane.material.color[G] = rgb[1] / 255.0f;
			plane.material.color[B] = rgb[2] / 255.0f;

			plane.position[X] = pos.x;
			plane.position[Y] = pos.y;
			plane.position[Z] = pos.z;
			plane.position[W] = 0.0f;
			
			plane.normal[X] = normal.x;
			plane.normal[Y] = normal.y;
			plane.normal[Z] = normal.z;
			plane.normal[W] = 0.0f;

			// plane.material.emission = (t_vec3){0.0f, 0.0f, 0.0f};
			// plane.material.strength = 0.0f;
			array_push(&scene->inv_planes, &plane);
		}
		else if (line[0] == 's' && line[1] == 'p')
		{
			// postition, diameter, color
			t_vec3 pos;
			sscanf(line, "%*s %f,%f,%f %f %d,%d,%d",
							&pos.x, &pos.y, &pos.z,
							&value,
							&rgb[0], &rgb[1], &rgb[2]);
			sphere.material.color[R] = rgb[0] / 255.0f;
			sphere.material.color[G] = rgb[1] / 255.0f;
			sphere.material.color[B] = rgb[2] / 255.0f;
			sphere.pos_f[X] = pos.x;
			sphere.pos_f[Y] = pos.y;
			sphere.pos_f[Z] = pos.z;
			sphere.pos_f[W] = 0.0f;
			sphere.radius = value / 2.0f;
			array_push(&scene->spheres, &sphere);
		}
		else if (line[0] == 'A')
		{
			float intensity;
			sscanf(line, "%*s %f %d,%d,%d",
							&intensity,
							&rgb[0], &rgb[1], &rgb[2]);
			scene->ambient_light = intensity;
			scene->ambient_color[R] = rgb[0] / 255.0f;
			scene->ambient_color[G] = rgb[1] / 255.0f;
			scene->ambient_color[B] = rgb[2] / 255.0f;
		}
		else if (line[0] == 'L')
		{
			t_point_light light;
			float pos[3];
			sscanf(line, "%*s %f,%f,%f %f %d,%d,%d",
						&pos[X], &pos[Y], &pos[Z],
						&light.intensity,
						&rgb[0], &rgb[1], &rgb[2]);
			light.position[X] = pos[X];
			light.position[Y] = pos[Y];
			light.position[Z] = pos[Z];
			light.color[R] = rgb[0] / 255.0f;
			light.color[G] = rgb[1] / 255.0f;
			light.color[B] = rgb[2] / 255.0f;
			array_push(&scene->point_lights, &light);
			printf("light: %f,%f,%f %f %d,%d,%d\n",
						light.position[X], light.position[Y], light.position[Z],
						light.intensity,
						rgb[0], rgb[1], rgb[2]);
		}
	}
}

void	init_scene(t_scene *scene)
{
	parse_test(scene);
	return ;
}