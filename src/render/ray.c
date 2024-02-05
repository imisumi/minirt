/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:32:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/05 01:57:53 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	get_specular_chance(t_vec3f ray_dir, t_hitinfo *hitinfo)
{
	float	specular_chance;

	if (hitinfo->inside)
	{
		specular_chance = fresnel_reflect_amount(hitinfo->material.ior, 1.0f, \
			-vec3f_dot(ray_dir, hitinfo->normal), hitinfo->material.specular);
	}
	else
	{
		specular_chance = fresnel_reflect_amount(1.0f, hitinfo->material.ior, \
			-vec3f_dot(ray_dir, hitinfo->normal), hitinfo->material.specular);
	}
	return (specular_chance);
}

void	calc_ray(t_rayf *ray, t_hitinfo *hitinfo, float do_specular, \
			float do_refraction, uint32_t *rngState)
{
	t_vec3f			refract_dir;
	float			refractive_index;
	const t_vec3f	diffuse_dir = vec3f_normalize(hitinfo->normal + \
		random_directionf(rngState));
	const t_vec3f	specular_dir = vec3f_lerp(vec3f_reflect(ray[0][DIR], \
		hitinfo->normal), diffuse_dir, hitinfo->material.roughness * \
		hitinfo->material.roughness);

	if (do_refraction == 1.0f)
		ray[0][ORIGIN] = hitinfo->position - (hitinfo->normal * EPSILON);
	else
		ray[0][ORIGIN] = hitinfo->position + (hitinfo->normal * EPSILON);
	if (hitinfo->inside)
		refractive_index = hitinfo->material.ior;
	else
		refractive_index = 1.0f / hitinfo->material.ior;
	refract_dir = vec3f_refract(ray[0][DIR], hitinfo->normal, refractive_index);
	refract_dir = vec3f_normalize(vec3f_lerp(refract_dir, -diffuse_dir, \
		hitinfo->material.refraction_roughness * \
		hitinfo->material.refraction_roughness));
	ray[0][DIR] = vec3f_lerp(diffuse_dir, specular_dir, do_specular);
	ray[0][DIR] = vec3f_lerp(ray[0][DIR], refract_dir, do_refraction);
}

// specular_chance = FresnelReflectAmount(
// 	hitinfo->inside ? hitinfo->material.ior : 1.0f, 
// 	!hitinfo->inside ? hitinfo->material.ior : 1.0f,
// 	ray[0][DIR], hitinfo->normal, hitinfo->material.specular, 1.0f);
void	update_ray(t_rayf *ray, t_hitinfo *hitinfo, uint32_t *rngState, \
					t_vec3f *ray_color)
{
	float		do_specular;
	float		do_refraction;
	float		specular_chance;
	float		refraction_chance;
	const float	ray_select_roll = randomFloat(rngState);

	specular_chance = hitinfo->material.specular;
	refraction_chance = hitinfo->material.refraction;
	if (specular_chance > 0.0f)
	{
		specular_chance = get_specular_chance(ray[0][DIR], hitinfo);
		refraction_chance *= ((1.0f - specular_chance) \
			/ (1.0f - hitinfo->material.specular));
	}
	do_specular = 0.0f;
	do_refraction = 0.0f;
	if (specular_chance > 0.0f && ray_select_roll < specular_chance)
		do_specular = 1.0f;
	else if (refraction_chance > 0.0f && \
		ray_select_roll < specular_chance + refraction_chance)
		do_refraction = 1.0f;
	if (do_refraction == 0.0f)
		*ray_color *= vec3f_lerp(hitinfo->material.color, \
			hitinfo->material.specular_color, do_specular);
	calc_ray(ray, hitinfo, do_specular, do_refraction, rngState);
}




// void	calc_ray(t_rayf *ray, t_hitinfo *hitinfo, float do_specular, float do_refraction, uint32_t *rngState)
// {
// 	if (do_refraction == 1.0f)
// 		ray[0][ORIGIN] = hitinfo->position - (hitinfo->normal * EPSILON);
// 	else
// 		ray[0][ORIGIN] = hitinfo->position + (hitinfo->normal * EPSILON);
// 	const t_vec3f	diffuse_dir = vec3f_normalize(hitinfo->normal + random_directionf(rngState));
		
// 	t_vec3f	specular_dir = vec3f_reflect(ray[0][DIR], hitinfo->normal);//? squartroot?
// 	specular_dir = vec3f_lerp(specular_dir, diffuse_dir, hitinfo->material.roughness * hitinfo->material.roughness);
	
// 	t_vec3f	refraction_dir = vec3f_refract(ray[0][DIR], hitinfo->normal, hitinfo->inside ? hitinfo->material.ior : 1.0f / hitinfo->material.ior);
	
// 	refraction_dir = vec3f_normalize(vec3f_lerp(refraction_dir, -diffuse_dir, hitinfo->material.refraction_roughness * hitinfo->material.refraction_roughness));
// 	ray[0][DIR] = vec3f_lerp(diffuse_dir, specular_dir, do_specular);
// 	ray[0][DIR] = vec3f_lerp(ray[0][DIR], refraction_dir, do_refraction);
// }

// float	get_specular_chance(t_vec3f ray_dir, t_hitinfo *hitinfo)
// {
// 	float	specular_chance;

// 	if (hitinfo->inside)
// 	{
// 		specular_chance = fresnel_reflect_amount(hitinfo->material.ior, 1.0f, \
// 			ray_dir, hitinfo->normal, hitinfo->material.specular, 1.0f);
// 	}
// 	else
// 	{
// 		specular_chance = fresnel_reflect_amount(1.0f, hitinfo->material.ior, \
// 			ray_dir, hitinfo->normal, hitinfo->material.specular, 1.0f);
// 	}
// 	return (specular_chance);
// }

// // specular_chance = FresnelReflectAmount(
// // 	hitinfo->inside ? hitinfo->material.ior : 1.0f, !hitinfo->inside ? hitinfo->material.ior : 1.0f,
// // 	ray[0][DIR], hitinfo->normal, hitinfo->material.specular, 1.0f);
// void	update_ray(t_rayf *ray, t_hitinfo *hitinfo, uint32_t *rngState, t_vec3f *ray_color)
// {
// 	float		do_specular;
// 	float		do_refraction;
// 	float		specular_chance;
// 	float		refraction_chance;
// 	const float	ray_select_roll = randomFloat(rngState);

// 	specular_chance = hitinfo->material.specular;
// 	refraction_chance = hitinfo->material.refraction;
// 	if (specular_chance > 0.0f)
// 	{
// 		specular_chance = get_specular_chance(ray[0][DIR], hitinfo);
// 		refraction_chance *= ((1.0f - specular_chance) / (1.0f - hitinfo->material.specular));
// 	}
// 	do_specular = 0.0f;
// 	do_refraction = 0.0f;
// 	if (specular_chance > 0.0f && ray_select_roll < specular_chance)
// 		do_specular = 1.0f;
// 	else if (refraction_chance > 0.0f && ray_select_roll < specular_chance + refraction_chance)
// 		do_refraction = 1.0f;
// 	if (do_refraction == 0.0f)
// 		*ray_color *= vec3f_lerp(hitinfo->material.color, hitinfo->material.specular_color, do_specular);
// 	calc_ray(ray, hitinfo, do_specular, do_refraction, rngState);
// }


