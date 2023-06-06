/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichiro <ichiro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:10:54 by imisumi           #+#    #+#             */
/*   Updated: 2023/06/06 23:57:03 by ichiro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	key_hook(mlx_key_data_t key, void *param)
{
	t_fdf	*data;

	data = param;
	key.key = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->mlx);
		exit(EXIT_SUCCESS);
	}
}
