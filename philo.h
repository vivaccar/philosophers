#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	int		n_philos;
	int		time_to_die;
	int		time_to_sleep;
	int		time_to_eat;
	int		repeat;
}				t_data;

#endif