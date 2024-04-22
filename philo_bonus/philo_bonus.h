/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:28:26 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/22 18:03:10 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_table
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
	sem_t				*time;
	sem_t				*death;
	sem_t				*full;
}						t_table;

typedef struct s_philo
{
	int				live;	
	int				id;
	int				meals;
	size_t			dead_time;
	pid_t			pid;
	t_table			*table;
	pthread_t		td;
}				t_philo;

int		check_input(int ac, char **av, t_table *table);
int		error_philo(char *msg, t_table *table);
int		argument_is_number(int ac, char **av);

//INIT
long	ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	init_semaphores(t_table *table);
int		init_philos(t_table *table);

//PROCESSES
void	kill_processes(t_table *table);
void	print_message(t_philo *philo, char *message);
void	*check_if_died(void *arg);
void	start_to_eat(t_philo *philo);
int		create_processes(t_table *table);

//UTILS
void	wait_for_posts(t_table *table);
void	destroy_data(t_table *table);
int		is_philo_full(t_philo *philo);
int		is_philo_live(t_philo *philo);
int		ft_usleep(size_t miliseconds);
size_t	ft_get_time(void);
void	wait_for_kill(void);

//EATING
void	hold(t_philo *philo);
void	eat(t_philo *philo);
void	drop(t_philo *philo);
void	sleep_and_think(t_philo *philo);

#endif