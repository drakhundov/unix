#include <stdio.h>

#include "constants.h"

#define BUFSIZE (MAXLINES * MAXLINE)

// Buffer is an area in memory where information can be stored temporarily.
static char allocbuf[BUFSIZE];
// A pointer to the free space.
// Will be moved forward every time some space is allocated.
static char *allocptr = allocbuf;
char *alloc_some_space(unsigned nbytes) {
  if (allocbuf + BUFSIZE - 1 - allocptr >= nbytes) {
    allocptr += nbytes;
    return allocptr - nbytes;
  } else {
    return NULL;
  }
}
