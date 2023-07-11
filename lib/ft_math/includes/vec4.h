/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:29:15 by ichiro            #+#    #+#             */
/*   Updated: 2023/07/11 02:28:13 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC4_H
# define VEC4_H

# include "struct.h"
# include <math.h>

// vec4
t_vec4 vec4_clamp(t_vec4 v, float min, float max);
t_vec4 vec4_normalize(t_vec4 v);
t_vec4 vec4_div_float(t_vec4 v, float t);
t_vec4 vec4_add(t_vec4 a, t_vec4 b);
t_vec4 vec4_mul(t_vec4 a, t_vec4 b);



#endif // VEC4_H