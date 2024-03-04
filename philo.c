#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

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

int check_parameters(int ac, char **av)
{
    int i;
    int j;

    i = 1;
    if (ac != 5 && ac != 6)
    {
        printf("Error: Invalid number of arguments!\n");
        return (0);
    }
    while (i < ac)
    {
        j = 0;
        while ((av[i][j] == 32) || (av[i][j] >= 9 && av[i][j] <= 13))
            j++;
        while (av[i][j])
        {
            if (!ft_isdigit(av[i][j]))
            {
                printf("Error: Arguments must contain only numbers!\n");
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

int    check_convert(int ac, char **argv, t_data *data)
{
    if ((data->n_philos = ft_atol(argv[1])) < 1)
    {
        printf("Error: Must have at least one philo!\n");
        return (0);
    }
    data->n_philos = ft_atol(argv[1]);
    data->time_to_die = ft_atol(argv[2]);
    data->time_to_eat = ft_atol(argv[3]);
    data->time_to_sleep = ft_atol(argv[4]);
    if (data->time_to_die < 60 || data->time_to_eat < 60 || data->time_to_sleep < 60)
    {
        printf("Error: At least 60 milliseconds is required!\n");
        return (0);
    }
    if (data->time_to_die > INT_MAX || data->time_to_eat > INT_MAX || data->time_to_sleep > INT_MAX)
    {
        printf("Error: The maximum integer is 2147483647!\n");
        return (0);
    }
    if (ac == 6)
    {
        if (data->n_eat = ft_atol(argv[5]) < 1);
        {
            printf("Error: The number of meals must be at least 1\n");
            return (0);
        }
    }
    else
        data->n_eat = -1;
    return (1);
}

int set_values(int ac, char **av, t_data *data)
{
    if (!check_parameters(ac, av))
        return (0);
    if (!check_convert(ac, av, data))
        return (0);
}

int main(int ac, char **av)
{
    t_data  data;
    
    if (!set_values(ac, av, &data))
        return (0);
    printf("Number of philos: %ld\n", data.n_philos);
    printf("Time to die: %ld\n", data.time_to_die);
    printf("Time to eat: %ld\n", data.time_to_eat);
    printf("Time to sleep: %ld\n", data.time_to_sleep);
    printf("Number of eats: %i\n", data.n_eat);
}