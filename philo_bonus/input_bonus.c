/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:25:17 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/22 11:30:17 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	error_philo(char *msg, t_table *table)
{
	(void)table;
	printf("%s", msg);
	return (0);
}

int	argument_is_number(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if (av[i][0] == 0)
			return (0);
		while (av[i][j])
		{
			if (av[i][0] == '-' && j == 0)
				j++;
			if (av[i][j] > '9' || av[i][j] < '0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_overflow_and_signal(t_table *table)
{
	if (table->n_philos < 1)
		return (error_philo("Error: Must have at least 1 philosopher\n", NULL));
	if (table->time_to_die <= 0 || table->time_to_eat <= 0
		|| table->time_to_sleep <= 0)
		return (error_philo("Error: Arguments must be greather than 0\n", NULL));
	if (table->n_philos > INT_MAX || table->repeat > INT_MAX
		|| table->time_to_eat > INT_MAX || table->time_to_sleep > INT_MAX
		|| table->time_to_die > INT_MAX)
		return (error_philo("Error: INT_MAX is 2147483647!\n", NULL));
	return (1);
}

int	init_data(char **av, t_table *table)
{
	table->n_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (av[5] && ft_atoi(av[5]) >= 0)
		table->repeat = ft_atoi(av[5]);
	else if (!av[5])
		table->repeat = -1;
	else
		return (error_philo("Error: Arguments must be greather than 0\n", NULL));
	if (!check_overflow_and_signal(table))
		return (0);
	return (1);
}

int	check_input(int ac, char **av, t_table *table)
{
	if (ac != 5 && ac != 6)
		return (error_philo("Error: Invalid number of arguments!\n", NULL));
	if (!argument_is_number(ac, av))
		return (error_philo("Error: Arguments must be numbers!\n", NULL));
	if (!init_data(av, table))
		return (0);
	return (1);
}