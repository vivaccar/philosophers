/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinivaccari <vinivaccari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:19:47 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/23 17:19:28 by vinivaccari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(t_table *table)
{
	while (1)
	{
		pthread_mutex_lock(&table->table_mtx);
		if (table->th_created)
		{
			pthread_mutex_unlock(&table->table_mtx);
			break ;
		}
		pthread_mutex_unlock(&table->table_mtx);
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

void	mili_sleep(size_t miliseconds)
{
	usleep(1000 * miliseconds);
}

int	error_philo(char *msg, t_table *table)
{
	printf("%s", msg);
	if (table)
		free(table->philo);
	if (table)
		free(table->forks);
	return (0);
}

void	destroy_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philo[i].philo_mtx);
		i++;
	}
	pthread_mutex_destroy(&table->table_mtx);
	pthread_mutex_destroy(&table->print_mtx);
	if (table)
		free(table->philo);
	if (table)
		free(table->forks);
}
