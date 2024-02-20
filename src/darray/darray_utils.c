/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:44:47 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/20 16:46:02 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darray.h"

void	vec_clear(void *refvec)
{
	t_array	*info;

	info = *(t_array **)refvec - 1;
	info->count = 0;
}

void	vec_free(void *refvec)
{
	t_array	*info;

	if (refvec == NULL || !*(t_array **)refvec)
		return ;
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
