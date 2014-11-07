#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mylib.h"

// что за дефайны? вы считаете что у меня на компьютере это тоже заработает?

//исправил
#define FILE1 "./fifo_file.txt"

int main(int argc, char** argv)
{
	int pipefd[2] = {0};
	int pp = pipe(pipefd);
	int error = 0;
	int frk = 0;
	int fd = 0;
	char* buf = (char*)calloc(1024, sizeof(char));

	if (argc > 2)

	{
		perror("ARGUMENTS");
		exit(1);
	}
	// првоеряет на ошибки сразу а не после 5 строк кода

	//не понял комментария выше
	if (pp == -1)
	{
		perror("PIPE");
		exit(1);
	}

	frk = fork();

	if (frk == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		execlp("ls", "ls", argv[1], "-l", NULL);
		printf("AAHHA\n");
		perror("EXEC");
		exit(1);
	}
	else if (frk < 0)
		perror("FORK_1");

        frk = fork();

        if (frk == -1)
                perror("FORK_2");

	if (frk == 0)
	{
		close(pipefd[1]);

		error = mkfifo(FILE1, 0666);
		if (error < 0)
		{
			perror("FIFO");
			exit(1);
		}

		fd = open(FILE1, O_WRONLY);
		if (fd < 0)
		{
			perror("OPEN");
			exit(1);
		}
		new_read(pipefd[0], buf);
		new_write(buf, fd);

		close(pipefd[0]);
	}

	else if (frk > 0)
	{
		close(pipefd[1]);
		close(pipefd[0]);
	}
	else
		printf("FORK_ERROR\n");

	return 0;

}
