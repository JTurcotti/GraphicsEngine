#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"

int main() {
  struct matrix *transform = new_matrix(4, 4);
  ident(transform);
  struct matrix *edges = new_matrix(4, 50);
  screen s;
  clear_screen(s);
  parse_file("script.txt", transform, edges, s);
}
