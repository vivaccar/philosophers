/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:10:03 by vivaccar          #+#    #+#             */
/*   Updated: 2024/03/29 17:57:41 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	signal;

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

int	error_philo(char *msg, t_data *data)
{
	if (data)
		free(data);
	printf("%s", msg);
	return (0);
}

int	check_overflow_and_signal(t_data *data)
{
	if (data->n_philos < 1)
		return (error_philo("Error: Must have at least 1 philosopher\n", data));
	if (data->time_to_die < 0 || data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (error_philo("Error: Only positive numbers as parameters!\n", data));
	return (1);
}

int	init_data(char **av, t_data *data)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (error_philo("Error: Data malloc\n", NULL));
	data->n_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5] && ft_atoi(av[5]) > 0)
		data->repeat = ft_atoi(av[5]);
	else if (!av[5])
		data->repeat = -1;
	else
		return (error_philo("Error: Only positive numbers as parameters!\n", data));
	if (!check_overflow_and_signal(data))
		return (0);
	return (1);
}

int	init_input(int ac, char **av, t_data *data)
{
	if (ac != 5 && ac != 6)
		return (error_philo("Error: Invalid number of arguments!\n", NULL));
	if (!argument_is_number(ac, av))
		return (error_philo("Error: Arguments must be numbers!\n", NULL));
	if (!init_data(av, data))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (!init_input(ac, av, data))
		return (0);
	free(data);
}