/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinivaccari <vinivaccari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:33:20 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/23 17:19:11 by vinivaccari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL ) == -1)
		write (2, "Error: Gettimeof day.\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	mili_sleep(size_t miliseconds)
{
	usleep(1000 * miliseconds);
}
