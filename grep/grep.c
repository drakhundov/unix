#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 1000

int _fgets(char *s, int n, FILE *ifp);
int _strindex(char *s, char *t);
int _strcmp(char *s, char *t);

struct options
{
    unsigned int lineno : 1; // print line no.
    unsigned int except : 1; // search lines without pattern
};

/* find all overlaps in string */

int main(int argc, char *argv[])
{
    char ln[MAXLINE], *pattern;
    long lineno = 0;
    int c, count = 0;

    struct options opts = {0, 0};

    FILE *fp = stdin;

    while (--argc > 0 && (c = (*++argv)[0]) == '-')
    {
        c = *(++argv[0]);

        switch (c)
        {
        case 'x':
            opts.except = 1;
            break;

        case 'n':
            opts.lineno = 1;
            break;

        case 'f':
            fp = fopen(*++argv, "r");
            break;

        case 'h':
            printf("    grep --flags pattern\n");
            printf("    -n - print number of line\n");
            printf("    -x - print all except\n");
            printf("    -f file\n");
            exit(0);

        default:
            printf("illegal option %c\n", c);
            count = -1;
            argc = 0;
        }
    }

    pattern = *argv;

    if (argc == 0)
    {
        fprintf(stderr, "pattern is required\n");
        exit(1);
    }

    while (_fgets(ln, MAXLINE, fp) > 0)
    {
        ++lineno;
        if ((_strindex(ln, pattern) != -1) != opts.except && /* string is't empty */ !(_strcmp(ln, "\n") == 0))
        {
            if (opts.lineno)
                printf("%ld: ", lineno);

            printf("%s", ln);
            ++count;
        }
    }

    return count;
}

int _fgets(char *s, int n, FILE *ifp)
{
    register int c;
    register char *cs;

    cs = s;
    while (--n > 0 && (c = getc(ifp)) != EOF)
    {
        if ((*cs++ = c) == '\n')
            break;
    }

    *cs = '\0';

    return strlen(s);
}

int _strindex(char *s, char *t)
{
    int i, j, k;

    for (i = 0; s[i] != '\0'; ++i)
    {
        for (j = i, k = 0; t[k] != '\0' && t[k] == s[j]; ++k, ++j)
            ;

        if (k != 0 && t[k] == '\0')
            return i;
    }

    return -1;
}

int _strcmp(char *s, char *t)
{
    while (*s++ == *t++)
        if (*s == '\0')
            return 0;

    return ((*s - *t) > 0) ? 1 : -1;
}
