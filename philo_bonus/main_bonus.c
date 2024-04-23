/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinivaccari <vinivaccari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:23:16 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/23 10:37:22 by vinivaccari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (!check_input(ac, av, &table))
		return (0);
	if (!init_philos(&table))
		return (0);
	init_semaphores(&table);
	create_processes(&table);
	wait_exit(&table);
	destroy_data(&table);
}
