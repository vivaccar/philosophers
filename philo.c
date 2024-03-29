/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:10:03 by vivaccar          #+#    #+#             */
/*   Updated: 2024/03/29 18:36:12 by vivaccar         ###   ########.fr       */
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

int	argument_is_number(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if(av[i][0] == '-' && j == 0)
				j++;
			if (av[i][j] > '9' || av[i][j] < '0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	error_philo(char *msg)
{
	printf("%s", msg);
	return (0);
}

int	check_overflow_and_signal(t_data *data)
{
	if (data->n_philos < 1)
		return (error_philo("Error: Must have at least 1 philosopher\n"));
	if (data->time_to_die < 0 || data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (error_philo("Error: Only positive numbers as parameters!\n"));
	if (data->n_philos > INT_MAX || data->repeat > INT_MAX || data->time_to_eat >INT_MAX
		|| data->time_to_sleep > INT_MAX || data->time_to_die > INT_MAX)
		return (error_philo("Error: INT_MAX is 2147483647!\n"));
	return (1);
}

int	init_data(char **av, t_data *data)
{
	data->n_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5] && ft_atoi(av[5]) >= 0)
		data->repeat = ft_atoi(av[5]);
	else if (!av[5])
		data->repeat = -1;
	else
		return (error_philo("Error: Only positive numbers as parameters!\n"));
	if (!check_overflow_and_signal(data))
		return (0);
	return (1);
}

int	init_input(int ac, char **av, t_data *data)
{
	if (ac != 5 && ac != 6)
		return (error_philo("Error: Invalid number of arguments!\n"));
	if (!argument_is_number(ac, av))
		return (error_philo("Error: Arguments must be numbers!\n"));
	if (!init_data(av, data))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!init_input(ac, av, &data))
		return (0);
	printf("Philos: %li\n", data.n_philos);
	printf("Time to die: %li\n", data.time_to_die);
	printf("Time to eat: %li\n", data.time_to_eat);
	printf("Time to sleep: %li\n", data.time_to_sleep);
	printf("Repeat: %li\n", data.repeat);
}