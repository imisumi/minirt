/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:26:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/16 18:26:53 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_sphere_utils
{
	t_vec3f	offset_origin;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	t;
	bool	inside;
}				t_sphere_utils;

static void	sphere_update_hit(t_hitinfo *hitinfo, t_sphere *sphere, \
	t_rayf ray, t_sphere_utils sp)
{
	t_vec3f	normal;

	hitinfo->hit = true;
	hitinfo->distance = sp.t;
	hitinfo->position = ray[ORIGIN] + (ray[DIR] * sp.t);
	normal = vec3f_normalize(hitinfo->position - sphere->pos_f);
	if (sp.inside)
		hitinfo->normal = -normal;
	else
		hitinfo->normal = normal;
	hitinfo->inside = sp.inside;
	hitinfo->material = sphere->material;
}

bool	single_sphere_intersection_f(t_rayf ray, t_sphere *sphere, \
	t_hitinfo *hitinfo)
{
	t_sphere_utils	sp;

	sp.offset_origin = ray[ORIGIN] - sphere->pos_f;
	sp.a = vec3f_dot(ray[DIR], ray[DIR]);
	sp.b = 2.0f * vec3f_dot(sp.offset_origin, ray[DIR]);
	sp.c = vec3f_dot(sp.offset_origin, sp.offset_origin) - \
		sphere->radius * sphere->radius;
	sp.discriminant = sp.b * sp.b - 4 * sp.a * sp.c;
	sp.inside = false;
	if (sp.discriminant >= 0.0f)
	{
		sp.t = (-sp.b - sqrtf(sp.discriminant)) / (2.0f * sp.a);
		if (sp.t < 0.0f)
		{
			sp.inside = true;
			sp.t = (-sp.b + sqrtf(sp.discriminant)) / (2.0f * sp.a);
		}
		if (sp.t > EPSILON && sp.t < hitinfo->distance)
			sphere_update_hit(hitinfo, sphere, ray, sp);
	}
	return (hitinfo->hit);
}

bool	sphere_intersection_f(t_rayf ray, t_scene *s, t_hitinfo *hitinfo)
{
	int	i;

	i = 0;
	while (i < vec_length(&s->spheres))
	{
		single_sphere_intersection_f(ray, &s->spheres[i], hitinfo);
		i++;
	}
	return (hitinfo->hit);
}

static t_hitinfo	sphere_intersect_range(t_rayf ray, t_sphere *spheres, \
	t_hitinfo *hitinfo, uint32_t range[2])
{
	uint32_t	start;
	uint32_t	end;

	start = range[0];
	end = range[1];
	while (start < end)
	{
		single_sphere_intersection_f(ray, &spheres[start], hitinfo);
		start++;
	}
	return (*hitinfo);
}

t_hitinfo	sphere_bvh_intersection_f(t_rayf ray, t_sphere *spheres, \
				t_hitinfo hitinfo, t_bvh_node *node)
{
	t_hitinfo	left;
	t_hitinfo	right;

	if (!aabb_intersection_f(ray, node->aabb))
		return (hitinfo);
	if (node->is_leaf == true)
	{
		return (sphere_intersect_range(ray, spheres, &hitinfo, \
					(uint32_t[2]){node->start, node->end}));
	}
	else
	{
		left = sphere_bvh_intersection_f(ray, spheres, hitinfo, node->left);
		right = sphere_bvh_intersection_f(ray, spheres, hitinfo, node->right);
		if (left.hit && (!right.hit || left.distance < right.distance))
			return (left);
		else if (right.hit)
			return (right);
	}
	return (hitinfo);
}
