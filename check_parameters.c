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


int    check_parameters(int ac, char **av)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while (i < ac)
    {
        j = 0;
        while (av[i][j] == 32)
            j++;
        if (av[i][j] == '-')
            j++;
        while (av[i][j])
        {
            if (!ft_isdigit(av[i][j]))
            {
                printf("Error: Arguments must be just numbers.\n");
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

int check_timestamps(t_data *data)
{
    if (data->n_philos < 0 || data->time_to_die < 0 || data->time_to_eat < 0 || data->time_to_sleep < 0)
    {
        printf("Error: The parameters must be all positives.\n");
        return (0);
    }
    if (data->time_to_die > INT_MAX || data->time_to_eat > INT_MAX || data->time_to_sleep > INT_MAX
            || data-> n_philos > INT_MAX || data->n_eat > INT_MAX)
    {
        printf("Error: The maximum time is 2147483647.\n");
        return (0);
    }
    return (1);
}

int    fill_data(int ac, char **av, t_data *data)
{
    int error;
    
    data->n_philos = ft_atol(av[1]);
    data->time_to_die = ft_atol(av[2]);
    data->time_to_eat = ft_atol(av[3]);
    data->time_to_sleep = ft_atol(av[4]);
    if (ac == 6)
    {
        data->n_eat = ft_atol(av[5]);
        if (data->n_eat < 0)
        {
            printf("Error: The parameters must be all positives.\n");
            return (0);
        }
    }
    else
        data->n_eat = -1;
    error = check_timestamps(data);
    return (error);
}

int set_values(int ac, char **av, t_data *data)
{
    if (ac != 5 && ac != 6)
    {
        printf("Error: Invalid number of arguments.\n");
        return (0);
    }
    if (!check_parameters(ac, av))
        return (0);
    if (!fill_data(ac, av, data))
        return (0);
    return (1);
}