#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <fcntl.h>

void filecopy(int inf, int outf);
void error(char *fmt, ...);

char *prog;

int main(int argc, void *argv[])
{
	int fd; // file descriptor
	extern char *prog;
	prog = argv[0];

	if (argc == 1)
	{
		filecopy(0, 1); // stdin to stdout
	}
	else
	{
		while (--argc > 0)
		{
			if ((fd = open(*++argv, O_RDONLY, 0)) == -1)
			{
				error("can't open '%s'", *argv);
			}
			else
			{
				filecopy(fd, 1);
				close(fd);
			}
		}
	}

	return 0;
}

void filecopy(int inf, int outf)
{
	char buf[BUFSIZ];
	int n;

	while ((n = read(inf, buf, BUFSIZ)) > 0)
	{
		if (write(outf, buf, n) != n)
		{
			error("cant write to output file");
		}
	}
}

void error(char *fmt, ...)
{
	va_list argv;

	extern char *prog;

	va_start(argv, fmt);

	fprintf(stderr, "[%s/error]: ", prog);
	vfprintf(stderr, fmt, argv);
	fprintf(stderr, "\n");

	va_end(argv);

	exit(1);
}
