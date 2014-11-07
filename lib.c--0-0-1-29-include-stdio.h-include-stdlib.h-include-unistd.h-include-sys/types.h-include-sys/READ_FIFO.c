#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mylib.h"

#define FILE "./fifo_file.txt"

int main(int argc, char** argv)
{
	int fd = 0;
	int f = fork();
	char* buf = (char*)calloc(1024, sizeof(char));


	if (argc > 1)
	{
		perror("ARGUMENTS");
		exit(1);
	}

	fd = open(FILE, O_RDONLY);

	if (fd < 0)
	{
		perror("FIFO");
		exit(1);
	}

	new_read(fd, buf);
	new_write(buf, STDOUT_FILENO);
	close(fd);
	// мы не проходили такой функции - замените на изученные на семинарах

	//исправлено
	if (f = 0)
	{
		execlp("rm", "rm", FILE, NULL);
		perror("EXEC");
		exit(1);
	}

	return 0;
}

