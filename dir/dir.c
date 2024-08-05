#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include <sys/stat.h>

#include <dirent.h>

enum opts
{
	_SIZE = 0b100000,
	_ATIME = 0b010000, // time last accessed
	_MTIME = 0b001000, // time last modified
	_INO = 0b000100,   // inode
	_USRID = 0b000010, // user id
	_GRPID = 0b000001  // group id
};

int opts = 0;

void dirwalk(char *, void (*)(char *));
void print_stats(char *);

int main(int argc, char *argv[])
{
	extern int opts;

	while (--argc > 0 && (*++argv)[0] == '-')
	{
		if (strcmp(*argv, "-atime") == 0)
			opts |= _ATIME;
		else if (strcmp(*argv, "-mtime") == 0)
			opts |= _MTIME;
		else if (strcmp(*argv, "-usrid") == 0)
			opts |= _USRID;
		else if (strcmp(*argv, "-grpid") == 0)
			opts |= _GRPID;
		else if (strcmp(*argv, "-size") == 0)
			opts |= _SIZE;
		else if (strcmp(*argv, "-ino") == 0)
			opts |= _INO;
	}

	if (argc == 0) // no files given, process current directory
	{
		dirwalk(".", print_stats);
	}
	else
	{
		while (argc-- > 0)
		{
			dirwalk(*argv++, print_stats);
		}
	}

	return 0;
}

void print_stats(char *name)
{
	struct stat stbuf;
	extern int opts;

	if (stat(name, &stbuf) == -1)
	{
		fprintf(stderr, "can't access to %s\n", name);
		return;
	}

	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, print_stats);

	puts(name);

	if (opts & _SIZE)
		printf("	size - %d", stbuf.st_size);

	if (opts & _ATIME)
		printf("    last accessed - %d", stbuf.st_atime);

	if (opts & _MTIME)
		printf("    last modified - %d", stbuf.st_mtime);

	if (opts & _INO)
		printf("    inode - %d", stbuf.st_ino);

	if (opts & _USRID)
		printf("    user id - %d", stbuf.st_uid);

	if (opts & _GRPID)
		printf("    group id - %d", stbuf.st_gid);

	puts("\n\n");
}

/* implement 'func' on every dir file (and subdir files too) */
void dirwalk(char *dirname, void (*func)(char *))
{
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dfd;

	if ((dfd = opendir(dirname)) == NULL)
	{
		fprintf(stderr, "error: can't access %s\n", dirname);
		return;
	}

	while ((dp = readdir(dfd)) != NULL)
	{
		// skip entry to itself and the parent
		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
			continue;

		if (strlen(dirname) + strlen(dp->d_name) + 2 > sizeof(name))
		{
			fprintf(stderr, "error: name %s\\%s is too long\n", dirname, dp->d_name);
		}
		else
		{
			sprintf(name, "%s\\%s", dirname, dp->d_name);
			(*func)(name);
		}
	}

	closedir(dfd);
}
