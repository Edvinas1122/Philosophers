/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emomkus <emomkus@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:44:50 by emomkus           #+#    #+#             */
/*   Updated: 2022/02/07 14:56:57 by emomkus          ###   ########.fr       */
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
	while (i < ct)
	{
		terminate_one(arr[i]);
		i++;
	}
	free(clock_data->time);
	free(clock_data);
	free(arr);
}

static void	wait_for_dead(t_philosopher **arr, t_thclock *clock_data,
							int ct, int times_to_end)
{
	int			i;
	suseconds_t	stamp;

	i = 0;
	stamp = *clock_data->time;
	usleep(50);
	while (1)
	{
		usleep(5);
		if (i >= ct)
			i = 0;
		if (*clock_data->time - arr[i]->time_stamp >= arr[0]->time_to->die)
		{
			printf("%ld %i died\n", *arr[0]->time, arr[i]->label);
			pthread_mutex_lock(arr[0]->global_stop);
			break ;
		}
		if (times_to_end <= arr[i]->eat_times && times_to_end != -42)
		{
			printf("Finish\n");
			pthread_mutex_lock(arr[0]->global_stop);
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
	clock_data = start_clock_thread(global_stop);
	arr = allocate_philosophers(num_of_philosophers, argv, clock_data->time,
			global_stop);
	start_philosopher_threads(num_of_philosophers, arr);
	if (argc == 6)
		times_to_end = ft_atoi(argv[5]);
	else
		times_to_end = -42;
	wait_for_dead(arr, clock_data, num_of_philosophers, times_to_end);
	usleep(500 + (arr[0]->time_to->eat * 1000)
		+ (arr[0]->time_to->sleep * 1000));
	terminate_all(arr, clock_data, num_of_philosophers);
	printf("Quit\n");
	return (0);
}
