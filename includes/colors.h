/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:06:12 by ichiro            #+#    #+#             */
/*   Updated: 2023/05/23 16:19:02 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include "struct.h"

# define BRIGHT_RED		-13421569
# define LIGHT_CORAL	-10066177
# define LAVENDER		-1721316097
# define SKY_BLUE		865717503
# define GOLD			-3407617
# define VANILLA		-13057
# define BLACK			255
# define OCEAN_BLUE		3368703
# define ORANGE			-6736897
# define TURQUOISE		869046783
# define TEAL			862349055
# define NAVY_BLUE		13311
# define SILVER			-858993409
# define GREY			-1717986817
# define DARK_GREY		1717987071
# define CHARCOAL		858993663
# define WHITE			-1

// colorpicker.c
uint32_t	current_color(int i);
void		render_color_picker(t_fdf *data);
t_rect		set_rect_value(t_picker p, int x_offset, int y_offset, int first);
void		init_color_picker(t_fdf **d, int x_offset, int y_offset);

// color_picker_2.c
bool		is_color_clicked(t_fdf *data, int x, int y, int i);
void		what_collor_is_clicked_2(t_fdf *data, int x, int y, int button);
void		what_collor_is_clicked(t_fdf **d, int x, int y, int button);

// color_utils.c
int			dif_num(int one, int two);

// color.c
void		fill_background(t_fdf *data);
uint32_t	*get_gradient(int steps, uint32_t c1, uint32_t c2);
int			*lowest_heighest_y(t_fdf *data);
int			heighest_y(t_fdf *data);
void		set_grid_colors(t_fdf **d);

// convert_color.c
int32_t		rgb_to_int32(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint32_t	hexstr_to_int32(char *str);
t_rgb		hex_to_rgb(int hex);
t_rgb		int32_to_rgb(uint32_t pixel_value);

#endif
