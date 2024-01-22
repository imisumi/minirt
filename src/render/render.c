/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:32:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/22 17:24:37 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3f	vec3f_reflect(t_vec3f v, t_vec3f n)
{
	return (v - (n * 2.0f * vec3f_dot(v, n)));
}


t_vec3f vec3f_lerp(const t_vec3f vec1, const t_vec3f vec2, const float t)
{
	const t_vec3f	result = (1.0f - t) * vec1 + t * vec2;

	return (result);
}

float	lerpf(float a, float b, float t)
{
	return (a + (b - a) * t);
}

float FresnelReflectAmount(float n1, float n2, t_vec3f incident, t_vec3f normal, float f0, float f90)
{
	// Schlick aproximation
	float r0 = (n1-n2) / (n1+n2);
	r0 *= r0;
	float cosX = -vec3f_dot(normal, incident);
	if (n1 > n2)
	{
	    float n = n1 / n2;
	    float sinT2 = n*n*(1.0-cosX*cosX);
	    // Total internal reflection
	    if (sinT2 > 1.0)
	        return f90;
	    cosX = sqrtf(1.0-sinT2);
	}
	float x = 1.0-cosX;
	float ret = r0+(1.0-r0)*x*x*x*x*x;
	
	// adjust reflect multiplier for object reflectivity
	return lerpf(f0, f90, ret);
}

// t_vec4f	per_pixel(t_vec3f dir, t_scene scene, uint32_t *rngState)
// {
// 	int bounce = 0;
// 	t_vec3f incomming_light = {0.0f, 0.0f, 0.0f, 0.0f};
// 	t_vec3f ray_color = {1.0f, 1.0f, 1.0f, 0.0f};

// 	t_vec3f ray[2];
// 	ray[ORIGIN] = scene.camera.position;
// 	ray[DIR] = dir;

// 	t_hitinfo hitinfo;
// 	float	bounce_attenuation = 0.8f;
// 	while (bounce <= MAX_BOUNCES)
// 	{
// 		//! check
// 		hitinfo.distance = INFINITY;
// 		hitinfo.hit = false;
		
// 		// hitinfo = inv_plane_intersection(ray, scene, hitinfo);
// 		// hitinfo = inv_plane_intersection_f(ray, scene, hitinfo);
// 		// hitinfo = sphere_intersection_f(ray, scene, hitinfo);
// 		if (USE_BVH)
// 			hitinfo = sphere_bvh_intersection_f(ray, scene.spheres, hitinfo, scene.bvh_spheres_f);
// 		else
// 			hitinfo = sphere_intersection_f(ray, scene, hitinfo);


// 		hitinfo = inv_plane_intersection_f(ray, scene, hitinfo);
		
// 		if (hitinfo.hit)
// 		{
// 			ray[ORIGIN] = hitinfo.position + (hitinfo.normal * EPSILON);
// 			t_vec3f	diffuse_dir = vec3f_normalize(hitinfo.normal + random_directionf(rngState));
// 			t_vec3f	specular_dir = vec3f_reflect(ray[DIR], hitinfo.normal);
// 			// specular_dir = vec3f_normalize(vec3f_lerp(specular_dir, diffuse_dir, hitinfo.material.roughness));
// 			specular_dir = vec3f_lerp(specular_dir, diffuse_dir, hitinfo.material.roughness);

			
// 			bool	is_specular = (hitinfo.material.specular >= randomFloat(rngState));

// 			//? fresnel
// 			float	specular_chance = hitinfo.material.specular;
// 			if (specular_chance > 0.0f)
// 			{
// 				specular_chance = FresnelReflectAmount(1.0f, 1.5f, ray[DIR], hitinfo.normal, specular_chance, 1.0f);
// 			}
// 			is_specular = (specular_chance >= randomFloat(rngState));

// 			ray[DIR] = vec3f_lerp(diffuse_dir, specular_dir, is_specular);
			
// 			float intensity_scale = powf(bounce_attenuation, bounce);

// 			t_vec3f emitted_light = {0};
// 			emitted_light = omni_dir_light_f(ray, scene, hitinfo);

			
// 			// emitted_light += omni_dir_light_f2(ray, scene, hitinfo);
// 			// emitted_light = omni_dir_light_f_comb(ray, scene, hitinfo);
// 			emitted_light = emitted_light * intensity_scale;

