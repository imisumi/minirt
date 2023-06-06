/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:41:49 by imisumi           #+#    #+#             */
/*   Updated: 2022/11/09 13:26:51 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = start;
	j = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s) && (size_t)start < ft_strlen(s))
		len = ft_strlen(s) - start;
	if ((size_t)start > ft_strlen(s))
		len = 0;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (ft_strlen(s) > start && j < len)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
