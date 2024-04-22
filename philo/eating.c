/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:37:35 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/22 19:32:42 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	hold(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(FORKS, philo);
		pthread_mutex_lock(philo->left_fork);
		print_status(FORKS, philo);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(FORKS, philo);
		pthread_mutex_lock(philo->right_fork);
		print_status(FORKS, philo);
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mtx);
	philo->dead_time = ft_get_time() + philo->table->time_to_die;
	pthread_mutex_unlock(&philo->philo_mtx);
	print_status(EAT, philo);
	ft_usleep(philo->table->time_to_eat);
}

void	drop(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
