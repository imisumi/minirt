/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 00:41:53 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/22 20:27:14 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "MLX42/MLX42.h"
# include "lib3d.h"

# include <pthread.h>

typedef struct s_data t_data;
typedef struct s_bvh_node t_bvh_node;

typedef enum error
{
	NO_ERROR = 0,
	STOF,
	VEC3_NAN,
	VEC3_INF,
	MLX_INIT,
	MLX_IMG,
	MLX_IMG_TO_WIN,
	MAP_INV_TYPE,
	MALLOC_BVH,
	ERROR_COUNT
}	t_error;

// typedef enum error
// {
// 	NO_ERROR = 0,
// 	STOF,
// 	VEC3_NAN,
// 	VEC3_INF,
// 	ERROR_COUNT
// }	t_error;

typedef struct
{
	t_vec3 position; // Position of the light source
	t_vec3 color;    // Color of the light
	float intensity; // Intensity of the light

	// t_vec3f	position_f;
	// t_vec3f	color_f;
}	t_omnidirectional_light;

typedef struct t_thread
{
	pthread_t	tid;

	uint32_t	x_start;
	uint32_t	x_end;
	uint32_t	y_start;
	uint32_t	y_end;

	uint32_t	index;
	
	t_data		*data;
}	t_thread;

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

	t_vec3f	position;
	t_vec3f	dir;

	t_vec2f	mouse_delta;
	t_vec2f	mouse_pos;
	bool	mouse_lock;
	t_vec2f	prev_mouse_pos;

	t_vec3f	*ray_dir;
	t_vec4f	*ray_target;
}	t_camera;

typedef struct s_render_block
{
	int	x_start;
	int	x_end;
	int	y_start;
	int	y_end;
}	t_render_block;

typedef struct s_utils
{
	pthread_t			threads[THREADS];
	t_render_block		blocks[THREADS];
	pthread_mutex_t		mutex;
	uint32_t			accumulated_frames;

	t_vec4f				*accumulated_data;
	double				prev_frame;

	uint32_t			width;
	uint32_t			height;
}				t_utils;

typedef struct s_material
{
	t_vec3f		color;
	float		roughness;
	
	float		specular;
	t_vec3f		specular_color;
	// t_vec3		emission;

	float		ior;
	float		refraction;
	float		refraction_roughness;
	t_vec3f		refraction_color;
	
	float		emission_strength;
	t_vec3f		emission_color;
}	t_material;


typedef struct s_aabb
{
	t_vec3	min;
	t_vec3	max;

	t_vec3f	min_f;
	t_vec3f	max_f;
}	t_aabb;

typedef uint32_t	t_vert_indices[3];
typedef uint32_t	t_vec3ui[3];

typedef struct t_tri
{
	// t_vec3f			v[3];
	
	// t_vec3f			vt[3];
	// t_vec3f			vn;
	uint32_t		v_idx[3];

	
	// t_material		material;
}	t_tri;

typedef struct s_tri_mesh
{
	t_tri			*tris;
	// float			*vertices;

	// t_vec3ui		*v_idx;
	// t_vec3ui		*vn_idx;
	// t_vec3ui		*vt_idx;
	// float			*vertices;
	// float			*normals;
	t_aabb			aabb;
	uint32_t		num_faces;
	t_material		material;
	t_bvh_node		*bvh;
}	t_tri_mesh;

typedef struct s_sphere
{
	t_vec3		position;
	t_vec3f		pos_f;
	// t_vec3f		position;
	
	float		radius;
	t_material	material;
}	t_sphere;

typedef struct s_inv_plane
{
	// t_vec3		position;
	// t_vec3		normal;
	t_vec3f		position;
	t_vec3f		normal;
	t_material	material;
}	t_inv_plane;

typedef struct s_cylinder
{
	t_vec3		position;
	t_vec3		normal;
	float		radius;
	float		height;
	t_material	material;
}	t_cylinder;

// typedef struct s_tri_mesh
// {
// 	t_vec3f		*vertices;
// 	t_vec3f		*normals;
// 	t_vec2f		*uvs;
// 	t_vec3f		*colors;
// 	t_vec3f		*vert_indices;

// }	t_tri_mesh;

typedef struct s_point_light
{
	t_vec3f		position;
	t_vec3f		color;
	float		intensity;
}	t_point_light;

typedef struct s_hdri
{
	float	*rgba;
	int		width;
	int		height;
}	t_hdri;

typedef struct s_scene
{
	// t_ambient	ambient;

	float		*vertices;
	t_sphere	*spheres;
	// t_bvh_node	*bvh_spheres;
	t_bvh_node	*bvh_spheres_f;
	t_bvh_node	*bvh_meshes;

	t_inv_plane	*inv_planes;

	t_cylinder	*cylinders;

	t_tri_mesh	*tri_meshes;
	uint32_t	num_tri_meshes;

	t_point_light	*point_lights;

	// float			*hdri;
	// int				hdri_width;
	// int				hdri_height;
	t_hdri			hdri;

	// t_plane		*planes;
	// t_material	*materials;
	float	ambient_light;
	// t_vec3		ambient_color;
	t_vec3f		ambient_color;
	t_camera	camera;
}				t_scene;

typedef struct s_data
{
	// pthread_mutex_t	mutex;
	t_utils			utils;
	t_scene			scene;
	mlx_t			*mlx;
	mlx_image_t		*img;
}				t_data;

// typedef enum e_type
// {
// 	SPHERE = 0
// }	t_type;

// typedef struct s_aabb
// {
// 	t_vec3	min;
// 	t_vec3	max;

// 	t_vec3f	min_f;
// 	t_vec3f	max_f;
// }	t_aabb;

typedef struct s_bvh_node
{
	// void	*object;
	// t_type	type;
	// t_sphere	sphere;
	uint32_t	start;
	uint32_t	end;
	t_aabb aabb;
	struct s_bvh_node *left;
	struct s_bvh_node *right;
	bool is_leaf;
}	t_bvh_node;

typedef struct s_hitinfo
{
	bool	hit;
	float	distance;
	// t_vec3	position;
	// t_vec3	normal;
	t_vec3f	position;
	t_vec3f	normal;
	bool	inside;

	t_material	material;
	// t_vec3		color;
	
}	t_hitinfo;

#endif
