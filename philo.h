/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emomkus <emomkus@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:45:09 by emomkus           #+#    #+#             */
/*   Updated: 2022/02/07 14:47:07 by emomkus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

/* Clock thread data */
typedef struct s_thclock
{
	pthread_t		th_clock;
	struct timeval	current_time;
	long int		*time;
	pthread_mutex_t	*global_stop;
}	t_thclock;

/* Time periods and terms */
typedef struct s_periods
{
	int	die;
	int	eat;
	int	sleep;
}	t_periods;

/* Philosopher thread data */
typedef struct s_philosopher
{
	int				label;
	pthread_t		thread;
	pthread_mutex_t	*global_stop;
	pthread_mutex_t	*mtx_left;
	pthread_mutex_t	*mtx_right;
	t_periods		*time_to;
	long int		*time;
	long int		time_stamp;
	int				eat_times;
	int				*status;
}	t_philosopher;

/* Main procedures */
int				main(int argc, char **argv);
t_thclock		*start_clock_thread(pthread_mutex_t *global_stop);
void			start_philosopher_threads(int ct, t_philosopher	**arr);

/* Input formation */
int				valid_unum_check(char **argv);
t_philosopher	**allocate_philosophers(int argc, char **argv,
					long int *time, pthread_mutex_t *global_stop);

/* Thread function */
void			*philosopher(void *param);

/* Additional functions */
int				ft_atoi(const char *str);

#endif