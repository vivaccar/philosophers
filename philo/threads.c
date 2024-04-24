/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:46:49 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/24 17:11:49 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	try_eat(t_philo *philo)
{
	hold(philo);
	eating(philo);
	drop(philo);
	pthread_mutex_lock(&philo->philo_mtx);
	philo->meals++;
	if (philo->meals == philo->table->repeat)
	{
		philo->full = 1;
		philo->dead_time = 0;
	}
	pthread_mutex_unlock(&philo->philo_mtx);
	print_status(SLEEP, philo);
	mili_sleep(philo->table->time_to_sleep, philo->table);
	print_status(THINK, philo);
}

void	*routine(void *table)
{
	t_philo			*philo;

	philo = (t_philo *)table;
	wait_threads(philo->table);
	pthread_mutex_lock(&philo->philo_mtx);
	philo->dead_time = philo->table->time_to_die + ft_get_time();
	pthread_mutex_unlock(&philo->philo_mtx);
	print_status(THINK, philo);
	if (philo->id % 2 == 0)
		mili_sleep(20, philo->table);
	while (!is_philo_full(philo) && is_philos_live(philo->table))
		try_eat(philo);
	return (NULL);
}

void	*monitor(void *arg)
{
	t_table	*table;
	int		i;

	i = 0;
	table = (t_table *)arg;
	wait_threads(table);
	while (dinner_running(table))
	{
		if (i == table->n_philos)
			i = 0;
		pthread_mutex_lock(&table->philo[i].philo_mtx);
		if (ft_get_time() >= table->philo[i].dead_time
			&& table->philo[i].dead_time != 0 && !table->philo[i].is_eating)
		{
			print_status("died", &table->philo[i]);
			pthread_mutex_unlock(&table->philo[i].philo_mtx);
			break ;
		}
		pthread_mutex_unlock(&table->philo[i].philo_mtx);
		i++;
	}
	return (NULL);
}

int	create_and_join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		if (pthread_create(&table->philo[i].td,
				NULL, &routine, &table->philo[i]))
			return (error_philo("Error: Thread Create.\n", table));
		i++;
	}
	pthread_mutex_lock(&table->table_mtx);
	table->th_created = 1;
	pthread_mutex_unlock(&table->table_mtx);
	i = 0;
	while (i < table->n_philos)
	{
		if (pthread_join(table->philo[i].td, NULL))
			return (error_philo("Error: Thread Join.\n", table));
		i++;
	}
	return (1);
}

int	start_dinner(t_table *table)
{
	table->start_time = ft_get_time();
	if (table->n_philos == 1)
		return (one_philo(table));
	if (pthread_create(&table->monitor, NULL, &monitor, table))
		return (error_philo("Error: Thread Monitoring.\n", table));
	if (!create_and_join_threads(table))
		return (0);
	end_dinner(table);
	if (pthread_join(table->monitor, NULL))
		return (error_philo("Error: Join Monitoring.\n", table));
	return (1);
}
