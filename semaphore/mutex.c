#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t	mutex;

void	func(void)
{
	sem_wait(&mutex);
	printf("Start...\n");
	sleep(4);
	printf("End!\n");
	sem_post(&mutex);
}

int main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;

	sem_init(&mutex, 0, 1);
	pthread_create(&thread1, NULL, (void *(*)(void *))func, NULL);
	sleep(2);
	pthread_create(&thread1, NULL, (void *(*)(void *))func, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	sem_destroy(&mutex);
	return (0);
}