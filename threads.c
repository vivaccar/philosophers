/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:46:49 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/12 16:52:23 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->status);
	if (!ft_strncmp(str, "died", 4) && is_philos_live(philo))	
	{
		pthread_mutex_lock(&philo->data->died_mtx);
		printf("%zu %i %s\n", ft_get_time() - philo->data->start_time, philo->id, str);
		philo->data->live = 0;
		pthread_mutex_unlock(&philo->data->died_mtx);
	}
	else if (is_philos_live(philo))
		printf("%zu %i %s\n", ft_get_time() - philo->data->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->status);
}

int	is_philo_full(t_philo *philo)
{
	int	full_signal;

	pthread_mutex_lock(&philo->full_mtx);
	if (philo->full)
		full_signal = 1;
	else
		full_signal = 0;
	pthread_mutex_unlock(&philo->full_mtx);
	return (full_signal);
}

int	is_philos_live(t_philo *philo)
{
	int	dead_signal;	

	pthread_mutex_lock(&philo->data->died_mtx);
	if (!philo->data->live)
		dead_signal = 0;
	else
		dead_signal = 1;
	pthread_mutex_unlock(&philo->data->died_mtx);
	return (dead_signal); 
}

void	*check_if_died(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!is_philo_full(philo) && is_philos_live(philo))
	{
		pthread_mutex_lock(&philo->p_mtx);
		if (ft_get_time() > philo->dead_time)
				print_status("died", philo);
		pthread_mutex_unlock(&philo->p_mtx);
	}
	return (NULL);
}

void	hold_forks(pthread_mutex_t *first, pthread_mutex_t *second, t_philo *philo)
{
	pthread_mutex_lock(first);
	print_status(FORKS, philo);
	pthread_mutex_lock(second);
	print_status(FORKS, philo);
	print_status(EAT, philo);
	pthread_mutex_lock(&philo->p_mtx);
	philo->dead_time = ft_get_time() + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->p_mtx);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(first);
    pthread_mutex_unlock(second);
	pthread_mutex_lock(&philo->full_mtx);
	philo->meals++;
	if (philo->meals == philo->data->repeat)
		philo->full = 1;
	pthread_mutex_unlock(&philo->full_mtx);
	print_status(SLEEP, philo);
	ft_usleep(philo->data->time_to_sleep);
	print_status(THINK, philo);
}

void	try_to_eat(t_philo *philo)
{
	pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

	if (philo->id % 2 == 0)
	{
        first_fork = philo->left_fork;
        second_fork = philo->right_fork;
    }
	else
	{
        first_fork = philo->right_fork;
        second_fork = philo->left_fork;
    }
	hold_forks(first_fork, second_fork, philo);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->dead_time = philo->data->time_to_die + ft_get_time();
	if (pthread_create(&philo->td, NULL, &check_if_died, philo))
		return (NULL);
	while (!is_philo_full(philo) && is_philos_live(philo))
		try_to_eat(philo);
	if (pthread_join(philo->td, NULL))
		return (NULL);
	return (NULL);
}

int	one_philo(t_data *data)
{
    if (pthread_create(&data->threads[0], NULL, &routine, &data->philo[0]))
		return (0);
	pthread_detach(data->philo[0].td);
	pthread_detach(data->threads[0]);
    while (is_philos_live(&data->philo[0]))
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
