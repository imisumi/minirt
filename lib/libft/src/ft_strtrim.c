/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:39:32 by imisumi           #+#    #+#             */
/*   Updated: 2022/11/09 13:24:08 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	start_str(char const *s1, char const *set, size_t start, size_t stp)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (start < ft_strlen(s1) && stp != 1)
	{
		i = 0;
		while (i < ft_strlen(set))
		{
			if (i == (ft_strlen(set) - 1) && (s1[j] != set[i]))
			{
				stp = 1;
				break ;
			}
			if (s1[j] == set[i])
			{
				start++;
				break ;
			}
			i++;
		}
		j++;
	}
	return (start);
}

static int	end_str(char const *s1, char const *set, size_t end, size_t stop)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(s1) - 1;
	while (end > 0 && stop != 1)
	{
		i = 0;
		while (i < ft_strlen(set))
		{
			if (i == (ft_strlen(set) - 1) && (s1[j] != set[i]))
			{
				stop = 1;
				break ;
			}
			if (s1[j] == set[i])
			{
				end--;
				break ;
			}
			i++;
		}
		j--;
	}
	return (end);
}

static char	*final_str(size_t start, size_t end, char const *s1)
{
	size_t	i;
	char	*str;

	i = 0;
	str = malloc(((end - start) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (start < end)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	stop;
	size_t	end;

	start = 0;
	stop = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	if (set[0] != '\0')
		start = start_str(s1, set, start, stop);
	if (start != end && set[0] != '\0')
		end = end_str(s1, set, end, stop);
	return (final_str(start, end, s1));
}
