/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:44:47 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/05 21:32:44 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DARRAY_H
# define DARRAY_H

# include "libft.h"

# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>


bool	vec_init(void *refvec, uint32_t capacity, size_t element_size);
bool	array_push(void *refvec, void *value);
void	array_clear(void *refvec);
void	array_free(void *refvec);
int		array_length(void *refvec);

#endif