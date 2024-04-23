/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinivaccari <vinivaccari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:20:29 by vivaccar          #+#    #+#             */
/*   Updated: 2024/04/23 17:19:42 by vinivaccari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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

typedef struct s_philo
{
	pthread_t			td;
	int					id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		philo_mtx;
	struct s_table		*table;
	size_t				dead_time;
	int					meals;
	int					full;
}					t_philo;

typedef struct s_table
{
	long			n_philos;
	long			time_to_die;
	long			time_to_sleep;
	long			time_to_eat;
	long			repeat;
	int				live;
	int				th_created;
	int				dinner_running;
	size_t			start_time;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_t		monitor;
	pthread_mutex_t	table_mtx;
	pthread_mutex_t	print_mtx;
}				t_table;

//INPUT
int		init_input(int ac, char **av, t_table *table);
int		init_table(char **av, t_table *table);
int		check_overflow_and_signal(t_table *table);
int		argument_is_number(int ac, char **av);

//INIT
int		init_philos(t_table *table);
void	init_forks_and_mutexes(t_table *table);
long	ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//UTILS
int		error_philo(char *msg, t_table *table);
size_t	ft_get_time(void);
void	mili_sleep(size_t miliseconds);
void	destroy_table(t_table *table);
void	print_status(char *str, t_philo *philo);
int		is_philos_live(t_philo *philo);
int		start_dinner(t_table *table);
void	wait_threads(t_table *table);
int		dinner_running(t_table *table);
void	end_dinner(t_table *table);

//ONE_PHILO
int		one_philo(t_table *table);
void	*only_one(void *arg);

//THREAD
void	*monitor(void *arg);
void	*routine(void *table);
void	eating(t_philo *philo);
void	sleep_and_think(t_philo *philo);
int		is_philo_full(t_philo *philo);

//EATING
void	hold(t_philo *philo);
void	eating(t_philo *philo);
void	drop(t_philo *philo);

#endif