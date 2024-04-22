/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:46:49 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/22 12:48:52 by vivaccar         ###   ########.fr       */
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
	if (philo->meals == philo->data->repeat)
	{
		philo->full = 1;
		philo->dead_time = 0;
	}
	pthread_mutex_unlock(&philo->philo_mtx);
	print_status(SLEEP, philo);
	ft_usleep(philo->data->time_to_sleep);
	print_status(THINK, philo);
}

void	*routine(void *data)
{
	t_philo			*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->philo_mtx);
	philo->dead_time = philo->data->time_to_die + ft_get_time();
	pthread_mutex_unlock(&philo->philo_mtx);
	if (philo->id % 2 == 0)
		ft_usleep(2);
	while (!is_philo_full(philo) && is_philos_live(philo))
		try_eat(philo);
	return (NULL);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	wait_threads(data);
	while (dinner_running(data))
	{
		if (i == data->n_philos)
			i = 0;
		pthread_mutex_lock(&data->philo[i].philo_mtx);
		if (ft_get_time() >= data->philo[i].dead_time
			&& data->philo[i].dead_time != 0)
		{
			print_status("died", &data->philo[i]);
			pthread_mutex_unlock(&data->philo[i].philo_mtx);
			break ;
		}
		pthread_mutex_unlock(&data->philo[i].philo_mtx);
		i++;
	}
	return (NULL);
}

int	create_and_join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_create(&data->philo[i].td, NULL, &routine, &data->philo[i]))
			return (error_philo("Error: Thread Create.\n", data));
		i++;
	}
	pthread_mutex_lock(&data->table_mtx);
	data->th_created = 1;
	pthread_mutex_unlock(&data->table_mtx);
	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_join(data->philo[i].td, NULL))
			return (error_philo("Error: Thread Join.\n", data));
		i++;
	}
	return (1);
}

int	start_dinner(t_data *data)
{
	data->start_time = ft_get_time();
	if (data->n_philos == 1)
		return (one_philo(data));
	if (pthread_create(&data->monitor, NULL, &monitor, data))
		return (error_philo("Error: Thread Monitoring.\n", data));
	if (!create_and_join_threads(data))
		return (0);
	end_dinner(data);
	if (pthread_join(data->monitor, NULL))
		return (error_philo("Error: Join Monitoring.\n", data));
	return (1);
}
