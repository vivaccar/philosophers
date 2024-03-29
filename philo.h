#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_data
{
	long		n_philos;
	long		time_to_die;
	long		time_to_sleep;
	long		time_to_eat;
	long		repeat;
}				t_data;

#endif