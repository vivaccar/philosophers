/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinivaccari <vinivaccari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:34:24 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/23 11:48:42 by vinivaccari      ###   ########.fr       */
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
	//if (ft_strncmp(message, DIED, 4))
	sem_post(philo->table->print);
	/*else
	{
		destroy_data(philo->table);
		return ;
	}*/
}

void	*check_if_died(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (!is_philo_live(philo))
		{
			print_message(philo, DIED);
			destroy_data(philo->table);
			exit(0);
		}
		else if (is_philo_full(philo))
			return (NULL);
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
	print_message(philo, THINK);
	if (philo->id % 2 == 0)
		ft_usleep(15);
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
	destroy_data(philo->table);
	exit(0);
}

void	wait_exit(t_table *table)
{
	int		status;
	pid_t	end_pid;

	while (1)
	{
		end_pid = waitpid(-1, &status, 0);
		if (end_pid > 0)
		{
			if (WIFEXITED(status))
			{
				kill_processes(table);
				break;
			}
		}
		else if (end_pid == -1)
		{
			destroy_data(table);
			exit(1);
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
