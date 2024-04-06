/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:10:03 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/06 15:38:08 by vivaccar         ###   ########.fr       */
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

void	*eat(void *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)data;
	i = 0;
	philo->dead_time = philo->data->start_time + (unsigned long) philo->data->time_to_die;
	while (i != philo->data->repeat && philo->data->live)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		if (ft_get_time() > (unsigned long) philo->dead_time)
		{
			philo->data->live = 0;
			return (printf("%zu: %i died\n", ft_get_time() - philo->data->start_time, philo->id), NULL);
		}
		printf("%zu: %i has taken a fork\n", ft_get_time() - philo->data->start_time, philo->id);
		printf("%zu: %i has taken a fork\n", ft_get_time() - philo->data->start_time, philo->id);
		printf("%zu: %i is eating\n", ft_get_time() - philo->data->start_time, philo->id);
		philo->dead_time = ft_get_time() + philo->data->time_to_die;
		ft_usleep(philo->data->time_to_eat);
		printf("%zu: %i drop the fork\n", ft_get_time() - philo->data->start_time, philo->id);
		printf("%zu: %i drop the fork\n", ft_get_time() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		printf("%zu: %i is sleeping\n", ft_get_time() - philo->data->start_time, philo->id);
		ft_usleep(philo->data->time_to_sleep);
		printf("%zu: %i is thinking\n", ft_get_time() - philo->data->start_time, philo->id);
		i++;
	}
	return (NULL);
}

void	deliver_forks(t_data *data)
{
	int	i;

	i = 1;
	while (i <= data->n_philos)
	{
		data->philo[i - 1].id = i;
		data->philo[i - 1].data = data;
		pthread_mutex_init(&data->forks[i - 1], NULL);
		data->philo[i - 1].right_fork = &data->forks[i - 1];
		if (data->n_philos == i)
			data->philo[i - 1].left_fork = &data->forks[0];
		else
			data->philo[i - 1].left_fork = &data->forks[i];
		i++;
	}
}

int	init_philos(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
		return (error_philo("Error: Fork's malloc error!\n"));
	data->threads = malloc(sizeof(pthread_t) * data->n_philos);
	if (!data->threads)
		return (error_philo("Error: Thread's malloc error!\n"));
	data->philo = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philo)
		return (error_philo("Error: Philo's malloc error!\n"));
	deliver_forks(data);
	return (1);
}

int	start_dinner(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = ft_get_time();
	while (i < data->n_philos)
	{
		if (pthread_create(&data->threads[i], NULL, &eat, &data->philo[i]))
			return (error_philo("Error: Thread Create.\n"));
		i++;
	}
	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_join(data->threads[i], NULL))
			return (error_philo("Error: Thread Join.\n"));
		i++;
	}
	return (1);
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
// PRINT ARGS
/* 	printf("Philos: %li\n", data.n_philos);
	printf("Time to die: %li\n", data.time_to_die);
	printf("Time to eat: %li\n", data.time_to_eat);
	printf("Time to sleep: %li\n", data.time_to_sleep);
	printf("Repeat: %li\n", data.repeat); */

// PRINT PHILOS
/* 	int	i = 1;
	while (i <= data.n_philos)
	{
		printf("Philo %i id: %i, Right Fork id: %i, Left Fork id: %i\n", i, data.philo[i - 1].id, data.philo[i - 1].right_fork->id, data.philo[i - 1].left_fork->id);
		i++;
	} */
	free(data.philo);
	free(data.forks);
}