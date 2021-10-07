#include <iostream>
#include <signal.h>
#include <unistd.h>

/* Signal works if exit with CTRL+C command */
void catch_sigint(int sig_num)
{
	signal(sig_num, catch_sigint);
	std::cout << "SIGINT handled: " << sig_num << std::endl;
}

/* Signal works if kill process by pid */
void catch_sigterm(int sig_num)
{
	signal(sig_num, catch_sigterm);
	std::cout << "SIGTERM handled: " << sig_num << std::endl;
}

int main()
{
	pid_t	process_pid = getpid();

	std::cout << "Process pid is " << process_pid << std::endl;
	signal(SIGINT, catch_sigint);
	signal(SIGTERM, catch_sigterm);
	signal(SIGSEGV, SIG_DFL);
	pause();
	return 0;
}