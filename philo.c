#include "philo.h"

int     ft_error(char *str, t_data *data)
{
    free(data);
    printf("%s", str);
    return (0);
}

int    alloc_structures(t_data *data)
{
    data->forks = malloc(sizeof(t_fork) * data->n_philos);
    if (!data->forks)
        return (ft_error("Forks malloc error.\n", data));
    data->philo = malloc(sizeof(t_philo) * data->n_philos);
    if (!data->philo)
        return (ft_error("Philos malloc error.\n", data));
    return (1);
}

void    init_philos(t_data *data)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while (i <= data->n_philos)
    {
        data->philo[j].id = i;
        data->philo[j].right_fork = &data->forks[j];
        if (i == data->n_philos)
            data->philo[j].left_fork = &data->forks[0];
        else
            data->philo[j].left_fork = &data->forks[j + 1];
        i++;
        j++;
    }
}

void    init_forks(t_data *data)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while (i <= data->n_philos)
    {
        data->forks[j].id = i;
        i++;
        j++;
    }
}

void    init_structures(t_data *data)
{
    init_forks(data);
    init_philos(data);
}

void    end(t_data *data)
{
    free(data->forks);
    free(data->philo);
}

int main(int ac, char **av)
{
    t_data  data;
    //struct  timeval tv;

    if (!set_values(ac, av, &data))
        return (0);
    if (!alloc_structures(&data))
        return (0);
    init_structures(&data);
    int i, j;
    i = 1;
    j = 0;
    while (i <= data.n_philos)
    {
        printf("Philo %i id: %i | Right fork id: %i | Left fork id: %i\n", i, data.philo[j].id, data.philo[j].right_fork->id, data.philo[j].left_fork->id);
        i++;
        j++;
    }
    /*printf("Number of philos: %ld\n", data.n_philos);
    printf("Time to die: %ld\n", data.time_to_die);
    printf("Time to eat: %ld\n", data.time_to_eat);
    printf("Time to sleep: %ld\n", data.time_to_sleep);
    printf("Number of eats: %ld\n", data.n_eat);*/

    /* forks
    i = 1;
    j = 0;
    while (i <= data.n_philos)
    {
        printf("Fork %i id: %i\n", i, data.forks[j].id);
        i++;
        j++;
    }*/
    end(&data);
    //gettimeofday(&tv, NULL);
    //printf("Time: %li", (tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}