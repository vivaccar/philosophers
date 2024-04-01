/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:10:03 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/01 12:08:15 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test(void *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)data;
	i = 0;

	while (i < 3)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		printf("Philo %i took the fork.\n", philo->id);
		printf("Philo %i took the fork.\n", philo->id);
		printf("Philo %i is eating..\n", philo->id);
		usleep(200 * 1000);
		printf("Philo %i drop the fork.\n", philo->id);
		printf("Philo %i drop the fork.\n", philo->id);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		printf("Philo %i is thinking...\n", philo->id);
		usleep(200 * 1000);
		i++;
	}
	return (NULL);
}

void	deliver_forks(t_data *data)
{
	int	i;

	i = 1;
	while (i <= data->n_philos)
	{
		data->philo[i - 1].id = i;
		pthread_mutex_init(&data->forks[i - 1], NULL);
		data->philo[i - 1].right_fork = &data->forks[i - 1];
		if (data->n_philos == i)
			data->philo[i - 1].left_fork = &data->forks[0];
		else
			data->philo[i - 1].left_fork = &data->forks[i];
		i++;
	}
}

int	init_philos(t_data *data)
{
	int	i;	

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
	i = 1;
	while (i <= data->n_philos)
	{
		pthread_create(&data->threads[i - 1], NULL, &test, (void *)&data->philo[i - 1]);
		i++;
	}
	i = 1;
	while (i <= data->n_philos)
	{
		pthread_join(data->threads[i - 1], NULL);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data			data;

	if (!init_input(ac, av, &data))
		return (0);
	if (!init_philos(&data))
		return (0);
// PRINT ARGS
/* 	printf("Philos: %li\n", data.n_philos);
	printf("Time to die: %li\n", data.time_to_die);
	printf("Time to eat: %li\n", data.time_to_eat);
	printf("Time to sleep: %li\n", data.time_to_sleep);
	printf("Repeat: %li\n", data.repeat); */

// PRINT PHILOS
/* 	int	i = 1;
	while (i <= data.n_philos)
	{
		printf("Philo %i id: %i, Right Fork id: %i, Left Fork id: %i\n", i, data.philo[i - 1].id, data.philo[i - 1].right_fork->id, data.philo[i - 1].left_fork->id);
		i++;
	} */
	free(data.philo);
	free(data.forks);
}