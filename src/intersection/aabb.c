/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 20:50:34 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/24 00:31:04 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
