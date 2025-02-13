#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void report_error(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "[error]: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
