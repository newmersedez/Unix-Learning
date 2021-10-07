#include <iostream>
#include <signal.h>
#include <unistd.h>

int main()
{
	sigset_t	signals;

	sigemptyset(&signals);
	sigfillset(&signals);
	std::cout << (sigismember(&signals, SIGTERM) ? "YES" : "NO") << std::endl;
	sigdelset(&signals, SIGTERM);
	std::cout << (sigismember(&signals, SIGTERM) ? "YES" : "NO") << std::endl;
	sigaddset(&signals, SIGTERM);
	std::cout << (sigismember(&signals, SIGTERM) ? "YES" : "NO") << std::endl;
	sigemptyset(&signals);
	std::cout << (sigismember(&signals, SIGTERM) ? "YES" : "NO") << std::endl;
	return 0;
}