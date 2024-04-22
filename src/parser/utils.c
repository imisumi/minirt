/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/04/22 19:29:06 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*str_replace_char(char *str, char find, char replace)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == find)
			str[i] = replace;
		i++;
	}
	return (str);
}

void	ft_split_free(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

size_t	ft_split_count(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

bool	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (true)
	{
		if (s1[i] != s2[i])
			return (false);
		if (s1[i] == '\0' && s2[i] == '\0')
			return (true);
		i++;
	}
}
