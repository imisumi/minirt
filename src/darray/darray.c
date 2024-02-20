/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:44:47 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/20 14:57:55 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darray.h"

// https://www.youtube.com/watch?v=Nn_hbAGnBOs&t=1157s
static void	exit_msg(char *msg)
{
	printf("Error: %s\n", msg);
	exit(1);
}

static void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;

	if (old_size == new_size)
		return (ptr);
	if (old_size > new_size)
		old_size = new_size;
	new = malloc(new_size);
	if (new == NULL)
		return (NULL);
	if (ptr != NULL)
	{
		ft_memcpy(new, ptr, old_size);
		free(ptr);
	}
	return (new);
}

void	vec_init(void *refvec, uint32_t capacity, size_t element_size)
{
	t_array	*info;

	info = malloc(sizeof(t_array) + (capacity * element_size));
	if (info == NULL)
		exit_msg("failed to allocate memory for array");
	*((void **)refvec) = info + 1;
	info->capacity = capacity;
	info->count = 0;
	info->element_size = element_size;
}

void	vec_push(void *refvec, void *value)
{
	t_array	*info;
	size_t	old_size;
	size_t	new_size;

	info = ((t_array *)(*((void **)refvec))) - 1;
	if (info->count >= info->capacity)
	{
		info->capacity *= 2;
		old_size = sizeof(t_array) + ((info->capacity / 2) * \
			info->element_size);
		new_size = sizeof(t_array) + (info->capacity * info->element_size);
		info = ft_realloc(info, old_size, new_size);
		if (info == NULL)
			exit_msg("failed to push element to array");
		*((void **)refvec) = info + 1;
	}
	ft_memcpy(
		(*(char **)refvec + (info->count * info->element_size)),
		value,
		info->element_size);
	info->count++;
}
