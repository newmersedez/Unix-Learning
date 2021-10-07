#include <iostream>
#include <signal.h>
#include <unistd.h>

/* CTRL+C signal handler using sigset function */
void	sigint_handler(int sig_num)
{
	signal(SIGINT, sigint_handler);
	std::cout << "SIGINT handler: " << sig_num << std::endl;
}

/* Kill process handler using sigset function */
void	sigterm_handler(int sig_num)
{
	signal(SIGTERM, sigterm_handler);
	std::cout << "SIGINT handler: " << sig_num << std::endl;
}

int main()
{
	pid_t	process_pid = getpid();

	std::cout << "Process pid: " << process_pid << std::endl;
	sigset(SIGINT, sigint_handler);
	sigset(SIGTERM, sigterm_handler);
	pause();
	return 0;
}