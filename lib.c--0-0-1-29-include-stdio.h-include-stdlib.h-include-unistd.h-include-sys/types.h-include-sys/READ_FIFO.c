#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILE "/home-local/student/Загрузки/fifo_file.txt"

int main(int argc, char** argv)
{
	int fd = 0;
	
	if (argc > 1)
		printf("INVALID_COUNT_OF_ARGS\n");

	fd = open(FILE, O_RDONLY);

	if (fd < 0)
		printf("ERROR_WITH_FIFOFILE_OPENING\n");

	old_new(fd, STDOUT_FILENO);
	
	close(fd);
	unlink(FILE);
	return 0;
}
