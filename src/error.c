/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 01:16:18 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/26 17:39:52 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_error	*error(void)
{
	static t_error	error;

	return (&error);
}

bool	print_error(const char *msg)
{
	const char	*error_strings[ERROR_COUNT] = {
	[NO_ERROR] = "NO_ERROR",
	[STOF] = "String to float error",
	[VEC3_NAN] = "Vec3 is not a number",
	[VEC3_INF] = "Vec3 is infinite",
	[MLX_INIT] = "Mlx init error",
	[MLX_IMG] = "Mlx new image error",
	[MLX_IMG_TO_WIN] = "Mlx image to window error",
	[MAP_INV_TYPE] = "Invalid type in map",
	[MALLOC_BVH] = "Malloc error in bvh",
	};

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
		

	// if (msg && *error() == NO_ERROR)
	// 	printf("%s\n", msg);
	// else
	// 	printf("%s: ", msg);
	// if (*error() != NO_ERROR)
	// 	printf("%s\n", error_strings[*error()]);

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
