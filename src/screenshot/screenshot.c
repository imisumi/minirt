/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:56:34 by ichiro            #+#    #+#             */
/*   Updated: 2024/02/17 16:56:48 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lodepng/lodepng.h"
#include "minirt.h"

void	image_flip_vertical(uint8_t *pixels, int width, int height)
{
	const uint32_t	row_size = width * 4;
	uint8_t			*temp_row;
	int				row;
	int				opposite_row;

	temp_row = malloc(row_size);
	if (!temp_row)
		exit_error(MALLOC, "image_flip_vertical");
	row = 0;
	while (row < height / 2)
	{
		opposite_row = height - 1 - row;
		ft_memcpy(temp_row, pixels + row * row_size, row_size);
		ft_memcpy(pixels + row * row_size, pixels + opposite_row * \
			row_size, row_size);
		ft_memcpy(pixels + opposite_row * row_size, temp_row, row_size);
		row++;
	}
	free(temp_row);
}

static void	write_image(uint8_t *image, t_data *data, const char *path)
{
	uint32_t	error;

	error = lodepng_encode32_file(path, image, \
		data->utils.width, data->utils.height);
	if (error)
		printf("Error %u: %s\n", error, lodepng_error_text(error));
	else
		printf("Image saved as screenshot.png\n");
	free(image);
}

void	screenshot(t_data *data)
{
	const size_t	size = data->utils.width * data->utils.height * 4;
	uint8_t			*image;
	t_vec4f			color;
	int				i;
	int				j;

	image = malloc(size);
	if (!image)
		exit_error(MALLOC, "screenshot");
	i = 0;
	j = 0;
	while (i < size)
	{
		color = data->utils.accumulated_data[j];
		color /= (float)data->utils.accumulated_frames;
		color = vec3f_tone_map(color);
		image[j * 4] = (uint8_t)(color[X] * 255);
		image[j * 4 + 1] = (uint8_t)(color[Y] * 255);
		image[j * 4 + 2] = (uint8_t)(color[Z] * 255);
		image[j * 4 + 3] = 255;
		j++;
		i += 4;
	}
	image_flip_vertical(image, data->utils.width, data->utils.height);
	write_image(image, data, "screenshots/screenshot.png");
}
