/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/04/22 16:59:20 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_mat4	fill_mat4(float f)
{
	const t_mat4	new = {
	{{f, f, f, f},
	{f, f, f, f},
	{f, f, f, f},
	{f, f, f, f}}};

	return (new);
}

t_mat4	create_mat4(float f)
{
	return (fill_mat4(f));
}

t_mat4	mat4_identity(void)
{
	t_mat4	result;

	result = create_mat4(0.0f);
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	return (result);
}

t_mat4	mat4_inverse(t_mat4 m)
{
	t_mat4	inv;
	t_mat4	mat;
	int		pivot_row;
	float	pivot;
	int		i;

	inv = mat4_identity();
	mat = m;
	i = 0;
	while (i < 4)
	{
		pivot_row = i;
		pivot = mat.m[i][i];
		inverse_1(mat, i, &pivot_row, &pivot);
		if (fabs(pivot) < 1e-8)
			return (mat);
		mat = swap_rows(mat, i, pivot_row);
		inv = swap_rows(inv, i, pivot_row);
		mat = scale_row(mat, i, 1.0f / pivot);
		inv = scale_row(inv, i, 1.0f / pivot);
		inverse_2(&inv, &mat, i);
		i++;
	}
	return (inv);
}
