#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t		semaphore;
static int	counter;

void	worker_increment(void)
{
	int	i;
	int	local;

	for (int i = 0; i < 10; i++)
	{
		sem_wait(&semaphore);
		local = counter;
		printf("worker increment = %d\n", counter);
		local++;
		counter = local;
		sleep(1);
		sem_post(&semaphore);
	}
}

void	worker_decrement(void)
{
	int	i;
	int	local;

	for (int i = 0; i < 10; i++)
	{
		sem_wait(&semaphore);
		local = counter;
		printf("worker decrement = %d\n", counter);
		local--;
		counter = local;
		sleep(1);
		sem_post(&semaphore);
	}
}

int	main(void)
{
	int			semfd;
	pthread_t	thread1;
	pthread_t	thread2;

	sem_init(&semaphore, 0, 1);
	pthread_create(&thread1, NULL, (void *(*)(void *))worker_increment, NULL);
	pthread_create(&thread2, NULL, (void *(*)(void *))worker_decrement, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	sem_destroy(&semaphore);
	printf("\nResult = %d\n", counter);
	return (0);
}
