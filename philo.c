/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:10:03 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/08 11:27:11 by vivaccar         ###   ########.fr       */
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


/* void	*checker(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (42)
	{
		if (philo->dead_time < ft_get_time())
		{
			printf("%zu: %i died\n", ft_get_time() - philo->data->start_time, philo->id);
			philo->data->live = 0;
			break ;
		}
	}
	return (NULL);
} */




void	print_status(char *str, t_philo *philo)
{
		pthread_mutex_lock(&philo->data->status);
		printf("%zu %i %s\n", ft_get_time() - philo->data->start_time, philo->id, str);
		pthread_mutex_unlock(&philo->data->status);
}

void	hold_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_status(FORKS, philo);
	pthread_mutex_lock(philo->left_fork);
	print_status(FORKS, philo);
	print_status(EAT, philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*supervisor(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->data->live)
	{
		if (philo->dead_time < ft_get_time() && !philo->is_eating)
		{
			philo->data->live = 0;
			print_status("died", philo);
		}
	}
	return (NULL);
}

void	*eat(void *data)
{
	t_philo	*philo;
	int		i;
	
	philo = (t_philo *)data;
	i = 0;
	if (pthread_create(&philo->td, NULL, &supervisor, philo))
	{
		error_philo("Error: Thread supervisor!\n");
		return (NULL);
	}
	philo->dead_time = ft_get_time() + philo->data->time_to_die;
	while (philo->data->live)
	{
		hold_forks(philo);
		philo->dead_time = ft_get_time() + philo->data->time_to_die;
		philo->is_eating = 1;
		ft_usleep(philo->data->time_to_eat);
		philo->is_eating = 0;
		drop_forks(philo);
		print_status(SLEEP, philo);
		ft_usleep(philo->data->time_to_sleep);
		print_status(THINK, philo);
		i++;
	}
	if (pthread_join(philo->td, NULL))
	{
		error_philo("Error: Thread supervisor!\n");
		return (NULL);
	}
	return (NULL);
}

void	deliver_forks(t_data *data)
{
	int	i;

	i = 1;
	while (i <= data->n_philos)
	{
		data->philo[i - 1].is_eating = 0;
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
	pthread_mutex_init(&data->status, NULL);
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