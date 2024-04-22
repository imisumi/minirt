/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2024/04/22 16:59:14 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_mat4	swap_rows(t_mat4 mat, int row1, int row2)
{
	int		i;
	float	temp;

	i = 0;
	while (i < 4)
	{
		temp = mat.m[row1][i];
		mat.m[row1][i] = mat.m[row2][i];
		mat.m[row2][i] = temp;
		i++;
	}
	return (mat);
}

t_mat4	scale_row(t_mat4 mat, int row, float scalar)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mat.m[row][i] *= scalar;
		i++;
	}
	return (mat);
}

t_mat4	add_rows(t_mat4 mat, int row1, int row2, float scalar)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mat.m[row1][i] += scalar * mat.m[row2][i];
		i++;
	}
	return (mat);
}

void	inverse_2(t_mat4 *inv, t_mat4 *mat, int i)
{
	int		j;
	float	factor;

	j = 0;
	while (j < 4)
	{
		if (j != i)
		{
			factor = -mat->m[j][i];
			*mat = add_rows(*mat, j, i, factor);
			*inv = add_rows(*inv, j, i, factor);
		}
		j++;
	}
}

void	inverse_1(t_mat4 mat, int i, int *pivot_row, float *pivot)
{
	int		j;

	j = i + 1;
	while (j < 4)
	{
		if (fabs(mat.m[j][i]) > fabs(*pivot))
		{
			*pivot_row = j;
			*pivot = mat.m[j][i];
		}
		j++;
	}
}
