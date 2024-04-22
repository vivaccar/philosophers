/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:34:24 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/22 16:43:02 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_processes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		kill(table->philo[i].pid, SIGKILL);
		i++;
	}
}

void	print_message(t_philo *philo, char *message)
{
	size_t	time;

	time = ft_get_time() - philo->table->start_time;
	sem_wait(philo->table->print);
	printf("%zu %i %s\n", philo->id, message);
	if (ft_strncmp(message, DIED, 4))
		sem_post(philo->table->print);
}

void	*check_if_died(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	while (1)
	{
		if (!is_philo_live(philo))
		{
			print_message(philo, DIED);
			while (i < philo->table->n_philos)
			{
				sem_post(philo->table->death);
				i++;
			}
			break ;
		}
		else if (is_philo_full(philo))
		{
			sem_post(philo->table->death);
			break ;
		}
		usleep(1);
	}
	return (NULL);
}

void	start_to_eat(t_philo *philo)
{
	int	i;

	i = 0;
	philo->dead_time = ft_get_time() + philo->table->time_to_die;
	if (pthread_create(&philo->td, NULL, &check_if_died, philo))
		return ;
	pthread_detach(philo->td);
	if (philo->id % 2 == 0)
		ft_usleep(20);
	while (1)
	{
		hold(philo);
		eat(philo);
		drop(philo);
		sleep_and_think(philo);
		i++;
		if (i == philo->table->repeat)
			break ;
	}
	wait_for_kill();
}

int	create_processes(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = ft_get_time();
	while (i < table->n_philos)
	{
		table->philo[i].pid = fork();
		if (table->philo[i].pid == 0)
			start_to_eat(&table->philo[i]);
		i++;
	}
	return (0);
}
