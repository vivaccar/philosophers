/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:42:19 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/22 13:16:19 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_dinner(t_data *data)
{
	pthread_mutex_lock(&data->table_mtx);
	data->dinner_running = 0;
	pthread_mutex_unlock(&data->table_mtx);
}

int	dinner_running(t_data *data)
{
	int	dinner;

	pthread_mutex_lock(&data->table_mtx);
	if (data->dinner_running == 0)
		dinner = 0;
	else
		dinner = 1;
	pthread_mutex_unlock(&data->table_mtx);
	return (dinner);
}

int	is_philo_full(t_philo *philo)
{
	int	full_signal;

	pthread_mutex_lock(&philo->philo_mtx);
	if (philo->full)
		full_signal = 1;
	else
		full_signal = 0;
	pthread_mutex_unlock(&philo->philo_mtx);
	return (full_signal);
}

int	is_philos_live(t_philo *philo)
{
	int	dead_signal;

	pthread_mutex_lock(&philo->data->table_mtx);
	if (!philo->data->live)
		dead_signal = 0;
	else
		dead_signal = 1;
	pthread_mutex_unlock(&philo->data->table_mtx);
	return (dead_signal);
}

void	print_status(char *str, t_philo *philo)
{
	size_t	time;

	time = ft_get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mtx);
	if (!ft_strncmp(str, "died", 4) && is_philos_live(philo))
	{
		pthread_mutex_lock(&philo->data->table_mtx);
		printf("%zu %i %s\n", time, philo->id, str);
		philo->data->live = 0;
		pthread_mutex_unlock(&philo->data->table_mtx);
	}
	else if (is_philos_live(philo))
		printf("%zu %i %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mtx);
}
