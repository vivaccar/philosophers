/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:23:16 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/22 13:31:17 by vivaccar         ###   ########.fr       */
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
		kill(table->philo[i].pid, SIGKILL);
		i++;
	}
}

void	print_message(t_philo *philo, char *message)
{
	sem_wait(philo->table->print);
	printf("%zu %i %s\n", ft_get_time() - philo->table->start_time, philo->id, message);
	if (ft_strncmp(message, DIED, 4))
		sem_post(philo->table->print);
}

int	is_philo_live(t_philo *philo)
{
	int	is_live;

	sem_wait(philo->table->time);
	if (philo->dead_time <= ft_get_time())
		is_live = 0;
	else
		is_live = 1;
	sem_post(philo->table->time);
	return (is_live);
}

int	is_philo_full(t_philo *philo)
{
	int	is_full;	

	sem_wait(philo->table->full);
	if (philo->meals == philo->table->repeat)
		is_full = 1;
	else
		is_full = 0;
	sem_post(philo->table->full);
		return (is_full);
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
/* 			while (i < philo->table->n_philos)
			{ */
			sem_post(philo->table->death);
/* 				i++;
			} */
			break ;
		}
		if (is_philo_full(philo))
		{
			sem_post(philo->table->death);
			break;
		}
		usleep(1);
	}
	return (NULL);
}

void	hold(t_philo *philo)
{
		sem_wait(philo->table->forks);
		print_message(philo, FORKS);
		sem_wait(philo->table->forks);
		print_message(philo, FORKS);
}

void	eat(t_philo *philo)
{
		print_message(philo, EAT);
		sem_wait(philo->table->time);
		philo->dead_time = ft_get_time() + philo->table->time_to_die;
		sem_post(philo->table->time);
		ft_usleep(philo->table->time_to_eat);
		sem_wait(philo->table->full);
		philo->meals++;
		sem_post(philo->table->full);
}

void	drop(t_philo *philo)
{
		sem_post(philo->table->forks);
		sem_post(philo->table->forks);
}

void	sleep_and_think(t_philo *philo)
{
		print_message(philo, SLEEP);
		ft_usleep(philo->table->time_to_sleep);
		print_message(philo, THINK);
}

void	wait_for_kill()
{
	while (42)
		ft_usleep(42);
}

void	start_to_eat(t_philo *philo)
{	
	int	i;

	i = 0;
	if (philo->id % 2 == 0)
		ft_usleep(5);
	philo->dead_time = ft_get_time() + philo->table->time_to_die;
	if (pthread_create(&philo->td, NULL, &check_if_died, philo))
		return ;
	pthread_detach(philo->td);
	while (1)
	{
		hold(philo);
		eat(philo);
		drop(philo);
		sleep_and_think(philo);
		i++;
		if (i == philo->table->repeat)
			break;
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
		{
			start_to_eat(&table->philo[i]);
		}
		i++;
	}
	return (0);
}

void	init_semaphores(t_table *table)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("time");
	sem_unlink("death");
	sem_unlink("full");
	table->forks = sem_open("forks", O_CREAT, 0600, table->n_philos);
	table->print = sem_open("print", O_CREAT, 0600, 1);
	table->time = sem_open("time", O_CREAT, 0600, 1);
	table->death = sem_open("death", O_CREAT, 0600, 1);
	table->full = sem_open("full", O_CREAT, 0600, 1);
}

void	destroy_data(t_table *table)
{
	sem_close(table->full);
	sem_close(table->death);
	sem_close(table->time);
	sem_close(table->forks);
	sem_close(table->print);
	free(table->philo);
}

void	wait_for_posts(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		sem_wait(table->death);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_table	table;

	if (!check_input(ac, av, &table))
		return (0);
	if (!init_philos(&table))
		return (0);
	init_semaphores(&table);
	sem_wait(table.death);
	create_processes(&table);
	wait_for_posts(&table);
	kill_processes(&table);
	destroy_data(&table);
}




















