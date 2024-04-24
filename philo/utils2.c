/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:42:19 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/24 17:11:30 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_dinner(t_table *table)
{
	pthread_mutex_lock(&table->table_mtx);
	table->dinner_running = 0;
	pthread_mutex_unlock(&table->table_mtx);
}

int	dinner_running(t_table *table)
{
	int	dinner;

	pthread_mutex_lock(&table->table_mtx);
	if (table->dinner_running == 0)
		dinner = 0;
	else
		dinner = 1;
	pthread_mutex_unlock(&table->table_mtx);
	return (dinner);
}

int	is_philo_full(t_philo *philo)
{
	int	full_signal;

	pthread_mutex_lock(&philo->philo_mtx);
	if (philo->full)
		full_signal = 1;
	else
		full_signal = 0;
	pthread_mutex_unlock(&philo->philo_mtx);
	return (full_signal);
}

int	is_philos_live(t_table *table)
{
	int	dead_signal;

	pthread_mutex_lock(&table->table_mtx);
	if (!table->live)
		dead_signal = 0;
	else
		dead_signal = 1;
	pthread_mutex_unlock(&table->table_mtx);
	return (dead_signal);
}

void	print_status(char *str, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->table->print_mtx);
	if (!ft_strncmp(str, "died", 4) && is_philos_live(philo->table))
	{
		pthread_mutex_lock(&philo->table->table_mtx);
		time = ft_get_time() - philo->table->start_time;
		printf("%zu %i %s\n", time, philo->id, str);
		philo->table->live = 0;
		pthread_mutex_unlock(&philo->table->table_mtx);
	}
	else if (is_philos_live(philo->table))
	{
		time = ft_get_time() - philo->table->start_time;
		printf("%zu %i %s\n", time, philo->id, str);
	}
	pthread_mutex_unlock(&philo->table->print_mtx);
}
