/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinivaccari <vinivaccari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:45:03 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/15 23:45:18 by vinivaccari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks_and_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].meals = 0;
		data->philo[i].full = 0;
		data->philo[i].dead_time = ft_get_time() + data->time_to_die;
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philo[i].philo_mtx, NULL);
		data->philo[i].right_fork = &data->forks[i];
		if (data->n_philos == i + 1)
			data->philo[i].left_fork = &data->forks[0];
		else
			data->philo[i].left_fork = &data->forks[i + 1];
		i++;
	}
	pthread_mutex_init(&data->print_mtx, NULL);
	pthread_mutex_init(&data->table_mtx, NULL);
}

int	init_philos(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
		return (error_philo("Error: Fork's malloc error!\n", data));
	data->threads = malloc(sizeof(pthread_t) * data->n_philos);
	if (!data->threads)
		return (error_philo("Error: Thread's malloc error!\n", data));
	data->philo = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philo)
		return (error_philo("Error: Philo's malloc error!\n", data));
	init_forks_and_mutexes(data);
	return (1);
}
