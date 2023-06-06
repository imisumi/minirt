/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:15:44 by imisumi           #+#    #+#             */
/*   Updated: 2022/10/13 10:15:44 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	size_t	m;

	m = n - 1;
	i = 0;
	if (!dest && !src)
		return (0);
	if ((char *)dest < (char *)src)
	{
		while (n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
			n--;
		}
	}
	while (i < n)
	{
		((char *)dest)[m] = ((char *)src)[m];
		i++;
		m--;
	}
	return ((char *) dest);
}
