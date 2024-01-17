/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:44:47 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/17 04:06:42 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "darray.h"
#include "darray.h"

// https://www.youtube.com/watch?v=Nn_hbAGnBOs&t=1157s
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

// void		*ft_realloc(void *ptr, size_t size)
// {
// 	void	*new_ptr;

// 	if (ptr == NULL)
// 		return (malloc(size));
// 	if (size == 0)
// 		return (ptr);
// 	new_ptr = malloc(size);
// 	if (new_ptr == NULL)
// 		return (NULL);
// 	ft_memset(new_ptr, 0, size);
// 	ft_memcpy(new_ptr, ptr, size);
// 	return (new_ptr);
// }

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;

	if (old_size == new_size)
		return (ptr);
	if (old_size > new_size)
		old_size = new_size;
	new = malloc(new_size);
	// new = NULL;
	if (new == NULL)
		return (NULL);
	if (ptr != NULL)
	{
		ft_memcpy(new, ptr, old_size);
		free(ptr);
	}
	return (new);
}

bool	vec_init(void *refvec, uint32_t capacity, size_t element_size)
{
	t_array	*info;

	info = malloc(sizeof(t_array) + (capacity * element_size));
	if (info == NULL)
	{
		printf("Error: malloc failed vec_init\n");
		return (false);
	}
	*((void**)refvec) = info + 1;
	info->capacity = capacity;
	info->count = 0;
	info->element_size = element_size;
	return (true);
}

bool	array_push(void *refvec, void *value)
{
	t_array	*info;

	info = ((t_array*)(*((void**)refvec))) - 1;
	if (info->count >= info->capacity)
	{
		info->capacity *= 2;
		size_t old_size = sizeof(t_array) + ((info->capacity / 2) * info->element_size);
		size_t new_size = sizeof(t_array) + (info->capacity * info->element_size);
		info = ft_realloc(info, old_size, new_size);
		// info = ft_realloc(info, ((info->capacity / 2) * info->element_size), (info->capacity * info->element_size));
		// info = realloc(info, sizeof(t_array) + (info->capacity * info->element_size));
		if (info == NULL)
		{
			printf("Error: failed to add array element\n");
			return (false);
		}
		*((void**)refvec) = info + 1;
	}
	ft_memcpy(
		(*(char**)refvec + (info->count * info->element_size)),
		value,
		info->element_size
	);
	info->count++;
	return (true);
}
//!!!!!!!!!!!!!!!!!!!!
// bool array_push(void *refvec, void *value)
// {
//     t_array *info = *((t_array **)refvec) - 1;

//     if (info->count >= info->capacity)
//     {
//         info->capacity *= 2;
//         t_array *new_info = ft_realloc(info, sizeof(t_array) + (info->capacity * info->element_size));

//         if (new_info == NULL)
//         {
//             printf("Error: failed to add array element\n");
//             return false;
//         }
// 		array_free(refvec);
//         *(void **)refvec = new_info + 1;
//         info = new_info;
//     }

// 	printf("%p\n", *(void **)refvec);
// 	printf("%p\n", info);
//     ft_memcpy(
//         (char *)(*(void **)refvec) + (info->count * info->element_size),
//         value,
//         info->element_size
//     );
	

//     info->count++;
//     return true;
// }

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





















// bool vec_init(void* _refList, unsigned int _capacity, size_t _element_size)
// bool	vec_init(void *refvec, uint32_t capacity, size_t element_size)
// {
//     t_array* info = malloc( sizeof(t_array) + (capacity * element_size));

//     *((void**)refvec) = info + 1;

//     info->capacity = capacity;
//     info->count = 0;
//     info->element_size = element_size;
// 	return (true);
// }

// void array_free(void* _refList) {
//     t_array* info = *(t_array**)_refList - 1;

//     free(info);
//     *((void**)_refList) = NULL;
// }

// void array_clear(void* _refList) {
//     t_array* info = *(t_array**)_refList - 1;

//     info->count = 0;
// }

// bool array_push(void* refvec, void* value) {
//     t_array* info = ((t_array*)(*((void**)refvec))) - 1;

//     if (info->count >= info->capacity)
//     {
//         info->capacity = info->capacity * 2;

//         info = realloc( info,
//             sizeof(t_array) + (info->capacity * info->element_size)
//         );

//         if (info == NULL)
//         {
//             printf("vec failed to realloc\n");
//         }

//         // if realloc moved the memory then we need to change where the refvec is pointing
//         *((void**)refvec) = info + 1;
//     }

//     memcpy(
//         (*(char**)refvec + (info->count * info->element_size)),
//         value,
//         info->element_size
//     );

//     info->count++;
// 	return true;
// }

// int array_length(void* refvec) {
//     t_array* info = *(t_array**)refvec - 1;

//     return info->count;
// }