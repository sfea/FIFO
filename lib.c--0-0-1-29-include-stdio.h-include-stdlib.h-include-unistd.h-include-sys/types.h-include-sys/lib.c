#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

extern int old_new(int old_fd, int new_fd)
{
	char buf[1024] = {0};
	int re = 1;
	int wr = 0;

	while (re > 0)
	{
		re = read(old_fd, buf, 1024);

		if (re < 0)
		return -1;

		wr = write(new_fd, buf, re);

		if (wr < 0)
		return -1;

		if (re < 1024 || buf[0] == '\0')
		break;
	}
}
