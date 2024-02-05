/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 23:56:35 by marvin            #+#    #+#             */
/*   Updated: 2022/10/08 23:56:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	*ft_memcpy(void *dest, const void *src, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!dest && !src)
// 		return (0);
// 	while (i < n)
// 	{
// 		((char *)dest)[i] = ((char *)src)[i];
// 		i++;
// 	}
// 	return (dest);
// }

void *ft_memcpy(void *dest, const void *src, size_t n) {
    size_t i;

    if (!dest || !src) {
        return NULL; // Return NULL if either dest or src is null
    }

    if (n == 0) {
        return dest; // Nothing to copy
    }

    unsigned char *d = dest;
    const unsigned char *s = src;

    for (i = 0; i < n; i++) {
        d[i] = s[i];
    }

    return dest;
}
