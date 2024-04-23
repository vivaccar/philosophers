/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinivaccari <vinivaccari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:32:02 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/23 17:13:42 by vinivaccari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_philo_live(t_philo *philo)
{
	int	is_live;

	sem_wait(philo->table->time);
	if (philo->dead_time <= ft_get_time())
		is_live = 0;
	else
		is_live = 1;
	philo->live = is_live;
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

void	destroy_data(t_table *table)
{
	sem_close(table->full);
	sem_close(table->time);
	sem_close(table->forks);
	sem_close(table->print);
	free(table->philo);
}

void	ft_exit(char *msg, t_table *table)
{
	printf("%s", msg);
	destroy_data(table);
	exit(0);
}
