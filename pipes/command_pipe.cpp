#include <iostream>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	int 	fifo[2];
	pid_t	pid1, pid2;

	if (pipe(fifo))
		exit(EXIT_FAILURE);
	switch (pid1 = fork())
	{
		case -1:
			exit(EXIT_FAILURE);
			break;
		case 0:
			if (dup2(fifo[1], STDOUT_FILENO) == -1)
				exit(EXIT_FAILURE);
			close(fifo[0]);
			close(fifo[1]);
			if (execlp("/bin/sh", "sh", "-c", argv[1], 0) == -1)
				exit(EXIT_FAILURE);
			break;
	}
	switch (pid2 = fork())
	{
		case -1:
			exit(EXIT_FAILURE);
			break;
		case 0:
			if (dup2(fifo[1], STDIN_FILENO) == -1)
				exit(EXIT_FAILURE);
			close(fifo[0]);
			close(fifo[1]);
			if (execlp("/bin/sh", "sh", "-c", argv[2], 0) == -1)
				exit(EXIT_FAILURE);
			break;
	}
	close(fifo[0]);
	close(fifo[1]);
	if (waitpid(pid1, &fifo[0], 0) != pid1 || waitpid(pid2, &fifo[1], 0) != pid2)
		exit(EXIT_FAILURE);
	return fifo[0] + fifo[1];
}