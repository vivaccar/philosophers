/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:45:03 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/22 16:47:47 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	long	result;
	long	signal;

	signal = 1;
	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if ((str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			signal = signal * -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * signal);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (((s1[i]) || (s2[i])) && (i < n))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	init_forks_and_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		table->philo[i].id = i + 1;
		table->philo[i].table = table;
		table->philo[i].meals = 0;
		table->philo[i].full = 0;
		table->philo[i].dead_time = ft_get_time() + table->time_to_die;
		pthread_mutex_init(&table->forks[i], NULL);
		pthread_mutex_init(&table->philo[i].philo_mtx, NULL);
		table->philo[i].right_fork = &table->forks[i];
		if (table->n_philos == i + 1)
			table->philo[i].left_fork = &table->forks[0];
		else
			table->philo[i].left_fork = &table->forks[i + 1];
		i++;
	}
	pthread_mutex_init(&table->print_mtx, NULL);
	pthread_mutex_init(&table->table_mtx, NULL);
}

int	init_philos(t_table *table)
{
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philos);
	if (!table->forks)
		return (error_philo("Error: Fork's malloc error!\n", table));
	table->philo = malloc(sizeof(t_philo) * table->n_philos);
	if (!table->philo)
		return (error_philo("Error: Philo's malloc error!\n", table));
	init_forks_and_mutexes(table);
	return (1);
}
