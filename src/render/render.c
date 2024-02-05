/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:32:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/05 03:00:49 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	object_intersection(t_rayf ray, t_scene *scene, t_hitinfo *hitinfo)
{
	hitinfo->distance = INFINITY;
	hitinfo->hit = false;
	hitinfo->inside = false;
	if (USE_BVH && vec_length(&scene->spheres) > 0)
	{
		*hitinfo = sphere_bvh_intersection_f(ray, scene->spheres, *hitinfo, \
			scene->bvh_spheres_f);
	}
	else
		sphere_intersection_f(ray, scene, hitinfo);
	inv_plane_intersection_f(ray, scene, hitinfo);
	if (USE_BVH && scene->num_tri_meshes > 0)
	{
		*hitinfo = mesh_bvh_intersection(ray, *hitinfo, scene->bvh_meshes, \
			scene);
	}
	else
		tri_mesh_intersection(ray, scene, hitinfo);
	return (hitinfo->hit);
}

typedef struct s_ray_utils
{
	uint32_t	bounce;
	t_vec3f		incomming_light;
	t_vec3f		ray_color;
	t_vec3f		emitted_light;
	t_vec3f		ray[2];
	t_hitinfo	hitinfo;
	float		p;
}	t_ray_utils;

t_vec4f	apply_enviorment(t_rayf ray, t_scene *scene, t_ray_utils *u)
{
	t_vec3f	sky;

	if (!RENDER_SKYBOX && u->bounce == 0)
		return ((t_vec4f){0.0f, 0.0f, 0.0f, 1.0f});
	if (BONUS && scene->hdri.rgba != NULL)
		sky = texture(ray[DIR], scene->hdri);
	else if (scene->ambient_light > 0.0f)
		sky = scene->ambient_color * scene->ambient_light;
	else
		sky = (t_vec3f){0.0f, 0.0f, 0.0f, 0.0f};
	u->incomming_light += (u->ray_color * sky);
	return ((t_vec4f){u->incomming_light[X], u->incomming_light[Y], \
		u->incomming_light[Z], 1.0f});
}

t_vec4f	per_pixel(t_vec3f dir, t_scene *scene, uint32_t *rngState)
{
	t_ray_utils	u;

	ft_memset(&u, 0, sizeof(t_ray_utils));
	u.ray_color = (t_vec3f){1.0f, 1.0f, 1.0f, 0.0f};
	u.ray[ORIGIN] = scene->camera.position;
	u.ray[DIR] = dir;
	while (u.bounce <= MAX_BOUNCES)
	{
		if (object_intersection(u.ray, scene, &u.hitinfo) == false)
			return (apply_enviorment(u.ray, scene, &u));
		if (u.hitinfo.inside)
			u.ray_color *= vec3f_exp(-u.hitinfo.material.refraction_color * \
				u.hitinfo.distance);
		update_ray(&u.ray, &u.hitinfo, rngState, &u.ray_color);
		u.p = fmaxf(fmaxf(u.ray_color[X], u.ray_color[Y]), u.ray_color[Z]);
		if (randomFloat(rngState) > u.p)
			break ;
		u.ray_color *= (1.0f / u.p);
		u.emitted_light = omni_dir_light_f(u.ray, scene, u.hitinfo);
		u.emitted_light += u.hitinfo.material.color * \
			u.hitinfo.material.emission_strength;
		u.incomming_light += (u.ray_color * u.emitted_light);
		u.bounce++;
	}
	return (vec3f_to_vec4f(u.incomming_light, 1.0f));
}

void	render_pixel(t_data *data, uint32_t x, uint32_t y)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	hex_color;
	t_vec4f		avg_color;

	avg_color = data->utils.accumulated_data[x + y * data->utils.width];
	avg_color /= (float)data->utils.accumulated_frames;
	avg_color = vec3f_tone_map(avg_color);
	avg_color = vec4f_clamp(avg_color, 0.0f, 1.0f);
	hex_color = vec4f_to_color(avg_color);
	i = 0;
	while (i < PIXEL_SIZE)
	{
		j = 0;
		while (j < PIXEL_SIZE)
		{
			put_pixel(data->img, (x * PIXEL_SIZE) + i, \
				((data->utils.height - y - 1) * PIXEL_SIZE) + j, \
				hex_color);
			j++;
		}
		i++;
	}
}

typedef struct s_render_utils
{
	t_data		*data;
	uint32_t	x;
	uint32_t	y;
	uint32_t	rng_state;
	t_vec4f		color;
	t_vec3f		dir;
}	t_render_utils;

void	*render(void *arg)
{
	const t_thread	*thread = arg;
	t_render_utils	u;

	u.data = thread->data;
	u.y = thread->y_start;
	while (u.y < thread->y_end)
	{
		u.x = thread->x_start;
		while (u.x < thread->x_end)
		{
			u.rng_state = get_rngstate(u.data->utils.width, \
				u.data->utils.height, u.x, u.y);
			u.dir = u.data->scene.camera.ray_dir[u.x + u.y * \
				u.data->utils.width];
			if (AA)
				u.dir = aa_update_dir(u.data, &u.rng_state, u.x, u.y);
			u.color = per_pixel(u.dir, &u.data->scene, &u.rng_state);
			u.data->utils.accumulated_data[u.x + u.y * u.data->utils.width] \
				+= u.color;
			render_pixel(u.data, u.x, u.y);
			u.x++;
		}
		u.y++;
	}
	return (NULL);
}

//? with rayprobability idk if needed
// t_vec4f	per_pixel(t_vec3f dir, t_scene *scene, uint32_t *rngState)
