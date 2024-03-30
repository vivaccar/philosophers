/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:10:03 by vivaccar          #+#    #+#             */
/*   Updated: 2024/03/30 18:15:20 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test(void *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)data;
	i = 0;

	while (i < 10)
	{
		pthread_mutex_lock(&philo->right_fork->mtx);
		pthread_mutex_lock(&philo->left_fork->mtx);
		printf("Philo %i took the fork %i\n", philo->id, philo->right_fork->id);
		printf("Philo %i took the fork %i\n", philo->id, philo->left_fork->id);
		printf("Philo %i is eating\n", philo->id);
		printf("Philo %i drop the fork %i\n", philo->id, philo->right_fork->id);
		printf("Philo %i drop the fork %i\n", philo->id, philo->left_fork->id);
		pthread_mutex_unlock(&philo->right_fork->mtx);
		pthread_mutex_unlock(&philo->left_fork->mtx);
		i++;
	}
	return (NULL);
}

int	init_philos(t_data *data)
{
	int	i;	

	data->fork = malloc(sizeof(t_fork) * data->n_philos);
	if (!data->fork)
		return (error_philo("Error: Fork's malloc error!\n"));
	data->philo = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philo)
		return (error_philo("Error: Philo's malloc error!\n"));
	i = 1;
	while (i <= data->n_philos)
	{
		data->philo[i - 1].id = i;
		data->fork[i - 1].id = i;
		pthread_mutex_init(&data->fork[i - 1].mtx, NULL);
		if (i == data->n_philos)
		{
			data->philo[i - 1].right_fork = &data->fork[i - 1];
			data->philo[i - 1].left_fork = &data->fork[0];
		}
		else
		{
			data->philo[i - 1].right_fork = &data->fork[i - 1];
			data->philo[i - 1].left_fork = &data->fork[i];
		}
		i++;
	}
	i = 1;
	while (i <= data->n_philos)
	{
		pthread_create(&data->philo[i - 1].thread, NULL, &test, (void *)&data->philo[i - 1]);
		i++;
	}
	i = 1;
	while (i <= data->n_philos)
	{
		pthread_join(data->philo[i - 1].thread, NULL);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data			data;

	if (!init_input(ac, av, &data))
		return (0);
	init_philos(&data);
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
	free(data.fork);
}