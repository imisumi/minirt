/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:26:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/16 15:29:58 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_hitinfo	sphere_intersection(t_ray ray, t_scene s, t_hitinfo hitinfo)
// {
// 	int	i;

// 	i = 0;
// 	// printf("sphere_intersec = %d\n", array_length(&s.spheres));
// 	while (i < array_length(&s.spheres))
// 	{
// 		t_vec3	offset_origin = vec3_sub(ray.origin, s.spheres[i].position);
	
// 		float	a = vec3_dot(ray.direction, ray.direction);
// 		float	b = 2.0f * vec3_dot(offset_origin, ray.direction);
// 		float	c = vec3_dot(offset_origin, offset_origin) - s.spheres[i].radius * s.spheres[i].radius;
	
// 		float	discriminant = b * b - 4 * a * c;
	
// 		if (discriminant >= 0.0f)
// 		{
// 			float	t = (-b - sqrtf(discriminant)) / (2.0f * a);
// 			if (t > 0.0f && t < hitinfo.distance)
// 			{
// 				// printf("sphere hit\n");
// 				hitinfo.hit = true;
// 				hitinfo.distance = t;
// 				hitinfo.position = vec3_add(ray.origin, vec3_mulf(ray.direction, t));
// 				hitinfo.normal = vec3_normalize(vec3_sub(hitinfo.position, s.spheres[i].position));
// 				hitinfo.material = s.spheres[i].material;
// 				// hitinfo.material = s.materials[s.spheres[i].material_index];
// 				// if (s.spheres[i].color == true)
// 				// 	hitinfo.material.color = s.spheres[i].col;
// 			}
// 		}
// 		i++;
// 	}
// 	return (hitinfo);
// }

// t_hitinfo	single_sphere_intersection(t_ray ray, t_sphere sphere, t_hitinfo hitinfo)
// {
// 	t_vec3	offset_origin = vec3_sub(ray.origin, sphere.position);

// 	float	a = vec3_dot(ray.direction, ray.direction);
// 	float	b = 2.0f * vec3_dot(offset_origin, ray.direction);
// 	float	c = vec3_dot(offset_origin, offset_origin) - sphere.radius * sphere.radius;

// 	float	discriminant = b * b - 4 * a * c;

// 	if (discriminant >= 0.0f)
// 	{
// 		float	t = (-b - sqrtf(discriminant)) / (2.0f * a);
// 		if (t > 0.0f && t < hitinfo.distance)
// 		{
// 			hitinfo.hit = true;
// 			hitinfo.distance = t;
// 			hitinfo.position = vec3_add(ray.origin, vec3_mulf(ray.direction, t));
// 			hitinfo.normal = vec3_normalize(vec3_sub(hitinfo.position, sphere.position));
// 			hitinfo.material = sphere.material;
// 		}
// 	}
// 	return (hitinfo);
// }

// // t_hitinfo	sphere_bvh_intersection(t_ray ray, t_scene s, t_hitinfo hitinfo, t_bvh_node *node)
// t_hitinfo	sphere_bvh_intersection(t_ray ray, t_sphere *spheres, t_hitinfo hitinfo, t_bvh_node *node)
// {
// 	float	t;

// 	t = aabb_intersection(ray, node->aabb);
// 	if (!t)
// 		return (hitinfo);
// 	if (node->is_leaf == true)
// 	{
// 		if (RENDER_BVH && t >= 0.0 && t < hitinfo.distance)
// 		{
// 			// hitinfo = render_bvh(ray, hitinfo, t, node);
// 			hitinfo.hit = true;
// 			hitinfo.material.color = vec3_new(0.5, 0.5, 0.5);
// 			hitinfo.distance = t;
// 		}
// 		else
// 		{
// 			for (int i = node->start; i < node->end; i++)
// 				hitinfo = single_sphere_intersection(ray, spheres[i], hitinfo);
// 		}
// 		return (hitinfo);
// 	}
// 	else
// 	{
// 		t_hitinfo left = sphere_bvh_intersection(ray, spheres, hitinfo, node->left);
// 		t_hitinfo right = sphere_bvh_intersection(ray, spheres, hitinfo, node->right);
// 		if (left.hit && !right.hit)
// 			return (left);
// 		else if (!left.hit && right.hit)
// 			return (right);
// 		else if (left.hit && right.hit)
// 		{
// 			if (left.distance < right.distance)
// 				return (left);
// 			else
// 				return (right);
// 		}
// 	}
// 	return (hitinfo);
// }



t_hitinfo	sphere_intersection_f(t_rayf ray, t_scene s, t_hitinfo hitinfo)
{
	int	i;

	i = 0;
	// printf("sphere_intersec = %d\n", array_length(&s.spheres));
	while (i < array_length(&s.spheres))
	{
		t_vec3f	offset_originf = ray[ORIGIN] - s.spheres[i].pos_f;
	
		float	a = vec3f_dot(ray[DIR], ray[DIR]);
		float	b = 2.0f * vec3f_dot(offset_originf, ray[DIR]);
		float	c = vec3f_dot(offset_originf, offset_originf) - s.spheres[i].radius * s.spheres[i].radius;
	
		float	discriminant = b * b - 4 * a * c;
	
		if (discriminant >= 0.0f)
		{
			float	t = (-b - sqrtf(discriminant)) / (2.0f * a);
			if (t > 0.0f && t < hitinfo.distance)
			{
				hitinfo.hit = true;
				hitinfo.distance = t;
				hitinfo.position = ray[ORIGIN] + (ray[DIR] * t);
				hitinfo.normal = vec3f_normalize(hitinfo.position - s.spheres[i].pos_f);
				hitinfo.material = s.spheres[i].material;
			}
		}
		i++;
	}
	return (hitinfo);
}

