#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "unistd.h"
# include "stdio.h"
# include "sys/wait.h"
# include "semaphore.h"
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <fcntl.h>
# include <signal.h>

# define EAT "is eating"
# define FORKS "has taken a fork"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

typedef	struct s_table
{
	long				n_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				start_time;
	long				repeat;
	struct s_philo		*philo;
	sem_t				*forks;
	sem_t				*print;
}						t_table;

typedef	struct s_philo
{
	int			id;
	int			meals;
	size_t		dead_time;
	pid_t		pid;
	t_table		*table;
	pthread_t	td;
}				t_philo;

int		check_input(int ac, char **av, t_table *table);

long	ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_usleep(size_t miliseconds);
size_t	ft_get_time(void);

int		error_philo(char *msg, t_table *table);

#endif