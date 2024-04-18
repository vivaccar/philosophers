/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:23:16 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/18 18:48:31 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_philos(t_table *table)
{
	int	i;

	table->philo = malloc(sizeof(t_philo) * table->n_philos);
	if (!table->philo)
		return (error_philo("Error: Philo's malloc!\n", NULL));
	i = 0;
	while (i < table->n_philos)
	{
		table->philo[i].id = i + 1;
		table->philo[i].meals = 0;
		table->philo[i].table = table;
		table->philo[i].pid = -1;
		table->philo[i].dead_time = 0;
		i++;
	}
	return (1);
}

void	kill_processes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		kill(table->philo[i].pid, SIGINT);
		i++;
	}
}

void	*check_if_died(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->dead_time < ft_get_time())
		{
			printf("%zu %i died.\n", ft_get_time() - philo->table->start_time, philo->id);
			kill_processes(philo->table);
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
	while (i != philo->table->repeat)
	{
		sem_wait(philo->table->forks);
		printf("%zu %i has taken a fork\n", ft_get_time() - philo->table->start_time, philo->id);
		sem_wait(philo->table->forks);
		printf("%zu %i has taken a fork\n", ft_get_time() - philo->table->start_time, philo->id);
		printf("%zu %i is eating\n", ft_get_time() - philo->table->start_time, philo->id);
		philo->dead_time = ft_get_time() + philo->table->time_to_die;
		ft_usleep(philo->table->time_to_eat);
		printf("%zu %i is sleeping\n", ft_get_time() - philo->table->start_time, philo->id);
		sem_post(philo->table->forks);
		sem_post(philo->table->forks);
		ft_usleep(philo->table->time_to_sleep);
		printf("%zu %i is thinking\n", ft_get_time() - philo->table->start_time, philo->id);
		i++;
	}
	if (pthread_detach(philo->td))
		return ;
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
		{
			start_to_eat(&table->philo[i]);
			exit(0);
		}
		i++;
	}
	return (0);
}

void	init_semaphores(t_table *table)
{
	sem_unlink("forks");
	table->forks = sem_open("forks", O_CREAT, 0644, table->n_philos);
}

int	main(int ac, char **av)
{
	t_table	table;
	int		x;
	int		j = 0;

	if (!check_input(ac, av, &table))
		return (0);
	if (!init_philos(&table))
		return (0);
	init_semaphores(&table);
	create_processes(&table);
	while (j < table.n_philos)
	{
		waitpid(0, &x, 0);
		j++;
	}
	sem_close(table.forks);
	free(table.philo);
/* 	for (int i = 0; i < table.n_philos; i++)
		printf("pid: %i", table.philo[i].pid); */
	//return (0);
/* 	printf("time to die: %zu\n", table.time_to_die);
	printf("time to eat: %zu\n", table.time_to_eat);
	printf("time to sleep: %zu\n", table.time_to_sleep);
	printf("philos: %ld\n", table.n_philos); */
}




















