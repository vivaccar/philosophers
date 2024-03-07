#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "philo.h"

long	ft_atol(const char *str)
{
	int	    i;
	long	result;
	long    signal;

	signal = 1;
	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if ((str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			signal = signal * -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * signal);
}

void    *init_table(t_test *table, char **av)
{
    table->n_philos = ft_atol(av[1]);
    table->n_eat = ft_atol(av[2]);
    table->philo = malloc(sizeof(pthread_t) * table->n_philos);
    if (table->philo == NULL)
        return NULL;
    table->fork.philo_id = 0;
    pthread_mutex_init(&table->fork.mutex, NULL);
}

void    *dinner(void *arg)
{
    t_test          *table = ((t_test *)arg);

    pthread_mutex_lock(&table->fork.mutex);
    printf("Thread %i Created!\n", index);
    pthread_mutex_unlock(&table->fork.mutex);
    return (NULL);
}

void    start_threads(t_test *table)
{
    int i;

    i = 0;    
    while (i < table->n_philos)
    {
        pthread_create(&table->philo[i], NULL, &dinner, table);
        i++;
    }
    i = 0;
    while (i < table->n_philos)
    {
        pthread_join(table->philo[i], NULL);
        i++;
    }
}

int main(int ac, char **av)
{
    t_test table;

    if (ac != 3)
        return (0);
    init_table(&table, av);
    start_threads(&table);
}