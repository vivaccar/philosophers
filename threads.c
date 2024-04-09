/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:46:49 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/09 14:47:12 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->status);
	if (!(ft_strncmp(str, "died", 4)))	
		printf("%zu %i %s\n", ft_get_time() - philo->data->start_time, philo->id, str);
	else if (philo->data->live && ft_strncmp(str, "died", 4))
		printf("%zu %i %s\n", ft_get_time() - philo->data->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->status);
}

void	*supervisor(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->data->live && philo->data->repeat != philo->meals)
	{
		if (philo->dead_time < ft_get_time() && !philo->is_eating)
		{
			philo->data->live = 0;
			print_status("died", philo);
		}
	}
	return (NULL);
}
void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_status(FORKS, philo);
	pthread_mutex_lock(philo->left_fork);
	print_status(FORKS, philo);
	print_status(EAT, philo);
	philo->dead_time = ft_get_time() + philo->data->time_to_die;
	philo->is_eating = 1;
	ft_usleep(philo->data->time_to_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	philo->meals++;
}

void	sleep_and_think(t_philo *philo)
{
	print_status(SLEEP, philo);
	ft_usleep(philo->data->time_to_sleep);
	print_status(THINK, philo);
}

void	*routine(void *data)
{
	t_philo	*philo;
	int		i;
	
	philo = (t_philo *)data;
	i = 0;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	if (pthread_create(&philo->td, NULL, &supervisor, philo))
	{
		error_philo("Error: Thread supervisor!\n");
		return (NULL);
	}
	philo->dead_time = ft_get_time() + philo->data->time_to_die;
	while (philo->data->live && philo->meals != philo->data->repeat)
	{
		eating(philo);
		if (philo->meals != philo->data->repeat)
			sleep_and_think(philo);
	}
	if (pthread_join(philo->td, NULL))
	{
		error_philo("Error: Thread supervisor!\n");
		return (NULL);
	}
	return (NULL);
}

int	start_dinner(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = ft_get_time();
	while (i < data->n_philos)
	{
		if (pthread_create(&data->threads[i], NULL, &routine, &data->philo[i]))
			return (error_philo("Error: Thread Create.\n"));
		i++;
	}
	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_join(data->threads[i], NULL))
			return (error_philo("Error: Thread Join.\n"));
		i++;
	}
	return (1);
}