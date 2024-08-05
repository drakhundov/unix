#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "field.h"

#define MAXFIELDS 15

// Used to sort different parts of the input separately.
static field fields[MAXFIELDS];
int nfields;   // Number of fields the program should process.
int fieldidx;  // Index of the field currently being worked on.
options g_params;
field empty_field = {0};
extern char *g_lines[];
int readlines(char *lines[], unsigned maxlines);
void writelines(char *lines[], unsigned nlines);
void quick_sort(void *v[], int left, int right, int (*comp)(void *, void *));
void swap_values_of_ptr_arr(void *v[], int i, int j);
void report_error(char *fmt, ...);
int compare_nums(double *v1, double *v2);
int compare_strs(char *s, char *t);
int main(int argc, char *argv[]) {
  int nlines;
  int field_pos_no;  // 0 for start, 1 for end
  char option;       // A letter that denotes an option parsed from 'argv'.
  field_pos_no = 0;
  fieldidx = 0;
  fields[0] = empty_field;
  while (--argc > 0 && *++argv) {
    if (isdigit(*argv[0])) {
      if (fieldidx > MAXFIELDS - 1) {
        report_error("Too much fields (maximum %d).", MAXFIELDS);
      }
      if (field_pos_no == 0) {
        fields[fieldidx].start = atof(*argv);
        field_pos_no++;
      } else if (field_pos_no == 1) {
        fields[fieldidx].end = atof(*argv);
        field_pos_no++;
      } else {
        field_pos_no = 0;
      }
    } else if ('-' == *argv[0]++) {
      while (option = *argv[0]++) {
        switch (option) {
          case 'n':
            fields[fieldidx].params.sort_as_numeric = true;
            break;
          case 'r':
            fields[fieldidx].params.return_reversed = true;
            break;
          case 'f':
            fields[fieldidx].params.ignore_case = true;
            break;
          case 'd':
            fields[fieldidx].params.ignore_spaces = true;
            break;
          case 'h': {
            FILE *help_file = fopen("help.txt", "r");
            char c;
            while ((c = getc(help_file)) != EOF) putchar(c);
            return 0;
          }

          case '-':
            break;

          default:
            report_error("Invalid parameter %c.", option);
        }
      }
      ++fieldidx;
    }
  }
  nfields = fieldidx;
  g_params = fields[0].params;
  fieldidx = 0;
  if ((nlines = readlines(g_lines, MAXLINES)) >= 0) {
    if (fields[0].start == 0) {
      fields[0].start = 1;
      fields[0].end = nlines;
      nfields = 1;
    }
    int start, end;
    for (; fieldidx < nfields;) {
      start = fields[fieldidx].start - 1;
      end = fields[fieldidx].end - 1;
      quick_sort((void **)g_lines, start, end,
                 (int (*)(void *, void *))(
                     g_params.sort_as_numeric ? compare_nums : compare_strs));
      if (g_params.return_reversed) {
        for (int i = start; i <= end / 2; ++i) {
          swap_values_of_ptr_arr((void **)g_lines, i, end - i);
        }
      }
      // Go to next field.
      g_params = fields[++fieldidx].params;
    }
    writelines(g_lines, nlines);

    return 0;
  } else {
    report_error("Type some lines, please.");
  }
}
void swap_values_of_ptr_arr(void *v[], int i, int j) {
  char *tmp;

  tmp = v[i];
  v[i] = v[j];
  v[j] = tmp;
}
