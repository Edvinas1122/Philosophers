/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emomkus <emomkus@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:44:50 by emomkus           #+#    #+#             */
/*   Updated: 2022/02/04 22:18:09 by emomkus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		valid_unum_check(char **argv)
{
	/* all cases ? */
	int	i;
	int	x;

	x = 1;
	while (argv[x])
	{
		i = 0;
		while (argv[x][i])
		{
			if (!(argv[x][i] > 47 && argv[x][i] < 58))
				return (0);
			i++;
		}
		x++;
	}
	return (1);
}

void	*philosopher(void *param)
{
	t_philosopher	*data;
	
	data = (t_philosopher *)param;
	while (!(data->status[0]))
	{
		pthread_mutex_lock(data->mtx_left);
		printf("%ld %i has taken a fork\n", *data->time, data->label);
		pthread_mutex_lock(data->mtx_right);
		printf("%ld %i has taken a fork\n", *data->time, data->label);
		usleep(data->time_to->eat);
		printf("%ld %i is eating\n", *data->time, data->label);
		pthread_mutex_unlock(data->mtx_left);
		pthread_mutex_unlock(data->mtx_right);
		data->time_stamp = data->time[0];
		printf("%ld %i is sleeping\n", *data->time, data->label);
		usleep(data->time_to->sleep);
		if ((data->time[0] - data->time_stamp) > data->time_to->die)
		{
			data->status[0] = 1;
			printf("%ld %i died\n", *data->time, data->label);
			pthread_exit(0);
		}
		printf("%ld %i is thinking\n", *data->time, data->label);
	}
	pthread_exit(0);
}

t_periods	*assign_periods(char **argv)
{
	t_periods	*periods;

	periods = malloc(sizeof(t_periods));
	periods->die = 1000 * ft_atoi(argv[2]);
	periods->eat = 1000 * ft_atoi(argv[3]);
	periods->sleep = 1000 * ft_atoi(argv[4]);
	return (periods);
}

t_philosopher	**point_right_mtx(t_philosopher **arr, int argc)
{
	int	i;

	i = 0;
	while (i + 1 < argc)
	{
		arr[i]->mtx_right = arr[i + 1]->mtx_left;
		i++;
	}
	arr[i]->mtx_right = arr[0]->mtx_left;
	return (arr);
}

t_philosopher	**allocate_philosophers(int	argc, t_periods *periods, long int *time, int *status)
{
	t_philosopher	**arr;
	int				i;

	i = 0;
	arr = malloc(sizeof(t_philosopher *) * argc);
	while (i < argc)
	{
		arr[i] = malloc(sizeof(t_philosopher));
		arr[i]->label = i + 1;
		arr[i]->time_to = periods;
		arr[i]->status = status;
		arr[i]->time = time;
		arr[i]->mtx_left = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(arr[i]->mtx_left, NULL);
		i++;
	}
	arr = point_right_mtx(arr, argc);
	return (arr);
}

int	main(int argc, char **argv)
{
	t_periods		*periods;
	t_philosopher	**arr;
	int				ct;
	int				i;
	struct timeval	current_time;
	long int		*time;
	int				*status;

	i = 0;
	ct = ft_atoi(argv[1]);
	if (!valid_unum_check(argv) || argc != 5)
		return (0);
	periods = assign_periods(argv);
	status = malloc(sizeof(int));
	time = malloc(sizeof(long int));
	arr = allocate_philosophers(ct, periods, time, status);
	while (i < ct)
	{
		printf("thread create: %i\n", i);
		pthread_create(&arr[i]->thread, NULL, philosopher, (void *)arr[i]);
		i++;
	}
	while (arr[0]->time)
	{
		gettimeofday(&current_time, NULL);
		*time = current_time.tv_usec;
	}
	printf("thread join: %i\n", i);
	pthread_join(arr[i]->thread, NULL);
	return (0);
}
