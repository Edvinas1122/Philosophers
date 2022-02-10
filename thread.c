/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emomkus <emomkus@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:42:51 by emomkus           #+#    #+#             */
/*   Updated: 2022/02/10 12:51:28 by emomkus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sleeping(t_philosopher *data)
{
	pthread_mutex_lock(data->global_stop);
	pthread_mutex_unlock(data->mtx_left);
	pthread_mutex_unlock(data->mtx_right);
	printf("%ld %i is sleeping\n", *data->time, data->label);
	pthread_mutex_unlock(data->global_stop);
	while (*data->time - data->time_stamp - (data->time_to->eat)
		< data->time_to->sleep)
	{
		usleep(500);
	}
}

static void	eat(t_philosopher *data)
{
	pthread_mutex_lock(data->global_stop);
	data->time_stamp = *data->time;
	printf("%ld %i is eating\n", *data->time, data->label);
	pthread_mutex_unlock(data->global_stop);
	data->eat_times++;
	while (*data->time - data->time_stamp < data->time_to->eat)
	{
		usleep(500);
	}
}

static void	take_fork(t_philosopher	*data)
{
	pthread_mutex_lock(data->global_stop);
	pthread_mutex_unlock(data->global_stop);
	pthread_mutex_lock(data->mtx_left);
	pthread_mutex_lock(data->global_stop);
	printf("%ld %i has taken a fork\n", *data->time, data->label);
	pthread_mutex_unlock(data->global_stop);
	pthread_mutex_lock(data->mtx_right);
	pthread_mutex_lock(data->global_stop);
	printf("%ld %i has taken a fork\n", *data->time, data->label);
	pthread_mutex_unlock(data->global_stop);
}

void	*philosopher(void *param)
{
	t_philosopher	*data;

	data = (t_philosopher *)param;
	data->time_stamp = *data->time;
	while (1)
	{
		take_fork(data);
		eat(data);
		sleeping(data);
		pthread_mutex_lock(data->global_stop);
		printf("%ld %i is thinking\n", *data->time, data->label);
		pthread_mutex_unlock(data->global_stop);
	}
	pthread_exit(0);
}
