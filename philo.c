#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int i = 0;
pthread_mutex_t mutex;

void    *test()
{
    int j = 0;
    pthread_mutex_lock(&mutex);
    while (j < 1000000)
    {
        i++;
        j++;
    }
    pthread_mutex_unlock(&mutex);
}


int main(void)
{
    pthread_t t1;
    pthread_t t2;

    pthread_mutex_init(&mutex, NULL);
    pthread_create(&t1, NULL, &test, NULL);
    pthread_create(&t2, NULL, &test, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&mutex);
    printf("%i\n", i);
}