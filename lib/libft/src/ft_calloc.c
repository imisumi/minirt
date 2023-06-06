/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:15:44 by imisumi           #+#    #+#             */
/*   Updated: 2022/11/09 10:39:20 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*a;

	a = malloc(nmemb * size);
	if (!a)
		return (NULL);
	if (a != NULL)
		ft_bzero(a, nmemb * size);
	return (a);
}
