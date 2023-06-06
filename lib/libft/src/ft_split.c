/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:08:37 by imisumi           #+#    #+#             */
/*   Updated: 2022/11/09 13:26:17 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	arg_len(char const *s, char c)
{
	size_t	i;
	size_t	arg_count;

	arg_count = 1;
	i = 0;
	if (s[0] == '\0')
		return (arg_count - 1);
	if (s[0] == c)
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			return (arg_count - 1);
	}
	while (s[i] != '\0')
	{
		if ((s[i] == c) && (s[i + 1] != c) && (s[i + 1] != '\0'))
			arg_count++;
		i++;
	}
	return (arg_count);
}

static char	*mall_cpy(char *str, char c)
{
	int		i;
	char	*array;

	i = 0;
	array = 0;
	while (str[i] == c)
		i++;
	while (str[i] && str[i] != c)
		i++;
	array = (char *)malloc(sizeof(char) * (i + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		array[i] = str[i];
		i++;
	}
	array[i] = '\0';
	return (array);
}

static char	**free_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		strings;
	char	**array;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	strings = arg_len((char *)s, c);
	array = ft_calloc(sizeof(char *), strings + 1);
	if (!array)
		return (NULL);
	while (i < strings)
	{
		while (s[0] == c)
			s++;
		array[j] = mall_cpy((char *)s, c);
		if (!array[j])
			return (free_free(array));
		j++;
		s = s + ft_strlen(array[i]);
		i++;
	}
	return (array);
}
