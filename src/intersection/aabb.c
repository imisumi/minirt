/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 20:50:34 by ichiro            #+#    #+#             */
/*   Updated: 2023/12/18 23:37:58 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float aabb_intersection(t_ray ray, t_aabb aabb)
{
	float t1,t2,tnear = -1000.0f,tfar = 1000.0f,temp,tCube;
	bool intersectFlag = true;

	float rayDirection[3];
	rayDirection[0] = ray.direction.x;
	rayDirection[1] = ray.direction.y;
	rayDirection[2] = ray.direction.z;

	float rayStart[3];
	rayStart[0] = ray.origin.x;
	rayStart[1] = ray.origin.y;
	rayStart[2] = ray.origin.z;

	float b1[3];
	b1[0] = aabb.min.x;
	b1[1] = aabb.min.y;
	b1[2] = aabb.min.z;

	float b2[3];
	b2[0] = aabb.max.x;
	b2[1] = aabb.max.y;
	b2[2] = aabb.max.z;
	
	for(int i =0 ;i < 3; i++)
	{
		if(rayDirection[i] == 0)
		{
			if(rayStart[i] < b1[i] || rayStart[i] > b2[i])
				intersectFlag = false;
		}
		else
		{
			t1 = (b1[i] - rayStart[i])/rayDirection[i];
			t2 = (b2[i] - rayStart[i])/rayDirection[i];
		if(t1 > t2)
		{
			temp = t1;
			t1 = t2;
			t2 = temp;
		}
		if(t1 > tnear)
			tnear = t1;
		if(t2 < tfar)
			tfar = t2;
		if(tnear > tfar)
			intersectFlag = false;
		if(tfar < 0)
			intersectFlag = false;
		}
	}
	if(intersectFlag == false)
		tCube = 0;
	else
		tCube = tnear;
	
	return tCube;
}


// float aabb_intersection_f(t_rayf ray, t_aabb aabb)
// {
// 	float t1,t2,tnear = -1000.0f,tfar = 1000.0f,temp,tCube;
// 	bool intersectFlag = true;

// 	float rayDirection[3];
// 	rayDirection[0] = ray[DIR][X];
// 	rayDirection[1] = ray[DIR][Y];
// 	rayDirection[2] = ray[DIR][Z];

// 	float rayStart[3];
// 	rayStart[0] = ray[ORIGIN][X];
// 	rayStart[1] = ray[ORIGIN][Y];
// 	rayStart[2] = ray[ORIGIN][Z];

// 	float b1[3];
// 	b1[0] = aabb.min_f[X];
// 	b1[1] = aabb.min_f[Y];
// 	b1[2] = aabb.min_f[Z];

// 	float b2[3];
// 	b2[0] = aabb.max_f[X];
// 	b2[1] = aabb.max_f[Y];
// 	b2[2] = aabb.max_f[Z];
	
// 	for(int i =0 ;i < 3; i++)
// 	{
// 		if(rayDirection[i] == 0)
// 		{
// 			if(rayStart[i] < b1[i] || rayStart[i] > b2[i])
// 				intersectFlag = false;
// 		}
// 		else
// 		{
// 			t1 = (b1[i] - rayStart[i])/rayDirection[i];
// 			t2 = (b2[i] - rayStart[i])/rayDirection[i];
// 		if(t1 > t2)
// 		{
// 			temp = t1;
// 			t1 = t2;
// 			t2 = temp;
// 		}
// 		if(t1 > tnear)
// 			tnear = t1;
// 		if(t2 < tfar)
// 			tfar = t2;
// 		if(tnear > tfar)
// 			intersectFlag = false;
// 		if(tfar < 0)
// 			intersectFlag = false;
// 		}
// 	}
// 	if(intersectFlag == false)
// 		tCube = 0;
// 	else
// 		tCube = tnear;
	
// 	return tCube;
// }


float aabb_intersection_f(t_rayf ray, t_aabb aabb)
{
	float t1,t2,tnear = -1000.0f,tfar = 1000.0f,temp,tCube;
	bool intersectFlag = true;

	t_vec3f b1 = aabb.min_f;
	t_vec3f b2 = aabb.max_f;
	
	for(int i =0 ;i < 3; i++)
	{
		if(ray[DIR][i] == 0)
		{
			if(ray[ORIGIN][i] < b1[i] || ray[ORIGIN][i] > b2[i])
				intersectFlag = false;
		}
		else
		{
			t1 = (b1[i] - ray[ORIGIN][i])/ray[DIR][i];
			t2 = (b2[i] - ray[ORIGIN][i])/ray[DIR][i];
		if(t1 > t2)
		{
			temp = t1;
			t1 = t2;
			t2 = temp;
		}
		if(t1 > tnear)
			tnear = t1;
		if(t2 < tfar)
			tfar = t2;
		if(tnear > tfar)
			intersectFlag = false;
		if(tfar < 0)
			intersectFlag = false;
		}
	}
	if(intersectFlag == false)
		tCube = 0;
	else
		tCube = tnear;
	
	return tCube;
}
