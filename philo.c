/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:10:03 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/10 18:01:26 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].p_mtx);
		i++;
	}
	pthread_mutex_destroy(&data->data_locker);
	pthread_mutex_destroy(&data->status);
}

int	main(int ac, char **av)
{
	t_data			data;

	if (!init_input(ac, av, &data))
		return (0);
	if (!init_philos(&data))
		return (0);
	if (!start_dinner(&data))
		return (0);
	//destroy_data(&data);
	free(data.philo);
	free(data.threads);
	free(data.forks);
}