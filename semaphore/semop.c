#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>

struct sembuf sbuf[2] = {{0, -1, SEM_UNDO | IPC_NOWAIT}, {1, 0, 1}};

int main(void)
{
	int	fd;
	int	perms;

	perms = S_IRWXU | S_IRWXG | S_IRWXO;
	fd = semget(100, 2, IPC_CREAT | perms);
	if (fd == -1)
	{
		perror("semget");
		exit(EXIT_FAILURE);
	}
	if (semop(fd, sbuf, 2) == -1)
	{
		perror("semop");
		exit(EXIT_FAILURE);
	}
	return (0);
}