// 			//! add emission
// 			emitted_light += hitinfo.material.color * hitinfo.material.emission_strength;

// 			// ray_color *= hitinfo.material.color;
// 			ray_color *= vec3f_lerp(hitinfo.material.color, hitinfo.material.specular_color, is_specular);
// 			incomming_light = incomming_light + (ray_color * emitted_light);
			
// 			float p = fmaxf(fmaxf(ray_color[X], ray_color[Y]), ray_color[Z]);
// 			if (randomFloat(rngState) > p)
// 				break ;
// 			ray_color *= (1.0f / p);
// 		}
// 		else
// 		{
// 			t_vec3f	sky;
// 			// if (scene.ambient_light == 0.0f)
// 			// 	break ;
// 			// else if (scene.ambient_light == -1.0f)
// 			// 	sky = default_skyf(ray[DIR], scene);
// 			// else
// 			// 	sky = scene.ambient_color * scene.ambient_light;

				
// 			// sky = default_skyf(ray[DIR], scene);
// 			// incomming_light = vec3_add(incomming_light, vec3_mul(ray_color, sky));
// 			// t_vec3f sky = {0.5f, 0.5f, 0.5f, 0.0f};
// 			if (BONUS && scene.hdri.rgba != NULL)
// 				sky = texture(ray[DIR], scene.hdri);
// 			else if (scene.ambient_light > 0.0f)
// 				sky = scene.ambient_color * scene.ambient_light;
// 			// else
// 			// 	sky = default_skyf(ray[DIR], scene);
// 			// sky = (t_vec3f){1, 1, 1, 1};
// 			// sky = (t_vec3f){0, 0, 0, 0};
// 			incomming_light = incomming_light + (ray_color * sky);
// 			break ;
// 		}
// 		bounce++;
// 	}
// 	// return ((t_vec4){incomming_light.x, incomming_light.y, incomming_light.z, 1.0f});
// 	return ((t_vec4f){incomming_light[X], incomming_light[Y], incomming_light[Z], 1.0f});
// }

t_vec3f	vec3f_exp(t_vec3f v)
{
	return ((t_vec3f){expf(v[X]), expf(v[Y]), expf(v[Z]), 0.0f});
}

// Function to calculate refraction of a vector
// t_vec3f vec3f_refract(t_vec3f incident, t_vec3f normal, float eta)
// {
// 	float cosI = vec3f_dot(-incident, normal);
// 	float sinT2 = eta * eta * (1.0 - cosI * cosI);
	
// 	if (sinT2 > 1.0) {
// 	    // Total internal reflection
// 	    return (t_vec3f){0.0f, 0.0f, 0.0f, 0.0f};
// 	}
	
// 	float cosT = sqrtf(1.0 - sinT2);
// 	return eta * incident + (eta * cosI - cosT) * normal;
// }

// t_vec3f vec3f_refract(t_vec3f uv, t_vec3f n, float etai_over_etat)
// {
//     float cos_theta = fmin(vec3f_dot(-uv, n), 1.0);
//     t_vec3f r_out_perp =  etai_over_etat * (uv + cos_theta*n);
// 	float sqrt_term = -sqrt(fabs(1.0 - vec3f_length(r_out_perp)));
//     // t_vec3f r_out_parallel = -sqrt(fabs(1.0 - vec3f_length(r_out_perp))) * n;
// 	t_vec3f r_out_parallel = sqrt_term * n;
//     return r_out_perp + r_out_parallel;
// }

t_vec3f	vec3f_refract(t_vec3f incident, t_vec3f normal, float eta)
{
	t_vec3f out;
	float N_dot_I = vec3f_dot(normal, incident);
	float k = 1.f - eta * eta * (1.f - N_dot_I * N_dot_I);
	if (k < 0.f)
		out = (t_vec3f){0.f, 0.f, 0.f, 0.0f};
	else
		out = eta * incident - (eta * N_dot_I + sqrtf(k)) * normal;

	return (out);
}



