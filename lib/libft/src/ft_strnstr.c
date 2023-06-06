/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:10:20 by imisumi           #+#    #+#             */
/*   Updated: 2022/11/09 13:24:37 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if ((!haystack || !needle) && len == 0)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *) &haystack[i]);
	while (haystack[i] != '\0' && i < len)
	{
		while (haystack[i + j] == needle[j] && (i + j < len))
		{
			if (needle[j + 1] == '\0' && i + j < len)
				return ((char *) &haystack[i]);
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}
