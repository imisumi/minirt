/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:38:07 by imisumi           #+#    #+#             */
/*   Updated: 2022/11/09 13:26:38 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if ((char)c == '\0')
	{
		while (s[i] != '\0')
			i++;
		return ((char *) s + i);
	}
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *) s + i);
		i++;
	}
	return (NULL);
}
