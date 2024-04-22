/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:20:38 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/22 19:19:50 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	table->death = sem_open("death", O_CREAT, 0600, 0);
	table->full = sem_open("full", O_CREAT, 0600, 1);
}

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
		table->philo[i].live = 1;
		i++;
	}
	return (1);
}
