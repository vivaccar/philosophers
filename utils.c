/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinivaccari <vinivaccari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:19:47 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/13 22:35:29 by vinivaccari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_get_time()
{
	struct timeval	time;

	if (gettimeofday(&time, NULL ) == -1 ) 
		write( 2 , "Error: Gettimeof day.\n" , 22 );
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int ft_usleep(size_t miliseconds)
 { 
	size_t 	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < miliseconds)
		usleep (500);
	return (0);
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

int	error_philo(char *msg)
{
	printf("%s", msg);
	return (0);
}

void	destroy_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (data->n_philos > 1)
			pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].philo_mtx);
		i++;
	}
	pthread_mutex_destroy(&data->table_mtx);
	pthread_mutex_destroy(&data->print_mtx);
	//pthread_mutex_destroy(&data->create_mtx);
	if (data->philo)
		free(data->philo);
	if (data->threads)
		free(data->threads);
	if (data->forks)
		free(data->forks);
}
