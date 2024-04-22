/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:19:47 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/22 12:41:45 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->table_mtx);
		if (data->th_created)
		{
			pthread_mutex_unlock(&data->table_mtx);
			break ;
		}
		pthread_mutex_unlock(&data->table_mtx);
		usleep(1);
	}
}

size_t	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL ) == -1)
		write (2, "Error: Gettimeof day.\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t miliseconds)
{
	size_t	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < miliseconds)
		usleep (500);
	return (0);
}

int	error_philo(char *msg, t_data *data)
{
	printf("%s", msg);
	if (data)
		free(data->philo);
	if (data)
		free(data->forks);
	return (0);
}

void	destroy_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].philo_mtx);
		i++;
	}
	pthread_mutex_destroy(&data->table_mtx);
	pthread_mutex_destroy(&data->print_mtx);
	if (data)
		free(data->philo);
	if (data)
		free(data->forks);
}
