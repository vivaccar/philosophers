/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:33:20 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/22 19:47:14 by vivaccar         ###   ########.fr       */
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

int	ft_usleep(size_t miliseconds)
{
	size_t	start;cd ..
	

	start = ft_get_time();
	while ((ft_get_time() - start) < miliseconds)
		usleep (500);
	return (0);
}

void	wait_for_kill(void)
{
	while (42)
		ft_usleep(42);
}
