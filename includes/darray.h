/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 00:44:47 by ichiro            #+#    #+#             */
/*   Updated: 2023/12/09 00:40:04 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DARRAY_H
# define DARRAY_H

# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>


void	vec_init(void *refvec, uint32_t capacity, size_t element_size);
void	array_push(void *refvec, void *value);
void	array_clear(void *refvec);
void	array_free(void *refvec);
int		array_length(void *refvec);

#endif