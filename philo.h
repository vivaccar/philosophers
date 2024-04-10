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
# define DIED "died"
# define E_SLEEP "\U0001F4A4"
# define E_DIED "\U00002620"
# define E_THINKING "\U0001F914"
# define E_FORKS "\U0001F374"
# define E_EAT "\U0001F60B"


struct		s_data;

typedef struct s_philo
{
	int					id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		p_mtx;
	struct s_data		*data;
	size_t				dead_time;
	pthread_t			td;
	int					is_eating;
	int					meals;
	int					full;
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
	pthread_mutex_t	data_locker;
}				t_data;

//INPUT
int		init_input(int ac, char **av, t_data *data);
int		init_data(char **av, t_data *data);
int		check_overflow_and_signal(t_data *data);
int		argument_is_number(int ac, char **av);

//INIT
int		init_philos(t_data *data);
void	deliver_forks(t_data *data);

//UTILS
long	ft_atoi(const char *str);
int		error_philo(char *msg);
size_t	ft_get_time();
int 	ft_usleep(size_t miliseconds);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	destroy_data(t_data *data);


//THREAD
void	print_status(char *str, t_philo *philo, char *e);
void	*supervisor(void *data);
void	eating(t_philo *philo);
void	sleep_and_think(t_philo *philo);
void	*routine(void *data);
int		start_dinner(t_data *data);

#endif