#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <math.h>
#include <pthread.h>

# define MAX_THREADS		4
# define INTEGRAL_TOP		1
# define INTEGRAL_BOTTOM	0

static int		id;
long double		pi_parts[MAX_THREADS];
pthread_t		threads[MAX_THREADS];

/* Formula for PI calculation */

long double	formula(long double x)
{
	return (4 * atan(x));
}

/* Singlethread PI number calculation */

long double	singlethread_find_pi(void)
{
	return (formula(INTEGRAL_TOP) - formula(INTEGRAL_BOTTOM));
}

/* Multithread PI number calculation */

void	iterate_pi_part(void)
{
	static long double	start;
	static long double	end;

	start = (long double)id * (INTEGRAL_TOP - INTEGRAL_BOTTOM) / MAX_THREADS;
	end = (long double)(id + 1) * (INTEGRAL_TOP - INTEGRAL_BOTTOM) / MAX_THREADS;
	pi_parts[id] = formula(end) - formula(start);
	id++;
}

long double multithread_find_pi(void)
{
	int		i;
	long double	result;

	i = 0;
	result = 0.0;
	while (i < MAX_THREADS)
	{
		pthread_create(&threads[i], NULL, (void *(*)(void *))iterate_pi_part, NULL);
		pthread_join(threads[i], NULL);
		i++;
	}
	i = 0;
	while (i < MAX_THREADS)
	{
		result += pi_parts[i];
		i++;
	}
	return (result);
}

int main()
{
	printf("Singlethread PI = %.10Lf\n", singlethread_find_pi());
	printf("Multithread  PI = %.10Lf", multithread_find_pi());
	return (0);
}