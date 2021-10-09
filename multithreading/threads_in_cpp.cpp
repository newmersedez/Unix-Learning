#include <iostream>
#include <thread>
#include <math.h>
#include <iomanip>
#include <vector>

# define MAX_THREADS		4
# define INTEGRAL_TOP		1
# define INTEGRAL_BOTTOM	0

static int	id;
double		pi_parts[MAX_THREADS];

double formula(double x)
{
	return (4 * atan(x));
}

double singlethread_pi()
{
	return (formula(INTEGRAL_TOP) - formula(INTEGRAL_BOTTOM));
}

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
	int							i;
	double						result;
	std::vector< std::thread >	threads_vec;

	i = 0;
	result = 0.0;
	while (i < MAX_THREADS)
	{
		threads_vec.push_back(std::move(std::thread(iterate_pi)));
		threads_vec[i].join();
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
	std::cout << std::setprecision(10) << "Singlethread Pi = " << singlethread_pi() << std::endl;
	std::cout << "Multithread  Pi = " << multithread_pi() << std::endl;
	return (0);
}
