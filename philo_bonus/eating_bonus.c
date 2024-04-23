/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinivaccari <vinivaccari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:31:07 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/23 17:16:24 by vinivaccari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	mili_sleep(philo->table->time_to_eat);
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
	mili_sleep(philo->table->time_to_sleep);
	print_message(philo, THINK);
}
