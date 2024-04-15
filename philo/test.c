# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

void	*hello()
{
	printf("Hello threads\n");
	sleep(3);
	printf("Bye.\n");
	return (NULL);
}

int	main(void)
{
	pthread_t	t1, t2;
	pthread_create(&t1, NULL, &hello, NULL);
	pthread_create(&t2, NULL, &hello, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
}