/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emomkus <emomkus@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:27:30 by emomkus           #+#    #+#             */
/*   Updated: 2022/02/11 07:01:55 by emomkus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	terminate_one(t_philosopher *arr)
{
	free(arr->mtx_left);
	free(arr);
}

void	terminate_all(t_philosopher **arr, t_thclock *clock_data, int ct)
{
	int	i;

	i = 0;
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
