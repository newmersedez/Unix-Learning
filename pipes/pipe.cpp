#include <iostream>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	int		fifo[2], status;
	pid_t	child_pid;
	char	buffer[BUFSIZ];

	if (pipe(fifo) == -1)
	{
		std::cerr << "Failed to create pipe" << std::endl;
		exit(EXIT_FAILURE);
	}
	if ((child_pid = fork()) == -1)
	{
		std::cerr << "Failed to create child process" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (child_pid != 0)
	{
		//parent
		std::cout << "I am parent " << getpid() << std::endl;
		close(fifo[0]);
		write(fifo[1], "THIS MESSAGE WAS SENT BY UNIX PIPES", BUFSIZ);
		close(fifo[1]);
		waitpid(child_pid, NULL, 0);
	}
	else
	{
		//child
		read(fifo[0], buffer, BUFSIZ);
		close(fifo[0]);
		std::cout << "\nHi, I am " << getpid() << ", my parent is " << getppid() << std::endl;
		std::cout << buffer << std::endl;
	}
	return 0;
}