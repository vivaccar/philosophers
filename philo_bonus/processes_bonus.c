/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinivaccari <vinivaccari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:34:24 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/23 17:48:18 by vinivaccari      ###   ########.fr       */
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
	printf("%zu %i %s\n", time, philo->id, message);
	if (ft_strncmp(message, DIED, 4))
		sem_post(philo->table->print);
}

void	monitoring(t_philo *philo)
{
	while (1)
	{
		if (!is_philo_live(philo))
		{
			print_message(philo, DIED);
			destroy_data(philo->table);
			exit(1) ;
		}
		else if (is_philo_full(philo))
			return ;
		usleep(1);
	}
	return ;
}

int	get_live(t_philo *philo)
{
	int	live;

	sem_wait(philo->table->time);
	live = philo->live;
	sem_post(philo->table->time);
	return (live);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_message(philo, THINK);
	if (philo->id % 2 == 0)
		mili_sleep(15);
	while (get_live(philo))
	{
		hold(philo);
		eat(philo);
		drop(philo);
		if (is_philo_full(philo))
			return (NULL);
		sleep_and_think(philo);
	}
	return (NULL);
}

void	start_to_eat(t_philo *philo)
{
	philo->dead_time = ft_get_time() + philo->table->time_to_die;
	if (pthread_create(&philo->td, NULL, &routine, philo))
		return ;
	monitoring(philo);
	if (pthread_join(philo->td, NULL))
		return ;
	destroy_data(philo->table);
	exit (0);
}

void	wait_exit(t_table *table)
{
	while (1)
	{
		if (waitpid(-1, NULL, WNOHANG) != 0)
		{
			kill_processes(table);
			break;
		}
	}
}

int create_processes(t_table *table)
{
    int i;
    
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
