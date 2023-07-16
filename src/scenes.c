/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/07/16 20:41:50 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <unistd.h>
# include <string.h>

void	init_scene_one(t_scene *s)
{
	t_material mat;
	
	s->nb_spheres = 1;
	s->spheres = malloc(sizeof(t_sphere) * s->nb_spheres);
	s->spheres[0] = create_sphere(vec3_create(0.0f, 1.0f, 0.0f), 1.0f);
	
	mat.albedo = vec3_create(1.0f, 0.1, 0.1);
	mat.smoothness = 1.0f;
	mat.specular = 0.05f;
	mat.emission_color = vec3_create(0.0f, 0.0f, 0.0f);
	mat.emission_intensity = 0.0f;

	s->spheres[0].material = mat;


	s->nb_planes = 10;
	s->planes = malloc(sizeof(t_plane) * s->nb_planes);


	// bottom plane
	s->planes[0].position = vec3_create(0.0f, 0.0f, 0.0f);
	s->planes[0].normal = vec3_create(0.0f, 1.0f, 0.0f);
	s->planes[0].width = 7.01f;
	s->planes[0].height = 4.01f;
	s->planes[0].material.albedo = vec3_create(0.4f, 0.4f, 0.4f);
	s->planes[0].material.emission_color = vec3_create(0.0f, 0.0f, 0.0f);
	s->planes[0].material.emission_intensity = 0.0f;
	s->planes[0].material.smoothness = 0.8f;
	s->planes[0].material.specular = 0.1f;

	// top plane
	s->planes[1].position = vec3_create(0.0f, 4.0f, 0.0f);
	s->planes[1].normal = vec3_create(0.0f, -1.0f, 0.0f);
	s->planes[1].width = 7.01f;
	s->planes[1].height = 4.01f;
	s->planes[1].material.albedo = vec3_create(0.7f, 0.7f, 0.7f);
	s->planes[1].material.emission_color = vec3_create(0.0f, 0.0f, 0.0f);
	s->planes[1].material.emission_intensity = 0.0f;
	s->planes[1].material.smoothness = 1.0f;
	s->planes[1].material.specular = 0.0f;


	// back
	// s->planes[4].position = vec3_create(0.0f, 1.5f, -1.5f);
	s->planes[2].position = vec3_create(0.0f, 2.0f, -2.0f);
	s->planes[2].normal = vec3_create(0.0f, 0.0f, 1.0f);
	s->planes[2].width = 7.01f;
	s->planes[2].height = 4.01f;
	s->planes[2].material.albedo = vec3_create(0.235f, 0.752f, 0.940f);
	s->planes[2].material.emission_color = vec3_create(0.0f, 0.0f, 0.0f);
	s->planes[2].material.emission_intensity = 0.0f;
	s->planes[2].material.smoothness = 0.0f;
	s->planes[2].material.specular = 0.0f;

	//left
	s->planes[3].position = vec3_create(-3.0f, 2.0f, 0.0f);
	s->planes[3].normal = vec3_create(1.0f, 0.0f, 0.0f);
	s->planes[3].width = 3.01f;
	s->planes[3].height = 4.01f;
	s->planes[3].material.albedo = vec3_create(1.0f, 1.0f, 1.0f);
	s->planes[3].material.emission_color = vec3_create(0.0f, 0.0f, 0.0f);
	s->planes[3].material.emission_intensity = 0.0f;
	s->planes[3].material.smoothness = 0.0f;
	s->planes[3].material.specular = 0.0f;

	// right
	s->planes[4].position = vec3_create(3.0f, 2.0f, 0.0f);
	s->planes[4].normal = vec3_create(-1.0f, 0.0f, 0.0f);
	s->planes[4].width = 3.01f;
	s->planes[4].height = 4.01f;
	s->planes[4].material.albedo = vec3_create(1.0f, 1.0f, 1.0f);
	s->planes[4].material.emission_color = vec3_create(0.0f, 0.0f, 0.0f);
	s->planes[4].material.emission_intensity = 0.0f;
	s->planes[4].material.smoothness = 0.0f;
	s->planes[4].material.specular = 0.0f;

	// front
	// s->planes[4].position = vec3_create(0.0f, 1.5f, -1.5f);
	s->planes[5].position = vec3_create(0.0f, 2.0f, 2.0f);
	s->planes[5].normal = vec3_create(0.0f, 0.0f, -1.0f);
	s->planes[5].width = 7.01f;
	s->planes[5].height = 4.01f;
	s->planes[5].material.albedo = vec3_create(0.235f, 0.752f, 0.940f);
	s->planes[5].material.emission_color = vec3_create(0.0f, 0.0f, 0.0f);
	s->planes[5].material.emission_intensity = 0.0f;
	s->planes[5].material.smoothness = 0.0f;
	s->planes[5].material.specular = 0.0f;

	//light

	s->planes[6].position = vec3_create(2.99f, 2.2f, 0.0f);
	s->planes[6].normal = vec3_create(-1.0f, 0.0f, 0.0f);
	s->planes[6].width = 3.5f;
	s->planes[6].height = 2.0f;
	s->planes[6].material.albedo = vec3_create(0.0f, 0.0f, 0.0f);
	s->planes[6].material.emission_color = vec3_create(1.0f, 1.0f, 1.0f);
	s->planes[6].material.emission_intensity = 8.0f;
	s->planes[6].material.smoothness = 0.0f;
	s->planes[6].material.specular = 0.0f;

	//left

	s->planes[7].position = vec3_create(-2.99f, 0.5f, 0.0f);
	s->planes[7].normal = vec3_create(1.0f, 0.0f, 0.0f);
	s->planes[7].width = 0.5f;
	s->planes[7].height = 0.5f;
	s->planes[7].material.albedo = vec3_create(0.0f, 0.0f, 0.0f);
	s->planes[7].material.emission_color = vec3_create(1.0f, 1.0f, 1.0f);
	s->planes[7].material.emission_intensity = 8.0f;
	s->planes[7].material.smoothness = 0.0f;
	s->planes[7].material.specular = 0.0f;

	s->planes[8].position = vec3_create(-2.99f, 1.5f, 0.0f);
	s->planes[8].normal = vec3_create(1.0f, 0.0f, 0.0f);
	s->planes[8].width = 0.5f;
	s->planes[8].height = 0.5f;
	s->planes[8].material.albedo = vec3_create(0.0f, 0.0f, 0.0f);
	s->planes[8].material.emission_color = vec3_create(1.0f, 1.0f, 1.0f);
	s->planes[8].material.emission_intensity = 8.0f;
	s->planes[8].material.smoothness = 0.0f;
	s->planes[8].material.specular = 0.0f;

	s->planes[9].position = vec3_create(-2.99f, 2.5f, 0.0f);
	s->planes[9].normal = vec3_create(1.0f, 0.0f, 0.0f);
	s->planes[9].width = 0.5f;
	s->planes[9].height = 0.5f;
	s->planes[9].material.albedo = vec3_create(0.0f, 0.0f, 0.0f);
	s->planes[9].material.emission_color = vec3_create(1.0f, 1.0f, 1.0f);
	s->planes[9].material.emission_intensity = 8.0f;
	s->planes[9].material.smoothness = 0.0f;
	s->planes[9].material.specular = 0.0f;
}