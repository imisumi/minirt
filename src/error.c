/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:16:18 by ichiro            #+#    #+#             */
/*   Updated: 2024/05/02 11:06:52 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_error	*error(void)
{
	static t_error	error = NO_ERROR;

	return (&error);
}

static void	write_error(const char *error_strings[], const char *msg)
{
	if (*error() == NO_ERROR)
	{
		if (msg)
			printf("%s\n", msg);
	}
	else
	{
		if (msg)
			printf("%s: %s\n", msg, error_strings[*error()]);
		else
			printf("%s\n", error_strings[*error()]);
	}
}

bool	print_error(const char *msg)
{
	const char	*error_strings[ERROR_COUNT] = {
	[NO_ERROR] = "NO_ERROR", [STOF] = "String to float error",
	[VEC3_NAN] = "Vec3 is not a number", [VEC3_INF] = "Vec3 is infinite",
	[MLX_INIT] = "Mlx init error", [MLX_IMG] = "Mlx new image error",
	[MLX_IMG_TO_WIN] = "Mlx image to window error",
	[MAP_INV_TYPE] = "Invalid type in map",
	[MALLOC_BVH] = "Malloc error in bvh", [MALLOC] = "Malloc failure",
	[THREAD_CREATE] = "Thread creation error",
	[THREAD_JOIN] = "Thread join error",
	[TEXTURE_LOAD] = "Texture load error",
	[OBJ_LOAD] = "Obj load error",
	[ARGC] = "Invalid number of arguments, expected: ./miniRT <scene.rt>",
	[FILE_EXT] = "Invalid file extension, expected: .rt",
	};

	write_error(error_strings, msg);
	return (false);
}

bool	print_warning(const char *msg)
{
	printf("Warning: %s\n", msg);
	return (true);
}

void	exit_error(t_error type, const char *msg)
{
	*error() = type;
	print_error(msg);
	exit(type);
}
