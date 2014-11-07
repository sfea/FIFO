#include <unistd.h>
#include <string.h>

// extern - убрать, сделать с заголовчным файлом .h

// чтение и запись у вас не буферизованные - нужно проверять, что за раз момет не считаться
// запршаиваемое количестов байт. Надо разделить на две функции - считывание и запись .

int new_read(int old_fd, char* buf)
{
	int re = 1;
	int i = 1;

	for (i = 1;;i++)
	{
		if (re = read(old_fd, buf, 1024) == 1024)
			buf = realloc(buf, i*1024);
		else
		{
			buf = realloc(buf, (i - 1)*1024 + re); 
			break;
		}

		if (re < 0)
			return -1;
	}
}

int new_write(char* buf, int new_fd)
{
	int wr = write(new_fd, buf, (int)strlen(buf));

	if (wr < 0)
		return -1;
}