t_vec4f	apply_enviorment(t_rayf ray, t_scene scene, t_vec4f incomming_light, t_vec4f ray_color)
{
	t_vec3f	sky;

	if (BONUS && scene.hdri.rgba != NULL)
		sky = texture(ray[DIR], scene.hdri);
	else if (scene.ambient_light > 0.0f)
		sky = scene.ambient_color * scene.ambient_light;
	else
		sky = (t_vec3f){0.0f, 0.0f, 0.0f, 0.0f};
	incomming_light = incomming_light + (ray_color * sky);
	return ((t_vec4f){incomming_light[X], incomming_light[Y], incomming_light[Z], 1.0f});
}

t_vec4f	per_pixel(t_vec3f dir, t_scene scene, uint32_t *rngState)
{
	int bounce = 0;
	t_vec3f incomming_light = {0.0f, 0.0f, 0.0f, 0.0f};
	t_vec3f ray_color = {1.0f, 1.0f, 1.0f, 0.0f};

	t_vec3f ray[2];
	ray[ORIGIN] = scene.camera.position;
	ray[DIR] = dir;

	t_hitinfo hitinfo;
	float	bounce_attenuation = 0.7f;
	while (bounce <= MAX_BOUNCES)
	{
		//! check
		hitinfo.distance = INFINITY;
		hitinfo.hit = false;
		hitinfo.inside = false;
		
		if (USE_BVH && vec_length(&scene.spheres) > 0)
			hitinfo = sphere_bvh_intersection_f(ray, scene.spheres, hitinfo, scene.bvh_spheres_f);
		else
			hitinfo = sphere_intersection_f(ray, scene, hitinfo);

		hitinfo = inv_plane_intersection_f(ray, scene, hitinfo);

		// if (scene.num_tri_meshes > 0)
		// tri_mesh_intersection(ray, &scene, &hitinfo);

		// hitinfo = triangle_bvh_intersection(ray, scene.tri_meshes[0], hitinfo, scene.tri_meshes[0].bvh);
		// hitinfo = triangle_bvh_intersection(ray, scene.tri_meshes[1], hitinfo, scene.tri_meshes[1].bvh);

		if (scene.num_tri_meshes > 0)
			hitinfo = mesh_bvh_intersection(ray, scene.tri_meshes, hitinfo, scene.bvh_meshes);
		
		if (!hitinfo.hit && !RENDER_SKYBOX && bounce == 0)
			return ((t_vec4f){0.0f, 0.0f, 0.0f, 1.0f});
		if (hitinfo.hit == false)
			return (apply_enviorment(ray, scene, incomming_light, ray_color));

		if (hitinfo.inside)
			ray_color *= vec3f_exp(-hitinfo.material.refraction_color * hitinfo.distance);

		float	specular_chance = hitinfo.material.specular;
		float	refraction_chance = hitinfo.material.refraction;

		float	ray_probability = 1.0f;
		if (specular_chance > 0.0f)
		{
			specular_chance = FresnelReflectAmount(
				hitinfo.inside ? hitinfo.material.ior : 1.0f,
				!hitinfo.inside ? hitinfo.material.ior : 1.0f,
				ray[DIR], hitinfo.normal, hitinfo.material.specular, 1.0f);
			float chance = (1.0f - specular_chance) / (1.0f - hitinfo.material.specular);
			refraction_chance *= chance;
		}

		float	do_specular = 0.0f;
		float	do_refraction = 0.0f;
		float	ray_select_roll = randomFloat(rngState);
		if (specular_chance > 0.0f && ray_select_roll < specular_chance)
		{
			do_specular = 1.0f;
			ray_probability = specular_chance;
		}
		else if (refraction_chance > 0.0f && ray_select_roll < specular_chance + refraction_chance)
		{
			do_refraction = 1.0f;
			ray_probability = refraction_chance;
		}
		else
			ray_probability = 1.0f - (specular_chance - refraction_chance);

		ray_probability = fmaxf(ray_probability, 0.001f);

		if (do_refraction == 1.0f)
			ray[ORIGIN] = hitinfo.position - (hitinfo.normal * EPSILON);
		else
			ray[ORIGIN] = hitinfo.position + (hitinfo.normal * EPSILON);
		

		t_vec3f	diffuse_dir = vec3f_normalize(hitinfo.normal + random_directionf(rngState));
		
		t_vec3f	specular_dir = vec3f_reflect(ray[DIR], hitinfo.normal);//? squartroot?
		specular_dir = vec3f_lerp(specular_dir, diffuse_dir, hitinfo.material.roughness * hitinfo.material.roughness);
		
		t_vec3f	refraction_dir = vec3f_refract(ray[DIR], hitinfo.normal, hitinfo.inside ? hitinfo.material.ior : 1.0f / hitinfo.material.ior);
		
		refraction_dir = vec3f_normalize(vec3f_lerp(refraction_dir, -diffuse_dir, hitinfo.material.refraction_roughness * hitinfo.material.refraction_roughness));


		ray[DIR] = vec3f_lerp(diffuse_dir, specular_dir, do_specular);
		ray[DIR] = vec3f_lerp(ray[DIR], refraction_dir, do_refraction);

		if (do_refraction == 0.0f)
		{
			ray_color *= vec3f_lerp(hitinfo.material.color, hitinfo.material.specular_color, do_specular);
		}

		float p = fmaxf(fmaxf(ray_color[X], ray_color[Y]), ray_color[Z]);
		if (randomFloat(rngState) > p)
			break ;
		//??????
		ray_color *= (1.0f / p);

		float intensity_scale = powf(bounce_attenuation, bounce);

		t_vec3f emitted_light = {0};
		emitted_light = omni_dir_light_f(ray, scene, hitinfo);


		//! add emission
		emitted_light += hitinfo.material.color * hitinfo.material.emission_strength;

		//????
		// emitted_light *= intensity_scale;
		
		// ray_color *= vec3f_lerp(hitinfo.material.color, hitinfo.material.specular_color, is_specular);
		incomming_light = incomming_light + (ray_color * emitted_light);
		bounce++;
	}
	return ((t_vec4f){incomming_light[X], incomming_light[Y], incomming_light[Z], 1.0f});
}



