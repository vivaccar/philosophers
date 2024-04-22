/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:44:09 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/22 12:49:30 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*only_one(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->right_fork);
	print_status(FORKS, philo);
	pthread_mutex_unlock(philo->right_fork);
	return (NULL);
}

int	one_philo(t_data *data)
{
	if (pthread_create(&data->monitor, NULL, &monitor, data))
		return (error_philo("Error: Monitoring Thread!\n", data));
	if (pthread_create(&data->philo[0].td, NULL, &only_one, &data->philo[0]))
		return (error_philo("Error: Philosophers Threads!\n", data));
	pthread_mutex_lock(&data->table_mtx);
	data->th_created = 1;
	pthread_mutex_unlock(&data->table_mtx);
	if (pthread_join(data->philo[0].td, NULL))
		return (error_philo("Error: Philosophers threads join!\n", data));
	while (1)
	{
		if (!is_philos_live(&data->philo[0]))
			break ;
		usleep(1);
	}
	if (pthread_join(data->monitor, NULL))
		return (error_philo("Error: Monitoring join!\n", data));
	return (1);
}
