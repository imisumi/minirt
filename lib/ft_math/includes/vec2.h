/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:29:15 by ichiro            #+#    #+#             */
/*   Updated: 2023/06/25 23:38:22 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2_H
# define VEC2_H

# include "struct.h"
# include <math.h>

// vec2
t_vec2	vec2_add(t_vec2 a, t_vec2 b);
t_vec2	vec2_add_float(t_vec2 a, float f);

t_vec2	vec2_sub(t_vec2 a, t_vec2 b);
t_vec2	vec2_sub_float(t_vec2 a, float f);

t_vec2	vec2_mul(t_vec2 a, t_vec2 b);
t_vec2	vec2_mul_float(t_vec2 a, float f);

#endif // VEC2_H