/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 20:50:34 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/14 04:54:30 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	swap_float(float *a, float *b)
{
	float	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static bool	aabb_check_intersection(float *tnear, float *tfar, \
	float t1, float t2)
{
	if (t1 > t2)
		swap_float(&t1, &t2);
	if (t1 > *tnear)
		*tnear = t1;
	if (t2 < *tfar)
		*tfar = t2;
	if (*tnear > *tfar || *tfar < 0)
		return (false);
	return (true);
}

// float	aabb_intersection_f(t_rayf ray, t_aabb aabb)
// {
// 	float	tnear;
// 	float	tfar;
// 	float	t1;
// 	float	t2;
// 	int		i;

// 	tnear = -1000.0f;
// 	tfar = 1000.0f;
// 	i = 0;
// 	while (i < 3)
// 	{
// 		if (ray[DIR][i] == 0)
// 		{
// 			if (ray[ORIGIN][i] < aabb.min_f[i] || \
// 				ray[ORIGIN][i] > aabb.max_f[i])
// 				return (0);
// 		}
// 		else
// 		{
// 			t1 = (aabb.min_f[i] - ray[ORIGIN][i]) / ray[DIR][i];
// 			t2 = (aabb.max_f[i] - ray[ORIGIN][i]) / ray[DIR][i];
// 			if (!aabb_check_intersection(&tnear, &tfar, t1, t2))
// 				return (0);
// 		}
// 		i++;
// 	}
// 	return (tnear);
// }

// float	aabb_intersection_f(t_rayf ray, t_aabb aabb)
// {
// 	float	tnear;
// 	float	tfar;
// 	float	t1;
// 	float	t2;
// 	int		i;

// 	tnear = -1000.0f;
// 	tfar = 1000.0f;
// 	i = 0;
// 	while (i < 3)
// 	{
// 		if (ray[DIR][i] == 0)
// 		{
// 			if (ray[ORIGIN][i] < aabb.min_f[i] || \
// 				ray[ORIGIN][i] > aabb.max_f[i])
// 				return (0);
// 		}
// 		else
// 		{
// 			t1 = (aabb.min_f[i] - ray[ORIGIN][i]) / ray[DIR][i];
// 			t2 = (aabb.max_f[i] - ray[ORIGIN][i]) / ray[DIR][i];
// 			if (!aabb_check_intersection(&tnear, &tfar, t1, t2))
// 				return (0);
// 		}
// 		i++;
// 	}
// 	return (tnear);
// }

float	aabb_intersection_f(t_rayf ray, t_aabb aabb)
{
	float	tnear;
	float	tfar;
	float	t1;
	float	t2;
	int		i;

	tnear = -1000.0f;
	tfar = 1000.0f;
	i = 0;
	while (i < 3)
	{
		if (ray[DIR][i] == 0)
		{
			if (ray[ORIGIN][i] < aabb.min_f[i] || \
				ray[ORIGIN][i] > aabb.max_f[i])
				return (0);
		}
		else
		{
			t1 = (aabb.min_f[i] - ray[ORIGIN][i]) / ray[DIR][i];
			t2 = (aabb.max_f[i] - ray[ORIGIN][i]) / ray[DIR][i];
			if (!aabb_check_intersection(&tnear, &tfar, t1, t2))
				return (0);
		}
		i++;
	}
	return (tnear);
}