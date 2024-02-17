/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:44:47 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/16 20:09:40 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darray.h"

typedef struct s_array
{
	uint32_t	capacity;
	uint32_t	count;
	size_t		element_size;
}				t_array;

void	vec_clear(void *refvec)
{
	t_array	*info;

	info = *(t_array **)refvec - 1;
	info->count = 0;
}

void	vec_free(void *refvec)
{
	t_array	*info;

	info = *(t_array **)refvec - 1;
	free(info);
	*(void **)refvec = NULL;
}

int	vec_length(void *refvec)
{
	t_array	*info;

	info = *(t_array **)refvec - 1;
	return (info->count);
}
