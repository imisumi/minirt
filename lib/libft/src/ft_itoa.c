/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:36:41 by imisumi           #+#    #+#             */
/*   Updated: 2022/11/07 13:39:57 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int	len;

	len = 0;
	if (n >= 2147483647)
		return (10);
	if (n <= -2147483648)
		return (11);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n >= 1)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*str_min(void)
{
	char	*max_min;
	char	*min;
	int		i;

	i = 0;
	max_min = "-2147483648";
	min = malloc(ft_strlen(max_min) + 1);
	if (!min)
		return (NULL);
	while (max_min[i] != '\0')
	{
		min[i] = max_min[i];
		i++;
	}
	min[i] = '\0';
	return (min);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	if (n == -2147483648)
		return (str_min());
	len = ft_numlen(n);
	str = malloc(len + 1);
	if (!str)
		return (0);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	str[len] = '\0';
	while (len >= 0 && n != 0)
	{
		str[len - 1] = (n % 10) + 48;
		n = n / 10;
		len--;
	}
	return (str);
}
