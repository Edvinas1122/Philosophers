/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emomkus <emomkus@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:58:26 by emomkus           #+#    #+#             */
/*   Updated: 2022/02/09 18:46:30 by emomkus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_clock(void *param)
{
	t_thclock	*clock_data;
	long int	start_of_program;

	clock_data = (t_thclock *)param;
	gettimeofday(&(clock_data->current_time), NULL);
	start_of_program = (clock_data->current_time.tv_sec * 1000)
		+ (clock_data->current_time.tv_usec / 1000);
	while (1)
	{
		pthread_mutex_lock(clock_data->clock_stop);
		pthread_mutex_unlock(clock_data->clock_stop);
		gettimeofday(&(clock_data->current_time), NULL);
		*(clock_data->time) = ((clock_data->current_time.tv_sec * 1000)
				+ (clock_data->current_time.tv_usec / 1000)) - start_of_program;
		usleep(15);
	}
	return (NULL);
}

/* Start time thread and return pointer to time address*/
t_thclock	*start_clock_thread(void)
{
	t_thclock	*clock_data;

	clock_data = malloc(sizeof(t_thclock));
	clock_data->clock_stop = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(clock_data->clock_stop, NULL);
	clock_data->time = malloc(sizeof(long int));
	pthread_create(&clock_data->th_clock, NULL, ft_clock, (void *)clock_data);
	return (clock_data);
}

/* Delay between each thread start */
static int	delay_selector(int ct)
{
	if (ct < 3)
		return (200);
	else if (ct < 6)
		return (150);
	else if (ct < 9)
		return (90);
	else if (ct < 20)
		return (60);
	else if (ct < 80)
		return (20);
	else
		return (1);
}

/* Start philosopher threads */
void	start_philosopher_threads(int ct, t_philosopher	**arr)
{
	int	i;
	int	delay;

	i = 0;
	delay = delay_selector(ct);
	while (i < ct)
	{
		if ((i % 2) == 0)
		{
			usleep(delay);
			pthread_create(&arr[i]->thread, NULL, philosopher, (void *)arr[i]);
		}
		i++;
	}
	i = 1;
	while (i < ct)
	{
		if ((i % 2) == 1)
		{
			usleep(delay);
			pthread_create(&arr[i]->thread, NULL, philosopher, (void *)arr[i]);
		}
		i++;
	}
}
