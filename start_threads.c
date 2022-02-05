/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emomkus <emomkus@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:58:26 by emomkus           #+#    #+#             */
/*   Updated: 2022/02/05 19:15:40 by emomkus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_clock(void *param)
{
	t_thclock	*clock_data;

	clock_data = (t_thclock *)param;
	while (1)
	{
		gettimeofday(&(clock_data->current_time), NULL);
		*(clock_data->time) = clock_data->current_time.tv_usec;
	}
	return (NULL);
}

/* Start time thread and return pointer to time address*/
t_thclock	*start_clock_thread(void)
{
	t_thclock	*clock_data;

	clock_data = malloc(sizeof(t_thclock));
	clock_data->time = malloc(sizeof(long int));
	pthread_create(&clock_data->th_clock, NULL, ft_clock, (void *)clock_data);
	return (clock_data);
}

/* Start philosopher threads */
void	start_philosopher_threads(int ct, t_philosopher	**arr)
{
	int	i;

	i = 0;
	while (i < ct)
	{
		printf("Thread created: %i\n", i);
		pthread_create(&arr[i]->thread, NULL, philosopher, (void *)arr[i]);
		i++;
	}
}
