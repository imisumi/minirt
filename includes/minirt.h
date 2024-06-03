/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:31:38 by imisumi           #+#    #+#             */
/*   Updated: 2024/06/03 14:29:51 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <math.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <unistd.h>

# include <GLFW/glfw3.h>

# include "tinyexr.h"
# include "MLX42/MLX42.h"
# include "libft.h"
# include "lib3d.h"
# include "constants.h"
# include "struct.h"
# include "darray.h"

// *************************************************************************** /
//?                              bvh                                      
// *************************************************************************** /
//? bvh_mesh.c
bool		init_mesh_bvh(t_scene *scene);

//? bvh_sphere.c
t_bvh_node	*build_bvh_sphere_f(t_sphere *spheres, uint32_t start, \
	uint32_t end, uint32_t max_depth);

//? bvh_triangle.c
t_bvh_node	*bvh_triangle(t_vec3ui *tri_indexes, uint32_t start_end[2], \
	uint32_t max_dept, float *vertices);

//? bvh_utils.c
t_aabb		aabb_infinity(void);
void		bvh_starter_node(t_bvh_node *node, uint32_t start, uint32_t end);
t_aabb		merge_aabb_f(t_aabb a, t_aabb b);

// *************************************************************************** /
//?                              camera                                      
// *************************************************************************** /
//? camera.c
void		recalculat_ray_directions(t_data *d);
void		recalculate_view(t_data *d);
void		recalculated_projection(t_data *d);
t_vec3f		aa_update_dir(t_data *data, uint32_t *rng, uint32_t x, uint32_t y);

//? init.c
void		init_camera(t_camera *cam);

// *************************************************************************** /
//?                              color                                      
// *************************************************************************** /
//? color.c
uint32_t	ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint32_t	vec4f_to_color(t_vec4f c);
t_vec3f		texture(t_vec3f normal, t_hdri *hdri);

//? tone_map.c
t_vec4f		vec3f_tone_map(t_vec3f color);

// *************************************************************************** /
//?                              hook                                      
// *************************************************************************** /
//? hook.c
void		render_loop(void *param);

//? window_resize.c
void		resize_window(t_data *data);

// *************************************************************************** /
//?                              intersection                                  
// *************************************************************************** /
//? aabb.c
float		aabb_intersection_f(t_rayf ray, t_aabb aabb);

//? cylinder.c
bool		cylinder_intersection(t_rayf ray, t_scene *scene, \
	t_hitinfo *hitinfo);

//? cylinder_utils.c
float		angle_between_vec3(t_vec3f v1, t_vec3f v2);
t_vec3f		create_rotation_axis(t_vec3f normal, t_vec3f up);
void		apply_cap_hitinfo(t_hitinfo *hitinfo, t_vec3f hitpoint, \
	float distance, t_cylinder *cylinder);

//? mesh.c
t_hitinfo	mesh_bvh_intersection(t_rayf ray, t_hitinfo hitinfo, \
	t_bvh_node *node, t_scene *scene);

//? plane.c
bool		inv_plane_intersection_f(t_rayf ray, t_scene *s, \
	t_hitinfo *hitinfo);

//? sphere.c
bool		single_sphere_intersection_f(t_rayf ray, t_sphere *sphere, \
	t_hitinfo *hitinfo);
bool		sphere_intersection_f(t_rayf ray, t_scene *s, t_hitinfo *hitinfo);
t_hitinfo	sphere_bvh_intersection_f(t_rayf ray, t_sphere *spheres, \
				t_hitinfo hitinfo, t_bvh_node *node);

//? triangle.c
bool		single_triangle_intersection(t_rayf ray, t_hitinfo *hitinfo, \
	t_scene *scene, int mesh_face[2]);
bool		tri_mesh_intersection(t_rayf ray, t_scene *scene, \
	t_hitinfo *hitinfo);
t_hitinfo	triangle_bvh_intersection(t_rayf ray, t_mesh_utils u, \
	t_bvh_node *node, t_scene *scene);

//? triangle_utils.c
t_vec3f		get_tri_from_index(t_scene *scene, int index, int face, int id);
void		set_tri_hitinfo(t_hitinfo *hitinfo, t_rayf ray, \
	float t, const t_vec3f edge[2]);
void		set_point_and_edge(t_scene *scene, t_vec3f tri[3], \
	int mesh_face[2], t_vec3f edge[2]);

// *************************************************************************** /
//?                              key_input                                      
// *************************************************************************** /
//? input.c
void		handle_input(t_data *d);

// *************************************************************************** /
//?                              material                                      
// *************************************************************************** /
//TODO
t_vec3f		sample_texture(mlx_texture_t *tex, const t_barycentric *c, \
			const float *uvs);
void		set_tri_material(t_hitinfo *hitinfo, t_scene *s, \
			int m_f_idx[2], float uv[2]);

// *************************************************************************** /
//?                              parser                                      
// *************************************************************************** /
//? camera.c
bool		parse_camera(char **split, t_camera *camera);
//? cylinder.c
bool		parse_cylinder(char **split, t_scene *scene);
//? light.c
bool		parse_ambient_light(char **split, t_scene *scene);
bool		parse_light(char **split, t_scene *scene);
bool		parse_hdri(char **split, t_scene *scene);
//? material.c
t_material	default_material(void);
bool		parse_material(t_material *mat, char **split);
//? obj_utils.c
float		*copy_float_array(float *arr, uint32_t len);
bool		load_texture(mlx_texture_t **tex, const char *path);
//? obj.c
bool		parse_obj(t_scene *scene, const char *filename);
//? parser.c
bool		parse_map(t_scene *scene, const char *file);
//? plane.c
bool		parse_plane(char **split, t_scene *scene);
//? sphere.c
bool		parse_sphere(t_scene *scene, char **split);
//? string_to_float.c
bool		ft_stof(const char *s, float *f);
bool		ft_stoi(const char *s, int *i);
//? utils_2.c
bool		parse_vec3_normal(char *line, t_vec3f *vec);
bool		parse_8bit_color(char *line, t_vec3f *col);
bool		parse_vec3(char *line, t_vec3f *vec);
//? utils.c
char		*str_replace_char(char *str, char find, char replace);
void		ft_split_free(char **split);
size_t		ft_split_count(char **split);
bool		ft_strcmp(const char *s1, const char *s2);

// *************************************************************************** /
//?                              render                                      
// *************************************************************************** /
//? light.c
t_vec3f		omni_dir_light_f(t_rayf ray, t_scene *scene, t_hitinfo hitinfo);

//? ray.c
void		update_ray(t_rayf *ray, t_hitinfo *hitinfo, uint32_t *rngState, \
					t_vec3f *ray_color);

//? render_utils.c
t_vec3f		default_skyf(t_vec3f direction);
t_hitinfo	new_hitinfo(void);
float		fresnel_reflect_amount(float n1, float n2, float cosx, float f0);

//? render.c
void		*render(void *arg);

// *************************************************************************** /
//?                              screenshot                                    
// *************************************************************************** /
//? screenshot.c
void		screenshot(t_data *data);

// *************************************************************************** /
//?                              thread                                      
// *************************************************************************** /
//? thread.c
bool		render_zone(t_data *data);

// *************************************************************************** /
//? error.c
t_error		*error(void);
bool		print_error(const char *msg);
bool		print_warning(const char *msg);
void		exit_error(t_error type, const char *msg);

//? init.c
void		init_buffers(t_data *data);
bool		init_bvh(t_data *data);

//? mlx.c
bool		setup_mlx(t_data *data);
bool		run_mlx(t_data *data);

//? random.c
float		random_float(uint32_t *state);
uint32_t	get_rngstate(uint32_t width, uint32_t height, \
	uint32_t xy[2], uint32_t frame);
t_vec3f		random_directionf(uint32_t *state);

//? utils.c
void		put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, \
	uint32_t color);
double		time_delta(double prev_frame);
float		fov_radians(float fov);

#endif
