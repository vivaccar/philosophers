#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_data
{
    long    n_philos;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    int     n_eat;
}               t_data;


#endif