/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:42:26 by imisumi           #+#    #+#             */
/*   Updated: 2022/11/09 10:41:45 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t				i;
	const unsigned char	*src;

	i = 0;
	src = (const unsigned char *) str;
	while (i < n)
	{
		if (*src == (const unsigned char)c)
			return ((unsigned char *) str);
		src++;
		str++;
		i++;
	}
	return (0);
}
