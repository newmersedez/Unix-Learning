#include <iostream>
#include <signal.h>
#include <unistd.h>

int main()
{
	sigset_t	signals;

	sigemptyset(&signals);
	if (sigpending(&signals) == -1)
		perror("sigpending");
	else
		std::cout << (sigismember(&signals, SIGTERM) ? "WAITING SIGNAL" : "NO WAITING") << std::endl;	
	return 0;
}