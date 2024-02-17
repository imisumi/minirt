/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:44:47 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/16 20:26:37 by imisumi-wsl      ###   ########.fr       */
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


void	vec_init(void *refvec, uint32_t capacity, size_t element_size);
void	vec_push(void *refvec, void *value);
void	vec_clear(void *refvec);
void	vec_free(void *refvec);
int		vec_length(void *refvec);

#endif