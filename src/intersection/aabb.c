/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 20:50:34 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/05 14:49:12 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// float aabb_intersection_f(t_rayf ray, t_aabb aabb)
// {
// 	// float t1,t2,tnear = -1000.0f,tfar = 1000.0f,temp,tCube;
// 	float t1,t2,tnear = EPSILON,tfar = 1000.0f,temp,tCube;
// 	bool intersectFlag = true;

// 	t_vec3f b1 = aabb.min_f;
// 	t_vec3f b2 = aabb.max_f;
	
// 	for(int i =0 ;i < 3; i++)
// 	{
// 		if(ray[DIR][i] == 0)
// 		{
// 			if(ray[ORIGIN][i] < b1[i] || ray[ORIGIN][i] > b2[i])
// 				intersectFlag = false;
// 		}
// 		else
// 		{
// 			t1 = (b1[i] - ray[ORIGIN][i])/ray[DIR][i];
// 			t2 = (b2[i] - ray[ORIGIN][i])/ray[DIR][i];
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

void	swap_float(float *a, float *b)
{
	float temp = *a;
	*a = *b;
	*b = temp;
}

float aabb_intersection_f(t_rayf ray, t_aabb aabb)
{
	float tnear = -1000.0f;
	float tfar = 1000.0f;

	for (int i = 0; i < 3; i++)
	{
		float t1, t2;
		if (ray[DIR][i] == 0)
		{
			if (ray[ORIGIN][i] < aabb.min_f[i] || ray[ORIGIN][i] > aabb.max_f[i])
				return 0;  // No intersection, return early
		}
		else
		{
			t1 = (aabb.min_f[i] - ray[ORIGIN][i]) / ray[DIR][i];
			t2 = (aabb.max_f[i] - ray[ORIGIN][i]) / ray[DIR][i];

			if (t1 > t2)
				swap_float(&t1, &t2);
			if (t1 > tnear)
				tnear = t1;
			if (t2 < tfar)
				tfar = t2;
			if (tnear > tfar || tfar < 0)
				return 0;  // No intersection, return early
		}
	}
	return tnear;
}
