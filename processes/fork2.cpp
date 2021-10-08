#include <iostream>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	if (fork() != 0)
	{
		std::cout << "Parent pid = " << getpid() << std::endl;
		// std::cout << "Child terminated " << wait(NULL);
		std::cout << "Child terminated " << waitpid(-1, NULL, 0);
	}
	else
	{
		std::cout << "I am " << getpid() << ", my parent is " << getppid() << std::endl;
	}
	return 0;
}