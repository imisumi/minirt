/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:56:34 by ichiro            #+#    #+#             */
/*   Updated: 2023/12/21 11:20:03 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lodepng/lodepng.h"
// #include "lodepng.h"
#include "minirt.h"

void	screenshot(t_data *data)
{
	const int	width = data->mlx->width;
	const int	height = data->mlx->height;

	size_t size = width * height * 4;

	// uint8_t	*image;
	// image = malloc(width * height * 4);
	uint8_t* image = (unsigned char*)malloc(size);

	int i = 0;
	int j = 0;
	j = width * height - 1; // Start from the last pixel
	while (i < size)
	{
		int row = j / width; // Calculate the row
		int col = j % width; // Calculate the column
		
		t_vec4f color = data->utils.accumulated_data[j];
		color /= (float)data->utils.accumulated_frames;
		color = vec3f_tone_map(color);
		
		// Calculate the new index based on the flipped position
		int newIndex = (height - row - 1) * width + col;
		
		image[newIndex * 4] = (uint8_t)(color[X] * 255);
		image[newIndex * 4 + 1] = (uint8_t)(color[Y] * 255);
		image[newIndex * 4 + 2] = (uint8_t)(color[Z] * 255);
		image[newIndex * 4 + 3] = 255;
		
		i += 4;
		j--;
	}
	uint32_t error = lodepng_encode32_file("screenshots/screenshot.png", image, width, height);
	if (error)
		printf("Error %u: %s\n", error, lodepng_error_text(error));
	else
		printf("Image saved as screenshot.png\n");
	free(image);
}
