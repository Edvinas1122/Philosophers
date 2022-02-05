/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emomkus <emomkus@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:42:51 by emomkus           #+#    #+#             */
/*   Updated: 2022/02/05 15:03:17 by emomkus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

		if ((data->time[0] - data->time_stamp) > data->time_to->die)
		{
			data->status[0] = 1;
			printf("%ld %i died\n", *data->time, data->label);
			pthread_mutex_unlock(data->mtx_left);
			pthread_mutex_unlock(data->mtx_right);
			pthread_exit(0);
		}



void	*philosopher(void *param)
{
	t_philosopher	*data;
	
	data = (t_philosopher *)param;
	data->time_stamp = data->time[0];
	while (!(data->status[0]))
	{
		pthread_mutex_lock(data->mtx_left);
		printf("%ld %i has taken a fork\n", *data->time, data->label);
		pthread_mutex_lock(data->mtx_right);
		printf("%ld %i has taken a fork\n", *data->time, data->label);
		data->time_stamp = data->time[0];
		usleep(data->time_to->eat);
		printf("%ld %i is eating\n", *data->time, data->label);
		pthread_mutex_unlock(data->mtx_left);
		pthread_mutex_unlock(data->mtx_right);
		printf("%ld %i is sleeping\n", *data->time, data->label);
		usleep(data->time_to->sleep);
		printf("%ld %i is thinking\n", *data->time, data->label);
	}
	pthread_exit(0);
}