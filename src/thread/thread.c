/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi-wsl <imisumi-wsl@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 23:09:09 by ichiro            #+#    #+#             */
/*   Updated: 2024/04/22 21:51:17 by imisumi-wsl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	thread_create(t_thread *threads, t_data *data)
{
	uint32_t		i;
	const uint32_t	step_x = data->utils.width / THREADS;

	i = 0;
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
		if (pthread_create(&threads[i].tid, NULL, render, &threads[i]) != 0)
			return (exit_error(THREAD_CREATE, NULL));
		i++;
	}
}

static void	create_threads(t_data *data)
{
	t_thread	threads[THREADS];
	int			i;

	thread_create(threads, data);
	i = 0;
	while (i < THREADS)
	{
		if (pthread_join(threads[i].tid, NULL) != 0)
			return (exit_error(THREAD_JOIN, NULL));
		i++;
	}
}

bool	render_zone(t_data *data)
{
	t_thread	zone;

	if (data->utils.accumulated_frames == 1)
	{
		ft_memset(data->utils.accumulated_data, 0, sizeof(t_vec4f) * \
			data->utils.width * data->utils.height);
	}
	if (MT)
		create_threads(data);
	else
	{
		zone.x_start = 0;
		zone.x_end = data->utils.width;
		zone.y_start = 0;
		zone.y_end = data->utils.height;
		zone.data = data;
		render(&zone);
	}
	return (true);
}
