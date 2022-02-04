/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emomkus <emomkus@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:45:09 by emomkus           #+#    #+#             */
/*   Updated: 2022/02/04 22:11:04 by emomkus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

/* Time periods and terms */
typedef struct s_periods
{
	int	die;
	int	eat;
	int	sleep;
}	t_periods;

typedef struct s_philosopher
{
	int				label;
	pthread_t		thread;
	pthread_mutex_t	*mtx_left;
	pthread_mutex_t	*mtx_right;
	t_periods		*time_to;
	long int		*time;
	long int		time_stamp;
	int				*status;
	
}	t_philosopher;

int	main(int argc, char **argv);

/* Additional functions */
int	ft_atoi(const char *str);

#endif