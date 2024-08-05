#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>

void filecopy(int, int);
void error(char *fmt, ...);

int main(int argc, char *argv[])
{
	int fd0, fd1;

	if (argc != 3)
		error("too few arguments");

	if ((fd0 = open(argv[1], O_RDONLY)) == -1)
		error("can\'t open %s", argv[1]);

	if ((fd1 = creat(argv[2], 666)) == -1)
		error("can\'t open or create %s", argv[2]);

	filecopy(fd0, fd1);

	close(fd0);
	close(fd1);

	return 0;
}

void filecopy(int from, int to)
{
	char buf[BUFSIZ];
	int n;

	while ((n = read(from, buf, BUFSIZ)) > 0)
	{
		if (write(to, buf, n) != n)
		{
			perror("can\'t write to the destination file");
			exit(1);
		}
	}
}

void error(char *fmt, ...)
{
	va_list argv;

	va_start(argv, fmt);

	fprintf(stderr, "[error]: ");
	vfprintf(stderr, fmt, argv);
	fprintf(stderr, "\n");

	va_end(argv);

	exit(1);
}