// t_vec4f	per_pixel(t_vec3f dir, t_scene scene, uint32_t *rngState)
// {
// 	int bounce = 0;
// 	t_vec3f ret = {0.0f, 0.0f, 0.0f, 0.0f};
// 	t_vec3f throughput = {1.0f, 1.0f, 1.0f, 0.0f};

// 	t_vec3f ray[2];
// 	ray[ORIGIN] = scene.camera.position;
// 	ray[DIR] = dir;

// 	t_hitinfo hitinfo;
// 	float	bounce_attenuation = 0.8f;
// 	while (bounce <= MAX_BOUNCES)
// 	{
// 		//! check
// 		hitinfo.distance = INFINITY;
// 		hitinfo.hit = false;
// 		hitinfo.inside = false;
		
// 		if (USE_BVH)
// 			hitinfo = sphere_bvh_intersection_f(ray, scene.spheres, hitinfo, scene.bvh_spheres_f);
// 		else
// 			hitinfo = sphere_intersection_f(ray, scene, hitinfo);
// 		// // hitinfo = inv_plane_intersection_f(ray, scene, hitinfo);
// 		// hitinfo.material.refraction = 1.0f;
// 		// hitinfo = single_sphere_intersection_f(ray, scene.spheres[0], hitinfo);
// 		if (hitinfo.hit == false)
// 			return (apply_enviorment(ray, scene, ret, throughput));




// 		if (hitinfo.inside)
// 			throughput *= vec3f_exp(-hitinfo.material.refraction_color * hitinfo.distance);

// 		float specular_chance = hitinfo.material.specular;
// 		float refraction_chance = hitinfo.material.refraction;

// 		float ray_probability = 1.0f;
// 		if (specular_chance > 0.0f)
// 		{
// 			specular_chance = FresnelReflectAmount(
// 				hitinfo.inside ? hitinfo.material.ior : 1.0f,
// 				!hitinfo.inside ? hitinfo.material.ior : 1.0f,
// 				ray[DIR], hitinfo.normal, hitinfo.material.specular, 1.0f);

// 			float chance_multiplier = (1.0f - specular_chance) / (1.0f - hitinfo.material.specular);
// 			refraction_chance *= chance_multiplier;
// 		}

