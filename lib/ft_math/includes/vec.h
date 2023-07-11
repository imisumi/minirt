/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:29:15 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/17 01:09:04 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include "struct.h"
# include "math.h"

// vec
t_vec2 vec2_fill(float f);

t_vec3 vec3_fill(float f);

t_vec4 vec4_fill(float f);

t_vec2	vec2_create(float x, float y);
t_vec3	vec3_create(float x, float y, float z);
t_vec4	vec4_create(float x, float y, float z, float w);

#endif // VEC_H