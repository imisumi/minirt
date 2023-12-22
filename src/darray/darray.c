/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:44:47 by ichiro            #+#    #+#             */
/*   Updated: 2023/12/09 00:39:53 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "darray.h"
#include "darray.h"

typedef struct s_array
{
	uint32_t	capacity;
	uint32_t	count;
	size_t		element_size;
}				t_array;

void	array_clear(void *refvec)
{
	t_array	*info;

	info = *(t_array **)refvec - 1;
	info->count = 0;
}

void	array_free(void *refvec)
{
	t_array	*info;

	info = *(t_array **)refvec - 1;
	free(info);
	*(void **)refvec = NULL;
}

int		array_length(void *refvec)
{
	t_array	*info;

	info = *(t_array **)refvec - 1;
	return (info->count);
}

void		*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(size));
	if (!size)
		return (ptr);
	new_ptr = malloc(size);
	if (new_ptr == NULL)
		return (NULL);
	memcpy(new_ptr, ptr, size);
	return (new_ptr);
}

void	vec_init(void *refvec, uint32_t capacity, size_t element_size)
{
	t_array	*info;

	info = malloc(sizeof(t_array) + (capacity * element_size));
	if (info == NULL)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
	*(void **)refvec = info + 1;
	info->capacity = capacity;
	info->count = 0;
	info->element_size = element_size;
}

void	array_push(void *refvec, void *value)
{
	t_array	*info;

	info = *(t_array **)refvec - 1;
	if (info->count >= info->capacity)
	{
		info->capacity *= 2;
		info = ft_realloc(info, sizeof(t_array) + (info->capacity * info->element_size));
		if (info == NULL)
		{
			// free(info);
			array_free(refvec);
			printf("Error: realloc failed\n");
			exit(1);
		}
		array_free(refvec);
		*(void **)refvec = info + 1;
	}
	memcpy(
		*(char **)refvec + (info->count * info->element_size),
		value,
		info->element_size
	);
	info->count++;
}

// int	main(void)
// {
// 	int		whole_numbers[5];
// 	int		i;
// 	float	*array;
// 	float	num;

// 	// whole_numbers[0] = 0;
// 	vec_init(&array, 5, sizeof(float));
// 	// i = 0;
// 	while (i < 11)
// 	{
// 		num = i + 0.5;
// 		array_push(&array, &num);
// 		i++;
// 	}
// 	// array_clear(&array);
// 	i = 0;
// 	while (i < array_length(&array))
// 	{
// 		printf("%f\n", array[i]);
// 		i++;
// 	}
// 	// array_free(&array);
// 	// array_free(&array);

// 	printf("array_length: %d\n", array_length(&array));
// 	return (0);
// }
