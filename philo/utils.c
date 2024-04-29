/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:19:47 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/24 19:26:25 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wait_threads(t_table *table)
{
	while (1)
	{
		pthread_mutex_lock(&table->table_mtx);
		if (table->thread_error)
			return (0);
		if (table->th_created)
		{
			pthread_mutex_unlock(&table->table_mtx);
			break ;
		}
		pthread_mutex_unlock(&table->table_mtx);
		usleep(1);
	}
	return (1);
}

size_t	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL ) == -1)
		write (2, "Error: Gettimeof day.\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	mili_sleep(size_t milliseconds, t_table *table)
{
	size_t	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < milliseconds && is_philos_live(table))
		usleep(500);
	return ;
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
	free(table->philo);
	free(table->forks);
}
