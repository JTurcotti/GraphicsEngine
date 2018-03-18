#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"

int main(int nargs, char *args[]) {
  char *input;
  srand(time(NULL));
  if (nargs < 2) {
    fprintf(stderr, "please provide input filename\n");
    return -1;
  } else {
    printf("reading input script: '%s'\n", args[1]);
    input = args[1];
  }
  parse_file(input);
}
