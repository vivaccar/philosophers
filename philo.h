#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mtx;
}				t_fork;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
}					t_philo;


typedef struct s_data
{
	long		n_philos;
	long		time_to_die;
	long		time_to_sleep;
	long		time_to_eat;
	long		repeat;
	t_philo		*philo;
	t_fork		*fork;
}				t_data;

//INPUT
int		init_input(int ac, char **av, t_data *data);
int		init_data(char **av, t_data *data);
int		check_overflow_and_signal(t_data *data);
int		argument_is_number(int ac, char **av);

//UTILS
long	ft_atoi(const char *str);
int		error_philo(char *msg);

#endif