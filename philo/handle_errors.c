/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:52:20 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/24 19:20:48 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fork_mutex_error(t_table *table, int n)
{
	int	i;

	i = 0;
	while (i <= n)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	return (0);
}

int	philo_mutex_error(t_table *table, int n)
{
	int	i;

	i = 0;
	fork_mutex_error(table, table->n_philos - 1);
	while (i <= n)
	{
		pthread_mutex_destroy(&table->philo[i].philo_mtx);
		i++;
	}
	return (0);
}

int	table_mutex_error(t_table *table, int flag)
{
	philo_mutex_error(table, table->n_philos - 1);
	if (flag == 1 || flag == 2)
		pthread_mutex_destroy(&table->table_mtx);
	if (flag == 2)
		pthread_mutex_destroy(&table->print_mtx);
	return (0);
}

int	thread_error(t_table *table)
{
	pthread_mutex_lock(&table->table_mtx);
	table->thread_error = 1;
	pthread_mutex_unlock(&table->table_mtx);
	return (error_philo("Error: Thread Create.\n", table));
}
