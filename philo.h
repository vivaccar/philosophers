#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <pthread.h>

typedef struct s_data
{
    int n_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int n_eat;
}               t_data;


#endif