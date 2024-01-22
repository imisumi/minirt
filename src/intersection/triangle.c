/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:26:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/22 01:26:26 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// bool	single_triangle_intersection(t_rayf ray, t_tri_mesh *mesh, uint32_t i, t_hitinfo *hitinfo)
// {
// 	// mesh->tris->tri[0] = (t_vec3f){0.0f, 0.0f, 0.0f};
// 	// mesh->tris->tri[1] = (t_vec3f){0.0f, 1.0f, 0.0f};
// 	// mesh->tris->tri[2] = (t_vec3f){1.0f, 0.0f, 0.0f};
	
	
// 	t_vec3f edge_ab = mesh->tris[i].v[1] - mesh->tris[i].v[0];
// 	t_vec3f edge_ac = mesh->tris[i].v[2] - mesh->tris[i].v[0];

// 	//TODO use normal from obj file
// 	// t_vec3f normal = vec3f_cross(edge_ab, edge_ac);
// 	t_vec3f normal = mesh->tris[i].vn;
// 	t_vec3f ao = ray[ORIGIN] - mesh->tris[i].v[0];
// 	t_vec3f dao = vec3f_cross(ray[DIR], ao);

// 	float determinant = -vec3f_dot(normal, ray[DIR]);
// 	float inv_det = 1.0f / determinant;

// 	float dst = vec3f_dot(normal, ao) * inv_det;
// 	float u = vec3f_dot(dao, edge_ac) * inv_det;
// 	float v = -vec3f_dot(dao, edge_ab) * inv_det;
// 	float w = 1.0f - u - v;

// 	if (u < 0 || u > 1)
// 		return (false);
// 	if (v < 0 || u + v > 1)
// 		return (false);

// 	if (w < 0)
// 		return (false);
		
// 	if (dst > EPSILON && dst < hitinfo->distance && determinant > EPSILON)
// 	{
// 		hitinfo->hit = true;
// 		// hitinfo->hit = true;
// 		hitinfo->position = ray[ORIGIN] + ray[DIR] * dst;
// 		hitinfo->normal = normal;
// 		hitinfo->distance = dst;
// 		hitinfo->material = mesh->material;
// 		hitinfo->material.color = (t_vec3f){1.0f, 0.0f, 0.0f};
// 	}
// 	return (true);
// }

//! working
// t_hitinfo triangle_intersection(t_ray ray, t_hitinfo obj_hit, t_tri tri)
// bool	single_triangle_intersection(t_rayf ray, t_tri_mesh *mesh, uint32_t i, t_hitinfo *hitinfo)
// {
// 	// if (vec3f_dot(ray[DIR], mesh->tris[i].vn) > 0)
// 	// 	return (false);
// 	t_vec3f e1 = mesh->tris[i].v[1] - mesh->tris[i].v[0];
// 	t_vec3f e2 = mesh->tris[i].v[2] - mesh->tris[i].v[0];
// 	// t_vec3f n = vec3_cross(e1, e2);
// 	t_vec3f h = vec3f_cross(ray[DIR], e2);
// 	float a = vec3f_dot(e1, h);

// 	if (a > -EPSILON && a < EPSILON)
// 		return (false);

// 	float f = 1.0f / a;
// 	t_vec3f s = ray[ORIGIN] - mesh->tris[i].v[0];
// 	float u = f * vec3f_dot(s, h);

// 	if (u < 0.0f || u > 1.0f)
// 		return (false);

// 	t_vec3f q = vec3f_cross(s, e1);
// 	float v = f * vec3f_dot(ray[DIR], q);

// 	if (v < 0.0f || u + v > 1.0f)
// 		return (false);
	
// 	float t = f * vec3f_dot(e2, q);

// 	float w = 1.0f - u - v;
	
// 	if (t > EPSILON && t < hitinfo->distance)
// 	{
// 		hitinfo->hit = true;
// 		hitinfo->position = ray[ORIGIN] + ray[DIR] * t;
// 		hitinfo->normal = vec3f_normalize(vec3f_cross(e1, e2));
// 		// hitinfo->normal = vec3f_normalize(vec3f_cross(e1, e2));
// 		hitinfo->distance = t;
// 		// hitinfo->material = mesh->material;
// 		hitinfo->material = mesh->tris[i].material;
// 		// hitinfo->material.color = (t_vec3f){1.0f, 0.0f, 0.0f};
// 		return (true);
// 	}
// 	return (false);
// }

// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
bool	single_triangle_intersection(t_rayf ray, t_tri_mesh *mesh, uint32_t i, t_hitinfo *hitinfo)
{
	t_vec3f e1 = mesh->tris[i].v[1] - mesh->tris[i].v[0];
	t_vec3f e2 = mesh->tris[i].v[2] - mesh->tris[i].v[0];
	
	t_vec3f ray_cross_e2 = vec3f_cross(ray[DIR], e2);

	float det = vec3f_dot(e1, ray_cross_e2);

	if (BACK_FACE_CULLING && det < 0)
		return (false);
	else if (det > -EPSILON && det < EPSILON)
		return (false); // This ray is parallel to this triangle.

	float inv_det = 1.0f / det;
	t_vec3f s = ray[ORIGIN] - mesh->tris[i].v[0];
	float u = inv_det * vec3f_dot(s, ray_cross_e2);

	if (u < 0.0f || u > 1.0f)
		return (false);

	t_vec3f s_cross_e1 = vec3f_cross(s, e1);
	float v = inv_det * vec3f_dot(ray[DIR], s_cross_e1);

	if (v < 0.0f || u + v > 1.0f)
		return (false);

	// if (u < 0 || u > 1 || v < 0 || u + v > 1)
	// 	return (false);
	// if ((u < 0) | (u > 1) | (v < 0) | (u + v > 1))
	// 	return (false);

	// At this stage we can compute t to find out where the intersection point is on the line.
	float t = inv_det * vec3f_dot(e2, s_cross_e1);
	
	if (t > EPSILON && t < hitinfo->distance)
	{
		hitinfo->hit = true;
		hitinfo->position = ray[ORIGIN] + ray[DIR] * t;
		hitinfo->normal = vec3f_normalize(vec3f_cross(e1, e2));
		// hitinfo->normal = vec3f_normalize(vec3f_cross(e1, e2));
		hitinfo->distance = t;
		hitinfo->material = mesh->material;
		hitinfo->material = mesh->tris[i].material;
		// hitinfo->material.color = (t_vec3f){1.0f, 0.0f, 0.0f};
		return (true);
	}
	return (false);
}

bool triangle_intersection(t_rayf ray, t_scene *scene, uint32_t index, t_hitinfo *obj_hit)
{
	int	i;

	i = 0;
	while (i < scene->tri_meshes[index].num_faces)
	{
		// if (i == 2)
		// 	break ;
		single_triangle_intersection(ray, &scene->tri_meshes[index], i, obj_hit);
		// t_tri tri = scene->tri_meshes[index].tris[i];
		// printf("%f %f %f\n", tri.vertices[0], tri.vertices[1], tri.vertices[2]);
		i++;
	}
	// exit(0);
	return (true);
}

bool	tri_mesh_intersection(t_rayf ray, t_scene *scene, t_hitinfo *obj_hit)
{
	int	i;

	i = 0;
	while (i < vec_length(&scene->tri_meshes))
	{
		triangle_intersection(ray, scene, i, obj_hit);
		// break ;
		i++;
	}
	return (true);
}

// t_hitinfo triangle_intersection(t_ray ray, t_hitinfo obj_hit, t_tri tri)
// {
// 	t_vec3 e1 = vec3_sub(tri.b, tri.a); // tri.b - tri.a
// 	t_vec3 e2 = vec3_sub(tri.c, tri.a); // tri.a - tri.c
// 	// t_vec3 n = vec3_cross(e1, e2);
// 	t_vec3 h = vec3_cross(ray.direction, e2);
// 	float a = vec3_dot(e1, h);

// 	if (a > -EPSILON && a < EPSILON)
// 		return (obj_hit);

// 	float f = 1.0f / a;
// 	t_vec3 s = vec3_sub(ray.origin, tri.a);
// 	float u = f * vec3_dot(s, h);

// 	if (u < 0.0f || u > 1.0f)
// 		return (obj_hit);

// 	t_vec3 q = vec3_cross(s, e1);
// 	float v = f * vec3_dot(ray.direction, q);

