#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_fork
{
    int         id;
}               t_fork;

typedef struct s_philo
{
    int         id;
    t_fork      *right_fork;
    t_fork      *left_fork;
}               t_philo;


typedef struct s_data
{
    long        n_philos;
    long        time_to_die;
    long        time_to_eat;
    long        time_to_sleep;
    long        n_eat;
    t_philo     *philo;
    t_fork      *forks;
}               t_data;



// Checking parameters
int     set_values(int ac, char **av, t_data *data);
int	    ft_isdigit(int c);
long	ft_atol(const char *str);
int     check_parameters(int ac, char **av);
int     check_timestamps(t_data *data);
int     fill_data(int ac, char **av, t_data *data);

#endif