t_hitinfo	single_sphere_intersection_f(t_rayf ray, t_sphere sphere, t_hitinfo hitinfo)
{
	t_vec3f	offset_origin = ray[ORIGIN] - sphere.pos_f;

	float a = vec3f_dot(ray[DIR], ray[DIR]);
	float b = 2.0f * vec3f_dot(offset_origin, ray[DIR]);
	float c = vec3f_dot(offset_origin, offset_origin) - sphere.radius * sphere.radius;

	float	discriminant = b * b - 4 * a * c;

	bool inside = false;

	if (discriminant >= 0.0f)
	{
		float	t = (-b - sqrtf(discriminant)) / (2.0f * a);
		if (t < 0.0f)
		{
			inside = true;
			// t = -b + sqrtf(discriminant) / (2.0f * a);
			t = (-b + sqrtf(discriminant)) / (2.0f * a);
			// t = -b + sqrtf(discriminant);
		}
		
		if (t > EPSILON && t < hitinfo.distance)
		{
			hitinfo.hit = true;
			hitinfo.distance = t;
			hitinfo.material = sphere.material;
			hitinfo.position = ray[ORIGIN] + (ray[DIR] * t);
			// hitinfo.normal = vec3f_normalize(hitinfo.position - sphere.pos_f);
			hitinfo.normal = vec3f_normalize(hitinfo.position - sphere.pos_f) * (inside ? -1.0f : 1.0f);

			hitinfo.inside = inside;
		}
	}
	return (hitinfo);
}



t_hitinfo	sphere_bvh_intersection_f(t_rayf ray, t_sphere *spheres, t_hitinfo hitinfo, t_bvh_node *node)
{
	float	t;

	t = aabb_intersection_f(ray, node->aabb);
	if (!t)
		return (hitinfo);
	// printf("check\n");
	if (node->is_leaf == true)
	{
		if (RENDER_BVH && t >= 0.0 && t < hitinfo.distance)
		{
			// hitinfo = render_bvh(ray, hitinfo, t, node);
			hitinfo.hit = true;
			// hitinfo.material.color = vec3_new(0.5, 0.5, 0.5);
			hitinfo.material.color = (t_vec3f){0.5, 0.5, 0.5};
			hitinfo.distance = t;
		}
		else
		{
			for (int i = node->start; i < node->end; i++)
				hitinfo = single_sphere_intersection_f(ray, spheres[i], hitinfo);
		}
		return (hitinfo);
	}
	else
	{
		t_hitinfo left = sphere_bvh_intersection_f(ray, spheres, hitinfo, node->left);
		t_hitinfo right = sphere_bvh_intersection_f(ray, spheres, hitinfo, node->right);
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



// bool TestSphereTrace(in vec3 rayPos, in vec3 rayDir, inout SRayHitInfo info, in vec4 sphere)


// t_hitinfo	single_sphere_intersection_f(t_rayf ray, t_sphere sphere, t_hitinfo hitinfo)
// {
// 	// vec3 m = rayPos - sphere.xyz;
// 	t_vec3f	m = ray[ORIGIN] - sphere.pos_f;

// 	// float b = dot(m, rayDir);
// 	float b = vec3f_dot(m, ray[DIR]);

// 	// float c = dot(m, m) - sphere.w * sphere.w;
// 	float c = vec3f_dot(m, m) - sphere.radius * sphere.radius;

// 	if(c > 0.0 && b > 0.0)
// 		return hitinfo;
// 		// return false;

// 	float discr = b * b - c;

// 	if(discr < 0.0)
// 		return hitinfo;
// 		// return false;

//     bool fromInside = false;
// 	float dist = -b - sqrt(discr);
//     if (dist < 0.0f)
//     {
//         fromInside = true;
//         dist = -b + sqrt(discr);
//     }
    
// 	if (dist > EPSILON && dist < hitinfo.distance)
//     {
//         // info.fromInside = fromInside;
//         // info.dist = dist;        
//         // info.normal = normalize((rayPos+rayDir*dist) - sphere.xyz) * (fromInside ? -1.0f : 1.0f);
// 		hitinfo.hit = true;
// 		hitinfo.distance = dist;
// 		hitinfo.material = sphere.material;
// 		hitinfo.position = ray[ORIGIN] + (ray[DIR] * dist);
// 		hitinfo.normal = vec3f_normalize(hitinfo.position - sphere.pos_f) * (fromInside ? -1.0f : 1.0f);
// 		hitinfo.inside = fromInside;
// 	}

// 	return hitinfo;
// }