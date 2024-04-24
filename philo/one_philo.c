/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:44:09 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/24 17:12:31 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*only_one(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_status(THINK, philo);
	pthread_mutex_lock(philo->right_fork);
	print_status(FORKS, philo);
	pthread_mutex_unlock(philo->right_fork);
	return (NULL);
}

int	one_philo(t_table *table)
{
	table->start_time = ft_get_time();
	if (pthread_create(&table->monitor, NULL, &monitor, table))
		return (error_philo("Error: Monitoring Thread!\n", table));
	if (pthread_create(&table->philo[0].td, NULL, &only_one, &table->philo[0]))
		return (error_philo("Error: Philosophers Threads!\n", table));
	pthread_mutex_lock(&table->table_mtx);
	table->th_created = 1;
	pthread_mutex_unlock(&table->table_mtx);
	if (pthread_join(table->philo[0].td, NULL))
		return (error_philo("Error: Philosophers threads join!\n", table));
	while (1)
	{
		if (!is_philos_live(table))
			break ;
		usleep(1);
	}
	if (pthread_join(table->monitor, NULL))
		return (error_philo("Error: Monitoring join!\n", table));
	return (1);
}
