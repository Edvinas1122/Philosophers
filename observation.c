/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emomkus <emomkus@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 10:49:19 by emomkus           #+#    #+#             */
/*   Updated: 2022/02/06 19:08:43 by emomkus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_thread
{
	pthread_mutex_t	*mtx;
	struct timeval	current_time;
	int				i;
}	t_thread;

/*threadid, threadattr, runner, runnerparameters */

void	*runner(void *param)
{
	t_thread	*data = (t_thread *)param;
	long int time;
	// pthread_mutex_lock(data->mtx);
	while (1)
	{
		gettimeofday(&(data->current_time), NULL);
		time = ((data->current_time.tv_sec * 1000) + (data->current_time.tv_usec / 1000));
		data->i++;
		sleep(1);
		printf("The 1st thread= %li\n", time);
	}
	// pthread_mutex_unlock(data->mtx);
	// pthread_exit(0);
}

// void	*runner2(void *param)
// {
// 	t_thread	*data = (t_thread *)param;

// 	usleep(1000000);
// 	pthread_mutex_lock(data->mtx);
// 	data->i++;
// 	printf("The 2nd thread= %i\n", data->i);
// 	pthread_mutex_unlock(data->mtx);
// 	pthread_exit(0);
// }

int	main(void)
{
	pthread_t		tid;
	// pthread_t		tid2;
	t_thread		data;
	char			*c;

	c = calloc(sizeof(char), 2);
	c[0] = 'a';
	tid = malloc(sizeof(pthread_t));
	data.i = 0;
	data.mtx = malloc(sizeof(pthread_mutex_t));
	gettimeofday(&(data.current_time), NULL);
	pthread_mutex_init(data.mtx, NULL);
	pthread_create(&tid, NULL, runner, (void *)&data);
	// pthread_create(&tid2, NULL, runner2, (void *)&data);
	sleep(7);
	// pthread_join(tid2, NULL);
	// free(tid);
	return (0);
}
