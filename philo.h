#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

# define EAT "is eating"
# define FORKS "has taken a fork"
# define SLEEP "is sleeping"
# define THINK "is thinking"

struct		s_data;

typedef struct s_philo
{
	int					id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_data		*data;
	size_t				dead_time;
	pthread_t			td;
	int					is_eating;
	int					meals;
}					t_philo;


typedef struct s_data
{
	long			n_philos;
	long			time_to_die;
	long			time_to_sleep;
	long			time_to_eat;
	long			repeat;
	int				live;
	size_t			start_time;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	pthread_mutex_t	status;
	pthread_mutex_t	hold;
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