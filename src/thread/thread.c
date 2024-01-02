/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 23:09:09 by ichiro            #+#    #+#             */
/*   Updated: 2024/01/02 15:22:49 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	create_thread(t_data *data)
{
	t_thread	threads[THREADS];
	uint32_t	step_x;
	int			i;

	i = 0;
	step_x = data->utils.width / THREADS;
	while (i < THREADS)
	{
		threads[i].x_start = i * step_x;
		threads[i].x_end = (i + 1) * step_x;
		if (i == THREADS - 1)
			threads[i].x_end = data->utils.width;
		threads[i].y_start = 0;
		threads[i].y_end = data->utils.height;
		threads[i].data = data;
		threads[i].index = i;
		pthread_create(&threads[i].tid, NULL, render, &threads[i]);
		i++;
	}
	// i = -1;
	// while (i++ < THREADS)
	// 	pthread_join(threads[i].tid, NULL);
	i = 0;
	while (i < THREADS)
	{
		pthread_join(threads[i].tid, NULL);
		i++;
	}
	return (true);
}
