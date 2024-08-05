#include <stdio.h>
#include <string.h>

#include "constants.h"

// Stores lines that should be sorted.
char *g_lines[MAXLINES];
// Returns some space from buffer if available. Defined in the 'alloc.c'.
char *alloc_some_space(unsigned nbytes);
int readlines(char *lines[], unsigned maxlines) {
  char new_line[MAXLINE];
  unsigned
      line_len;  // Stores the length of 'new_line' (to not overrun new_line).
  unsigned nlines;
  char *storage_for_line;

  int get_line(char *line, unsigned maxline);

  nlines = 0;
  while ((line_len = get_line(new_line, MAXLINE)) > 0) {
    if (nlines + 1 >= maxlines ||
        (storage_for_line = alloc_some_space(line_len + 1)) == NULL) {
      return -1;
    } else {
      strcpy(storage_for_line, new_line);
      g_lines[nlines++] = storage_for_line;
    }
  }

  return nlines;
}
void writelines(char *lines[], unsigned nlines) {
  for (int i = 0; i < nlines; ++i) printf("%d -- %s\n", i, lines[i]);
}
int get_line(char *line, unsigned maxline) {
  char *startptr = line;
  char new_char;
  /*
  (line - startptr + 1) denotes the amount
  of bits already used plus one bit for '\0'
  */
  for (new_char = getchar(); line - startptr + 1 <= maxline;
       new_char = getchar()) {
    if (new_char == '\n' || new_char == EOF) {
      *line = '\0';
      break;
    } else {
      *line++ = new_char;
    }
  }
  // Returns the length of the inputted line.
  return line - startptr;
}
