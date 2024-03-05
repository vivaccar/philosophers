#include "philo.h"

int    alloc_structures(t_data *data)
{
    data->philo = malloc(sizeof(t_philo) * data->n_philos);
    if (!data->philo)
    {
        printf("Malloc Error!\n");
        return (0);
    }
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
        i++;
        j++;
    }
}

void    init_structures(t_data *data)
{
    init_philos(data);
}

int main(int ac, char **av)
{
    t_data  data;
    
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
        printf("Philo %i id: %i\n", i, data.philo[j].id);
        i++;
        j++;
    }
    printf("Number of philos: %ld\n", data.n_philos);
    printf("Time to die: %ld\n", data.time_to_die);
    printf("Time to eat: %ld\n", data.time_to_eat);
    printf("Time to sleep: %ld\n", data.time_to_sleep);
    printf("Number of eats: %ld\n", data.n_eat);
}