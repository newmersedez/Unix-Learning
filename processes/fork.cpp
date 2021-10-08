#include <iostream>
#include <unistd.h>
#include <sys/param.h>
#include <limits.h>

int main()
{
	pid_t	child_pid, parent_pid;

	parent_pid = getppid();
	child_pid = fork();
	switch(child_pid)
	{
		case -1:
			perror("fork");
			break;
		case 0:
			std::cout << "Children process created - " << getpid() << std::endl;
			break;
		default:
			std::cout << "Parent process after fork - " << parent_pid <<std::endl;
	}
	return 0;
}
