#include <iostream>
#include <signal.h>
#include <unistd.h>

void catch_sigint(int sig_num)
{
	std::cout << "SIGINT handled: " << sig_num << std::endl;
}

void catch_sigterm(int sig_num)
{
	std::cout << "SIGTERM handled: " << sig_num << std::endl;
}

int main()
{
	struct sigaction	action_sigint, action_sigterm;

	std::cout << getpid() << std::endl;
	action_sigint.sa_handler = catch_sigint;
	action_sigterm.sa_handler = catch_sigterm;
	sigaction(SIGINT, &action_sigint, NULL);
	sigaction(SIGTERM, &action_sigterm, NULL);
	pause();
	return 0;
}