/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emomkus <emomkus@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:44:50 by emomkus           #+#    #+#             */
/*   Updated: 2022/02/07 19:03:50 by emomkus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	terminate_one(t_philosopher *arr)
{
	free(arr->mtx_left);
	free(arr);
}

void	terminate_all(t_philosopher **arr, t_thclock *clock_data, int ct)
{
	int	i;

	i = 0;
	free(arr[0]->status);
	free(arr[0]->time_to);
	free(arr[0]->global_stop);
	while (i < ct)
	{
		terminate_one(arr[i]);
		i++;
	}
	free(clock_data->time);
	free(clock_data->clock_stop);
	free(clock_data);
	free(arr);
}

static void	lock_all(t_philosopher **arr, t_thclock *clock_data)
{
	pthread_mutex_lock(arr[0]->global_stop);
	usleep(500 + (arr[0]->time_to->eat * 1000)
		+ (arr[0]->time_to->sleep * 1000));
	pthread_mutex_lock(clock_data->clock_stop);
}

static void	wait_for_dead(t_philosopher **arr, t_thclock *clock_data,
							int ct, int times_to_end)
{
	int	i;

	i = 0;
	usleep(50);
	while (1)
	{
		if (i >= ct)
			i = 0;
		if (*clock_data->time - arr[i]->time_stamp >= arr[0]->time_to->die)
		{
			printf("%ld %i died\n", *arr[0]->time, arr[i]->label);
			lock_all(arr, clock_data);
			break ;
		}
		if (times_to_end <= arr[i]->eat_times && times_to_end != -42)
		{
			lock_all(arr, clock_data);
			break ;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philosopher	**arr;
	t_thclock		*clock_data;
	pthread_mutex_t	*global_stop;
	int				num_of_philosophers;
	int				times_to_end;

	if (!(argc < 7 && argc > 4) || !valid_unum_check(argv))
		return (0);
	num_of_philosophers = ft_atoi(argv[1]);
	global_stop = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(global_stop, NULL);
	clock_data = start_clock_thread();
	arr = allocate_philosophers(num_of_philosophers, argv, clock_data->time,
			global_stop);
	start_philosopher_threads(num_of_philosophers, arr);
	if (argc == 6)
		times_to_end = ft_atoi(argv[5]);
	else
		times_to_end = -42;
	wait_for_dead(arr, clock_data, num_of_philosophers, times_to_end);
	usleep(500);
	terminate_all(arr, clock_data, num_of_philosophers);
	return (0);
}
