/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_to_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:29:56 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/16 21:36:49 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	ft_stof2(const char *s, float *res, float *fact)
{
	int	point_seen;
	int	i;

	point_seen = 0;
	while (*s)
	{
		if (*s == '.')
			point_seen++;
		else
		{
			i = *s - '0';
			if (i >= 0 && i <= 9)
			{
				if (point_seen)
					*fact /= 10.0f;
				*res = *res * 10.0f + (float)i;
			}
			else
				return (false);
		}
		s++;
	}
	return (true);
}

// https://stackoverflow.com/questions/4392665/
// converting-string-to-float-without-atof-in-c
bool	ft_stof(const char *s, float *f)
{
	float	fact;

	fact = 1;
	*f = 0.0f;
	if (*s == '-')
	{
		s++;
		fact = -1;
	}
	if (ft_stof2(s, f, &fact) == false)
	{
		*error() = STOF;
		return (false);
	}
	*f *= fact;
	return (true);
}

bool	ft_stoi(const char *s, int *i)
{
	int	fact;

	fact = 1;
	*i = 0;
	if (*s == '-')
	{
		s++;
		fact = -1;
	}
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			*i = *i * 10 + (*s - '0');
		else
			return (false);
		s++;
	}
	*i *= fact;
	return (true);
}
