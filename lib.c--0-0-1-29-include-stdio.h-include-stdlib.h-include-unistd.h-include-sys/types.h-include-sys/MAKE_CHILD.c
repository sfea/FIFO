#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// что за дефайны? вы считаете что у меня на компьютере это тоже заработает?
#define FOLDER "/home-local/student/Загрузки"
#define FILE1 "/home-local/student/Загрузки/fifo_file.txt"

int main(int argc, char** argv)
{
	int pipefd[2] = {0};
	int pp = pipe(pipefd);
	int error = 0;
	int frk = 0;
	int fd = 0;

	if (argc > 2)
		printf("ERROR_IN_COUNT_OF_ARG\n");
	// првоеряет на ошибки сразу а не после 5 строк кода
	if (pp == -1)
		printf("PIPE_ERROR\n");

	frk = fork();

	if (frk == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		execlp("ls", "ls", FOLDER, "-l", NULL);
		printf("EXEC_ERROR\n");
	}
	else if (frk < 0)
		printf("FORK_ERROR\n");

        frk = fork();

        if (frk == -1)
                printf("FORK_ERROR\n");

	if (frk == 0)
	{
		close(pipefd[1]);

		error = mkfifo(FILE1, 0666);
		if (error < 0)
			printf("ERROR_IN_FIFOFILE_CREATING\n");

		fd = open(FILE1, O_WRONLY);
		if (fd < 0)
			printf("ERROR_IN_OPENING_FILE\n");
		old_new(pipefd[0], fd);

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