// 		float	do_specular = 0.0f;
// 		float	do_refraction = 0.0f;
// 		float	ray_select_roll = randomFloat(rngState);
// 		if (specular_chance > 0.0f && ray_select_roll < specular_chance)
// 		{
// 			do_specular = 1.0f;
// 			ray_probability = specular_chance;
// 		}
// 		else if (refraction_chance > 0.0f && ray_select_roll < specular_chance + refraction_chance)
// 		{
// 			do_refraction = 1.0f;
// 			ray_probability = refraction_chance;
// 		}
// 		else
// 		{
// 			ray_probability = 1.0f - (specular_chance - refraction_chance);
// 		}
// 		ray_probability = fmaxf(ray_probability, 0.001f);
// 		if (do_refraction == 1.0f)
// 		{
// 			ray[ORIGIN] = hitinfo.position - (hitinfo.normal * EPSILON);
// 		}
// 		else
// 		{
// 			ray[ORIGIN] = hitinfo.position + (hitinfo.normal * EPSILON);
// 		}

// 		t_vec3f	diffuse_dir = vec3f_normalize(hitinfo.normal + random_directionf(rngState));

// 		t_vec3f	specular_dir = vec3f_reflect(ray[DIR], hitinfo.normal);
// 		specular_dir = vec3f_lerp(specular_dir, diffuse_dir, hitinfo.material.roughness * hitinfo.material.roughness);

// 		t_vec3f	refraction_dir = vec3f_refract(ray[DIR], hitinfo.normal, hitinfo.inside ? hitinfo.material.ior : 1.0f / hitinfo.material.ior);
// 		// refraction_dir = vec3f_normalize(vec3f_lerp(refraction_dir, -diffuse_dir, hitinfo.material.refraction_roughness * hitinfo.material.refraction_roughness));
// 		// refractionRayDir = normalize(mix(refractionRayDir, normalize(-hitInfo.normal + RandomUnitVector(rngState)), hitInfo.material.refractionRoughness*hitInfo.material.refractionRoughness));
// 		refraction_dir = vec3f_normalize(vec3f_lerp(refraction_dir, vec3f_normalize(-hitinfo.normal + random_directionf(rngState)), hitinfo.material.refraction_roughness * hitinfo.material.refraction_roughness));

// 		ray[DIR] = vec3f_lerp(diffuse_dir, specular_dir, do_specular);
// 		ray[DIR] = vec3f_lerp(ray[DIR], refraction_dir, do_refraction);

// 		ret += hitinfo.material.emission_strength * throughput;

// 		if (do_refraction == 0.0f)
// 		{
// 			throughput *= vec3f_lerp(hitinfo.material.color, hitinfo.material.specular_color, do_specular);
// 		}

// 		throughput /= ray_probability;

// 		float p = fmaxf(fmaxf(throughput[X], throughput[Y]), throughput[Z]);
// 		if (randomFloat(rngState) > p)
// 			break ;
// 		throughput *= (1.0f / p);
// 		bounce++;
// 	}
// 	return ((t_vec4f){ret[X], ret[Y], ret[Z], 1.0f});
// }

void	render_pixel(t_data *data, uint32_t x, uint32_t y)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	hex_color;
	t_vec4f		avg_color;

	avg_color = data->utils.accumulated_data[x + y * data->utils.width];
	avg_color /= (float)data->utils.accumulated_frames;
	avg_color = vec3f_tone_map(avg_color);
	//? clamp 0.0f - 1.0f maybe not needed
	hex_color = vec4f_to_color(avg_color);
	i = 0;
	while (i < PIXEL_SIZE)
	{
		j = 0;
		while (j < PIXEL_SIZE)
		{
			//! RRGGBBAA
			put_pixel(data->img, (x * PIXEL_SIZE) + i, \
				((data->utils.height - y - 1) * PIXEL_SIZE) + j, \
				hex_color);
			j++;
		}
		i++;
	}
}

void	*render(void *arg)
{
	const t_thread	*thread = arg;
	t_data	*data;

	data = thread->data;
	uint32_t	x;
	uint32_t	y;
	uint32_t	rngState;
	t_vec4f		color;
	t_vec3f		dir;
	
	y = thread->y_start;
	while (y < thread->y_end)
	{
		x = thread->x_start;
		while (x < thread->x_end)
		{
			rngState = get_rngstate(data->utils.width, data->utils.height, x, y);
			dir = data->scene.camera.ray_dir[x + y * data->utils.width];
			if (AA)
				dir = aa_update_dir(data, &rngState, x, y);
			color = per_pixel(dir, data->scene, &rngState);
			data->utils.accumulated_data[x + y * data->utils.width] += color;
			render_pixel(data, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}
