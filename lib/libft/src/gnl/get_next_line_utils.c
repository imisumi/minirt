/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:02:09 by imisumi           #+#    #+#             */
/*   Updated: 2023/01/31 13:04:34 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strdup(char *s)
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = malloc(sizeof(char) * gnl_strlen(s) + 1);
	if (!dup)
		return (NULL);
	dup[0] = '\0';
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;

	i = -1;
	j = 0;
	s1_len = gnl_strlen(s1);
	s2_len = gnl_strlen(s2);
	if (s1_len + s2_len == 0)
		return (NULL);
	str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (free(s1), str);
}

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	s_len;
	char	*str;

	s_len = gnl_strlen(s);
	i = start;
	j = 0;
	if (!s)
		return (0);
	if (len > s_len && (size_t)start < s_len)
		len = s_len - start;
	if ((size_t)start > s_len)
		len = 0;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s_len > start && j < len)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*gnl_strchr(const char *s, int c)
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
