/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/03/08 01:58:08 by imisumi-wsl      ###   ########.fr       */
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

bool	parse_vec3(char *line, t_vec3f *vec)
{
	char	**split;

	split = ft_split(line, ',');
	if (split == NULL)
		return (false);
	if (ft_split_count(split) != 3)
		return (ft_split_free(split), false);
	if (ft_stof(split[0], &vec[0][X]) == false)
		return (ft_split_free(split), false);
	if (ft_stof(split[1], &vec[0][Y]) == false)
		return (ft_split_free(split), false);
	if (ft_stof(split[2], &vec[0][Z]) == false)
		return (ft_split_free(split), false);
	if (isinf(vec[0][X]) || isinf(vec[0][Y]) || isinf(vec[0][Z]))
	{
		*error() = VEC3_INF;
		return (ft_split_free(split), false);
	}
	if (isnan(vec[0][X]) || isnan(vec[0][Y]) || isnan(vec[0][Z]))
	{
		*error() = VEC3_NAN;
		return (ft_split_free(split), false);
	}
	return (ft_split_free(split), true);
}

bool	parse_vec3_normal(char *line, t_vec3f *vec)
{
	int	i;

	if (parse_vec3(line, vec) == false)
		return (false);
	i = 0;
	while (i < 3)
	{
		if (vec[0][i] < -1.0f || vec[0][i] > 1.0f)
		{
			return (false);
		}
		i++;
	}
	*vec = vec3f_normalize(*vec);
	return (true);
}

bool	parse_8bit_color(char *line, t_vec3f *col)
{
	int		i;
	int		rgb;
	char	**split;

	split = ft_split(line, ',');
	if (split == NULL)
		return (false);
	if (ft_split_count(split) != 3)
		return (ft_split_free(split), false);
	i = 0;
	rgb = -1;
	while (i < 3)
	{
		if (ft_stoi(split[i], &rgb) == false)
			return (ft_split_free(split), false);
		if (rgb < 0 || rgb > 255)
			return (ft_split_free(split), false);
		col[0][i] = rgb / 255.0f;
		i++;
	}
	return (ft_split_free(split), true);
}
