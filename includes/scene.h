/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/07/15 17:26:16 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "../lib/ft_math/includes/math.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_material
{
	t_vec3	albedo;
	float	roughness;
	float	smoothness;
	t_vec3	emission_color;
	float	emission_intensity;
}	t_material;

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	normal;
	float	height;
	float	diameter;
	float	radius;
}	t_cylinder;

typedef struct s_sphere
{
	t_vec3		center;
	float		radius;
	t_material	material;
}	t_sphere;

typedef struct s_inv_plane
{
	t_vec3	position;
	t_vec3	normal;
}	t_inv_plane;

typedef struct s_plane
{
	t_vec3		position;
	t_vec3		normal;
	float		width;
	float		height;
	t_material	material;
}	t_plane;

typedef struct s_obj_hit
{
	bool		hit;
	t_vec3		position;
	t_vec3		normal;
	float		hit_distance;
	t_material	material;
}	t_obj_hit;

typedef struct s_camera
{
	t_mat4	projection;
	t_mat4	inv_projection;
	t_mat4	view;
	t_mat4	inv_view;

	float	vertical_fov;
	float	aspectRatio;
	float	zNear;
	float	zFar;

	t_vec3	position;
	t_vec3	direction;

	t_vec2	mouse_delta;
	t_vec2	mouse_pos;
	bool	mouse_lock;
	t_vec2	prev_mouse_pos;

	t_vec3	*ray_dir;
}	t_camera;

typedef struct s_scene
{
	t_sphere	*spheres;
	uint32_t	nb_spheres;

	t_inv_plane	inv_planes[10];
	uint32_t	nb_inv_planes;

	t_plane		*planes;
	uint32_t	nb_planes;

	t_cylinder	cylinders[10];
	uint32_t	nb_cylinders;

	t_camera	camera;
}	t_scene;

typedef struct s_mlx
{
	t_scene		scene;
	mlx_t		*mlx;
	mlx_image_t	*img;
}				t_mlx;

#endif