// 	if (v < 0.0f || u + v > 1.0f)
// 		return (obj_hit);
	
// 	float t = f * vec3_dot(e2, q);

// 	float w = 1.0f - u - v;
	
// 	if (t > EPSILON && t < obj_hit.distance)
// 	{

// 		int textureWidth = uv_tex->width;
// 		int textureHeight = uv_tex->height;
		
// 		// Barycentric Interpolation for texture coordinates
// 		float texU = (1 - u - v) * tri.uv_a.x + u * tri.uv_b.x + v * tri.uv_c.x;
// 		float texV = (1 - u - v) * tri.uv_a.y + u * tri.uv_b.y + v * tri.uv_c.y;
		
// 		// Wrap texture coordinates to [0, 1] (or tile the texture)
// 		// texU = fmod(texU, 1.0f);
// 		// texV = fmod(texV, 1.0f);
// 		texU = fmod(texU + 1.0f, 1.0f);
// 		texV = fmod(texV + 1.0f, 1.0f);

// 		if (texU < 0)
// 		    texU += 1.0f;
// 		if (texV < 0)
// 		    texV += 1.0f;
		
// 		int x = (int)(texU * textureWidth);
// 		int y = (int)(texV * textureHeight);
		
// 		int pixelIndex = (y * textureWidth + x) * 4; // 4 channels (R, G, B, A) per pixel
		
// 		uint8_t r = uv_tex->pixels[pixelIndex];
// 		uint8_t g = uv_tex->pixels[pixelIndex + 1];
// 		uint8_t b = uv_tex->pixels[pixelIndex + 2];




// 		obj_hit.hit = true;
// 		obj_hit.distance = t;
// 		obj_hit.position = vec3_add(ray.origin, vec3_mulf(ray.direction, t));
// 		obj_hit.normal = vec3_normalize(vec3_cross(e1, e2));
// 		obj_hit.material.color = tri.material.color;

// 		obj_hit.material.color = vec3_new(r / 255.0f, g / 255.0f, b / 255.0f);
// 	}
	
//     return obj_hit;
// }


t_hitinfo	triangle_bvh_intersection(t_rayf ray, t_tri_mesh meshes, t_hitinfo hitinfo, t_bvh_node *node)
{
	float	t;

	t = aabb_intersection_f(ray, node->aabb);
	if (!t)
		return (hitinfo);
	if (node->is_leaf == true)
	{
		if (RENDER_BVH && t > EPSILON && t < hitinfo.distance)
		{
			hitinfo.hit = true;
			hitinfo.material.color = (t_vec3f){1, 0, 1};
			hitinfo.distance = t;
			return (hitinfo);
		}
		for (int i = node->start; i < node->end; i++)
			single_triangle_intersection(ray, &meshes, i, &hitinfo);
		return (hitinfo);
	}
	else
	{
		t_hitinfo left = triangle_bvh_intersection(ray, meshes, hitinfo, node->left);
		t_hitinfo right = triangle_bvh_intersection(ray, meshes, hitinfo, node->right);
		if (left.hit && !right.hit)
			return (left);
		else if (!left.hit && right.hit)
			return (right);
		else if (left.hit && right.hit)
		{
			if (left.distance < right.distance)
				return (left);
			else
				return (right);
		}
	}
	return (hitinfo);
}

t_hitinfo	mesh_bvh_intersection(t_rayf ray, t_tri_mesh *meshes, t_hitinfo hitinfo, t_bvh_node *node)
{
	float	t;

	t = aabb_intersection_f(ray, node->aabb);
	if (!t)
		return (hitinfo);
	if (node->is_leaf == true)
	{
		for (int i = node->start; i < node->end; i++)
			hitinfo = triangle_bvh_intersection(ray, meshes[i], hitinfo, meshes[i].bvh);
		return (hitinfo);
	}
	else
	{
		t_hitinfo left = mesh_bvh_intersection(ray, meshes, hitinfo, node->left);
		t_hitinfo right = mesh_bvh_intersection(ray, meshes, hitinfo, node->right);
		if (left.hit && !right.hit)
			return (left);
		else if (!left.hit && right.hit)
			return (right);
		else if (left.hit && right.hit)
		{
			if (left.distance < right.distance)
				return (left);
			else
				return (right);
		}
	}
	return (hitinfo);
}