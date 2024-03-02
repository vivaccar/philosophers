#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	signal;

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

int check_parameters(int ac, char **argv)
{
    int i;
    int j;

    i = 1;
    if (ac != 5 && ac != 6)
    {
        printf("Invalid number of arguments!\n");
        return (0);
    }
    while (i < ac)
    {
        j = 0;
        while (argv[i][j])
        {
            if (!ft_isdigit(argv[i][j]))
            {
                printf("All arguments must be integers!\n");
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

void    init(int ac, char **argv, t_data *data)
{
    data->n_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (ac == 6)
        data->n_eat = ft_atoi(argv[5]);
    else
        data->n_eat = -1;
}

int main(int ac, char *argv[])
{
    t_data  data;
    
    if (!check_parameters(ac, argv))
        return (0);
    init(ac, argv, &data);
    printf("Number of philos: %i\n", data.n_philos);
    printf("Time to die: %i\n", data.time_to_die);
    printf("Time to eat: %i\n", data.time_to_eat);
    printf("Time to sleep: %i\n", data.time_to_sleep);
    printf("Number of eats: %i\n", data.n_eat);
}