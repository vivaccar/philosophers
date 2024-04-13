/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinivaccari <vinivaccari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:45:03 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/13 22:26:51 by vinivaccari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	deliver_forks(t_data *data)
{
	int	i;

	i = 1;
	while (i <= data->n_philos)
	{
		data->philo[i - 1].id = i;
		data->philo[i - 1].data = data;
		data->philo[i - 1].meals = 0;
		data->philo[i - 1].full = 0;
		data->philo[i - 1].dead_time = ft_get_time() + data->time_to_die;
		pthread_mutex_init(&data->forks[i - 1], NULL);
		pthread_mutex_init(&data->philo[i - 1].philo_mtx, NULL);
		data->philo[i - 1].right_fork = &data->forks[i - 1];
		if (data->n_philos == i)
			data->philo[i - 1].left_fork = &data->forks[0];
		else
			data->philo[i - 1].left_fork = &data->forks[i];
		i++;
	}
	data->th_created = 0;
	pthread_mutex_init(&data->print_mtx, NULL);
	pthread_mutex_init(&data->table_mtx, NULL);
}

int	init_philos(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
		return (error_philo("Error: Fork's malloc error!\n"));
	data->threads = malloc(sizeof(pthread_t) * data->n_philos);
	if (!data->threads)
		return (error_philo("Error: Thread's malloc error!\n"));
	data->philo = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philo)
		return (error_philo("Error: Philo's malloc error!\n"));
	deliver_forks(data);
	return (1);
}