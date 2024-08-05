#include <stdbool.h>
#include <ctype.h>

#include "field.h"

extern options g_params;
int compare_nums(double *v1, double *v2)
{
    /*
     ! If values are originally strings, 'atof' shall
     ! be used before passing them to the function.
     */
    if (*v1 > *v2)
        return 1;
    else if (*v1 < *v2)
        return -1;
    else
        return 0;
}
int compare_strs(char *s, char *t)
{
    bool fold = g_params.ignore_case;
    bool dir = g_params.ignore_spaces;
    for (; *s == *t; ++s, ++t)
    {
        if (dir)
        {
            if (*s == ' ' || *s == '\t')
                ++s;
            if (*t == ' ' || *t == '\t')
                ++t;
        }
        if (fold)
        {
            *s = tolower(*s);
            *t = tolower(*t);
        }
        // The loop will check if 's' and 't' are equal anyway.
        if (*s == '\0')
            return 0;
    }
    return ((*s - *t) > 0) ? 1 : -1;
}
