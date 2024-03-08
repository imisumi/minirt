/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:36:28 by ichiro            #+#    #+#             */
/*   Updated: 2024/03/08 03:46:31 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define TOP_CAP 1
#define BOTTOM_CAP 0

typedef struct s_cylinder_utils
{
	t_quat	q;
	t_vec3f	oo;
	t_vec3f	od;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	half_height;
	float	y;
	float	t1;
	float	t2;
}	t_cylinder_utils;

static void	init_cylinder_data(t_rayf ray, t_cylinder cy, t_cylinder_utils *u)
{
	u->q = quat_angle_axis_f(\
		angle_between_vec3(cy.normal, (t_vec3f){0.0f, 1.0f, 0.0f}), \
		create_rotation_axis(cy.normal, (t_vec3f){0.0f, 1.0f, 0.0f}));
	u->oo = quat_rotate_f(u->q, ray[ORIGIN] - cy.position);
	u->od = quat_rotate_f(u->q, ray[DIR]);
	u->a = u->od[X] * u->od[X] + u->od[Z] * u->od[Z];
	u->b = 2 * (u->oo[X] * u->od[X] + u->oo[Z] * u->od[Z]);
	u->c = u->oo[X] * u->oo[X] + u->oo[Z] * u->oo[Z] - cy.radius * cy.radius;
	u->discriminant = u->b * u->b - 4 * u->a * u->c;
}

//?		oo - offset origin
//?		od - offset direction
void	cylinder_shell_intersection(t_rayf ray, t_cylinder cy, \
	t_hitinfo *hinfo)
{
	t_cylinder_utils	u;

	init_cylinder_data(ray, cy, &u);
	if (u.discriminant > EPSILON)
	{
		u.t1 = (-u.b - sqrt(u.discriminant)) / (2 * u.a);
		u.t2 = (-u.b + sqrt(u.discriminant)) / (2 * u.a);
		if (u.t1 > u.t2)
			u.t1 = u.t2;
		if (u.t1 > EPSILON)
		{
			u.y = u.oo[Y] + (u.t1 * u.od[Y]);
			u.half_height = cy.height / 2;
			if (u.y > -u.half_height && u.y < u.half_height && \
				u.t1 < hinfo->distance)
			{
				hinfo->hit = true;
				hinfo->distance = u.t1;
				hinfo->position = ray[ORIGIN] + (ray[DIR] * u.t1);
				hinfo->normal = vec3f_normalize((t_vec3f){hinfo->position[X] \
				- cy.position[X], 0.0f, hinfo->position[Z] - cy.position[Z]});
				hinfo->material = cy.material;
			}
		}
	}
}

bool	cylinder_cap_intersection(t_rayf ray, t_cylinder *cy, \
	t_hitinfo *hitinfo, bool top_cap)
{
	float	t;
	float	demon;
	t_vec3f	offset_origin;
	t_vec3f	hit_point;
	t_vec3f	position;

	if (top_cap)
		position = cy->position + (cy->normal * (cy->height / 2));
	else
		position = cy->position - (cy->normal * (cy->height / 2));
	demon = vec3f_dot(cy->normal, ray[DIR]);
	if (fabs(demon) > EPSILON)
	{
		offset_origin = position - ray[ORIGIN];
		t = vec3f_dot(offset_origin, cy->normal) / demon;
		hit_point = ray[ORIGIN] + (ray[DIR] * t);
		if (t > EPSILON && t < hitinfo->distance && \
			vec3f_length(position - hit_point) < cy->radius)
		{
			apply_cap_hitinfo(hitinfo, hit_point, t, cy);
			if (!top_cap)
				hitinfo->normal = -cy->normal;
		}
	}
	return (hitinfo->hit);
}

bool	cylinder_intersection(t_rayf ray, t_scene *scene, t_hitinfo *hitinfo)
{
	int	i;

	i = 0;
	while (i < vec_length(&scene->cylinders))
	{
		cylinder_shell_intersection(ray, scene->cylinders[i], hitinfo);
		cylinder_cap_intersection(ray, &scene->cylinders[i], \
			hitinfo, TOP_CAP);
		cylinder_cap_intersection(ray, &scene->cylinders[i], \
			hitinfo, BOTTOM_CAP);
		i++;
	}
	return (hitinfo->hit);
}
