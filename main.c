/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emomkus <emomkus@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:44:50 by emomkus           #+#    #+#             */
/*   Updated: 2022/02/05 14:43:29 by emomkus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_join(arr[0]->thread, NULL);
	return (0);
}
