/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:46:49 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/15 15:02:37 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	if (!ft_strncmp(str, "died", 4) && is_philos_live(philo))
	{
		pthread_mutex_lock(&philo->data->table_mtx);
		printf("%zu %i %s\n", ft_get_time() - philo->data->start_time, philo->id, str);
		philo->data->live = 0;
		pthread_mutex_unlock(&philo->data->table_mtx);
	}
	else if (is_philos_live(philo))
		printf("%zu %i %s\n", ft_get_time() - philo->data->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mtx);
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


void	hold_forks(pthread_mutex_t *first, pthread_mutex_t *second, t_philo *philo)
{
	pthread_mutex_lock(first);
	print_status(FORKS, philo);
	
	pthread_mutex_lock(second);
	print_status(FORKS, philo);
	print_status(EAT, philo);
	pthread_mutex_lock(&philo->philo_mtx);
	philo->dead_time = ft_get_time() + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->philo_mtx);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(first);
    pthread_mutex_unlock(second);
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
	if (philo->data->n_philos == 1)
	hold_forks(first_fork, second_fork, philo);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->philo_mtx);
	philo->dead_time = philo->data->time_to_die + ft_get_time();
	pthread_mutex_unlock(&philo->philo_mtx);
	while (!is_philo_full(philo) && is_philos_live(philo))
		try_to_eat(philo);
	return (NULL);
}

void	wait_threads(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->table_mtx);
		if (data->th_created)
		{
			pthread_mutex_unlock(&data->table_mtx);
			break;
		}
		pthread_mutex_unlock(&data->table_mtx);
	}
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

void	*monitor(void *arg)
{
	t_data *data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	wait_threads(data);
	while (dinner_running(data))
	{
		if (i == data->n_philos)
			i = 0;
		pthread_mutex_lock(&data->philo[i].philo_mtx);
		if (ft_get_time() > data->philo[i].dead_time && data->philo[i].dead_time != 0)
		{
			print_status("died", &data->philo[i]);
			pthread_mutex_unlock(&data->philo[i].philo_mtx);
			break;
		}
		pthread_mutex_unlock(&data->philo[i].philo_mtx);
		i++;
	}
	return (NULL);
}

int	one_philo(t_data *data)
{
    if (pthread_create(&data->monitor, NULL, &monitor, data))
		return (0);
	if (pthread_create(&data->threads[0], NULL, &routine, &data->philo[0]))
		return (0);
	pthread_mutex_lock(&data->table_mtx);
	data->th_created = 1;
	pthread_mutex_unlock(&data->table_mtx);
	pthread_detach(data->threads[0]);
    while (1)
    {
		if (!is_philos_live(&data->philo[0]))
			break;
	}
	if (pthread_join(data->monitor, NULL))
			return (0);
    return (1);
}

int	create_and_join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_create(&data->threads[i], NULL, &routine, &data->philo[i]))
			return (error_philo("Error: Thread Create.\n"));
		i++;
	}
	pthread_mutex_lock(&data->table_mtx);
	data->th_created = 1;
	pthread_mutex_unlock(&data->table_mtx);
	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_join(data->threads[i], NULL))
			return (error_philo("Error: Thread Join.\n"));
		i++;
	}
	return (1);
}

void	end_dinner(t_data *data)
{
	pthread_mutex_lock(&data->table_mtx);
	data->dinner_running = 0;
	pthread_mutex_unlock(&data->table_mtx);
}

int	start_dinner(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = ft_get_time();
	if (data->n_philos == 1)
		return (one_philo(data));
	if (pthread_create(&data->monitor, NULL, &monitor, data))
		return (0);
	if (!create_and_join_threads(data))
		return (0);
	end_dinner(data);
	if (pthread_join(data->monitor, NULL))
		return (0);
	return (1);
}
