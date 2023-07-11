/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:29:39 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/25 23:53:11 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mat4.h"

t_mat4	fill_mat4(t_mat4 m, float f) {
	int i;
	int j;

	i = 0;
	while (i < 4) {
		j = 0;
		while (j < 4) {
			m.m[i][j] = f;
			j++;
		}
		i++;
	}
	return (m);
}

t_mat4	create_mat4(float f)
{
	t_mat4	m;

	m = fill_mat4(m, f);
	return (m);
}

t_mat4 mat4_identity(void)
{
	t_mat4 result = create_mat4(0.0f);
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	return result;
}