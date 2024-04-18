#include "philo_bonus.h"

void	eat(t_philo *philo)
{
	printf("Hello I'm a Philosopher %i!\n", philo->id);
}

int	main(void)
{
	// sem_t		*semaphore;
	//int 		id = 1;
	int			i = 1;
	t_philo		philo[5];

	// sem_unlink("first_semaphore");
	// semaphore = sem_open("first_semaphore", O_CREAT, 0644, 2);
	while (i <= 5)
	{
		philo[i - 1].id = i;
		i++;
	}
	i = 0;
	while (i < 5)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			eat(&philo[i]);
			exit(0);
		}
		i++;
	}
	printf("I'm main process.\n");
	// sem_wait(semaphore);
/* 	i = 1;
	while (i <= 5)
	{
		printf("Process: %i\n", philo[i - 1].pid);
		i++;
	} */
	// sleep(3);	
	// sem_post(semaphore);
	// sem_close(semaphore);
	// sem_unlink("first_semaphore");
}