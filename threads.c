/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:46:49 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/10 18:04:26 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->status);
	if (!(ft_strncmp(str, "died", 4)))	
	{
		printf("%zu %i %s\n", ft_get_time() - philo->data->start_time, philo->id, str);
		//philo->data->live = 1;
	}
	else if (philo->data->live && ft_strncmp(str, "died", 4))
		printf("%zu %i %s\n", ft_get_time() - philo->data->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->status);
}

void	*supervisor(void *data)
{
	t_philo	*philo;
	int	flag;
	
	flag = 0;
	philo = (t_philo *)data;
	while (!flag)
	{
		pthread_mutex_lock(&philo->data->data_locker);
		if (philo->data->live)
		{
			pthread_mutex_lock(&philo->p_mtx);
			if (philo->dead_time < ft_get_time() && !philo->is_eating)
			{
				pthread_mutex_lock(&philo->data->data_locker);
				philo->data->live = 0;
				pthread_mutex_unlock(&philo->data->data_locker);
				print_status("died", philo);
				flag = 1;
			}
			pthread_mutex_unlock(&philo->p_mtx);
		}
		pthread_mutex_unlock(&philo->data->data_locker);	
	}
	return (NULL);
}

void eating(t_philo *philo)
{
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

	if (philo->data->n_philos == 1)
	{
		first_fork = &philo->data->forks[0];
		second_fork = &philo->data->forks[0];
	}
 	else if (philo->id % 2 == 0)
	{
        first_fork = philo->left_fork;
        second_fork = philo->right_fork;
    }
	else 
	{
        first_fork = philo->right_fork;
        second_fork = philo->left_fork;
    }
    pthread_mutex_lock(first_fork);
    print_status(FORKS, philo);
    pthread_mutex_lock(second_fork);
    print_status(FORKS, philo);
	pthread_mutex_lock(&philo->p_mtx);
    print_status(EAT, philo);
    philo->dead_time = ft_get_time() + philo->data->time_to_die;
    philo->is_eating = 1;
    ft_usleep(philo->data->time_to_eat);
    philo->is_eating = 0;
    pthread_mutex_unlock(second_fork);
    pthread_mutex_unlock(first_fork);
    philo->meals++;
	pthread_mutex_unlock(&philo->p_mtx);
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
	if (pthread_create(&philo->td, NULL, &supervisor, philo))
	{
		error_philo("Error: Thread supervisor!\n");
		return (NULL);
	}
	pthread_mutex_lock(&philo->p_mtx);
	philo->dead_time = ft_get_time() + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->p_mtx);
	while (philo->data->live)
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

int	one_philo(t_data *data)
{
	if (pthread_create(&data->threads[0], NULL, &routine, &data->philo[0]))
		return (error_philo("Error: Thread Create!\n"));
	pthread_detach(data->threads[0]);
	while (data->live)
		ft_usleep(1);
	return (1);
}

int	start_dinner(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = ft_get_time();
	if (data->n_philos == 1)
		return (one_philo(data));
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