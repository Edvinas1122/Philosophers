/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_formation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emomkus <emomkus@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:47:02 by emomkus           #+#    #+#             */
/*   Updated: 2022/02/05 14:08:16 by emomkus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Validating input numbers */
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

/* setting periods of time to die eat and sleep */
static t_periods	*assign_periods(char **argv)
{
	t_periods	*periods;

	periods = malloc(sizeof(t_periods));
	periods->die = 1000 * ft_atoi(argv[2]);
	periods->eat = 1000 * ft_atoi(argv[3]);
	periods->sleep = 1000 * ft_atoi(argv[4]);
	return (periods);
}

/* Assigning common mutex pointers bettween neibgours */
static t_philosopher	**point_right_mtx(t_philosopher **arr, int argc)
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

/* Allocating pointer array for threads */
t_philosopher	**allocate_philosophers(int	argc, char **argv, long int *time)
{
	t_philosopher	**arr;
	t_periods		*periods;
	int				i;
	int				*status;

	i = 0;
	arr = malloc(sizeof(t_philosopher *) * argc);
	periods = assign_periods(argv);
	status = malloc(sizeof(int));
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