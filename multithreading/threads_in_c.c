#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <math.h>
#include <pthread.h>

# define MAX_THREADS		4
# define INTEGRAL_TOP		1
# define INTEGRAL_BOTTOM	0

static int	id;
pthread_t	threads[MAX_THREADS];
double		pi_parts[MAX_THREADS];

/* Formula for PI calculation */

double	formula(double x)
{
	return (4 * atan(x));
}

/* Singlethread PI number calculation */

double	singlethread_pi(void)
{
	return (formula(INTEGRAL_TOP) - formula(INTEGRAL_BOTTOM));
}

/* Multithread PI number calculation */

void	iterate_pi(void)
{
	static double	start;
	static double	end;

	start = (double)id * (INTEGRAL_TOP - INTEGRAL_BOTTOM) / MAX_THREADS;
	end = (double)(id + 1) * (INTEGRAL_TOP - INTEGRAL_BOTTOM) / MAX_THREADS;
	pi_parts[id] = formula(end) - formula(start);
	id++;
}

double multithread_pi(void)
{
	int		i;
	double	result;

	i = 0;
	result = 0.0;
	while (i < MAX_THREADS)
	{
		pthread_create(&threads[i], NULL, (void *(*)(void *))iterate_pi, NULL);
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
	printf("Singlethread PI = %.10f\n", singlethread_pi());
	printf("Multithread  PI = %.10f", multithread_pi());
	return (0);
}