#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t	mutex;

void	func(void)
{
	pthread_mutex_lock(&mutex);
	printf("Start...\n");
	sleep(2);
	printf("End!\n");
	pthread_mutex_unlock(&mutex);
}

int	main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;

	if (pthread_mutex_init(&mutex, NULL) == -1)
		exit(EXIT_FAILURE);
	pthread_create(&thread1, NULL, (void *(*)(void *))func, NULL);	
	pthread_create(&thread2, NULL, (void *(*)(void *))func, NULL);
	pthread_join(thread1, NULL);	
	pthread_join(thread2, NULL);
	pthread_mutex_destroy(&mutex);
	return (0);
}