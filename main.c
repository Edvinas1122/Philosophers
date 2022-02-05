/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emomkus <emomkus@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:44:50 by emomkus           #+#    #+#             */
/*   Updated: 2022/02/05 19:29:12 by emomkus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_for_dead(t_philosopher **arr, t_thclock *clock_data, int ct)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i > ct)
			i = 0;
		if(*clock_data->time - arr[0]->time_stamp > arr[0]->time_to->die)
		{
			printf("%ld %i died\n", *arr[0]->time, arr[0]->label);
			pthread_mutex_lock(arr[0]->global_stop);
			break;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philosopher	**arr;
	t_thclock		*clock_data;
	int				num_of_philosophers;

	num_of_philosophers = ft_atoi(argv[1]);
	if (!valid_unum_check(argv) || argc != 5)
		return (0);
	clock_data = start_clock_thread();
	arr = allocate_philosophers(num_of_philosophers, argv, clock_data->time);
	start_philosopher_threads(num_of_philosophers, arr);
	wait_for_dead(arr, clock_data, num_of_philosophers);
	sleep(1);
	printf("free Here\n");
	sleep(10);
	return (0);
}
