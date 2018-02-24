#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  struct matrix *A = new_matrix(2, 3);
  double r1[] = {1, 2, 3};
  A->m[0] = r1;
  double r2[] = {2, 3, 4};
  A->m[1] = r2;

  struct matrix *B = new_matrix(3, 4);
  double s1[] = {1, 2, 3, 4};
  double s2[] = {0, 0, 0, 0};
  double s3[] = {2, 3, 4, 5};
  B->m[0] = s1;
  B->m[1] = s2;
  B->m[2] = s3;

  struct matrix *Id3 = new_matrix(3, 3);
  ident(Id3);

  printf("Matrix A (2 x 3):\n");
  print_matrix(A);

  printf("Matrix B (3 x 4):\n");
  print_matrix(B);

  printf("Matrix Id3 (3 x 3):\n");
  print_matrix(Id3);

  printf("Matrix A x B:\n");
  print_matrix(matrix_mult(A, B));

  printf("Matrix A x Id3:\n");
  print_matrix(matrix_mult(A, Id3));

  struct matrix *center = new_matrix(4, 125);
  struct matrix *corner1 = new_matrix(4, 125);
  struct matrix *corner2 = new_matrix(4, 125);
  struct matrix *corner3 = new_matrix(4, 125);
  struct matrix *corner4 = new_matrix(4, 125);
  int i, x, y;

  for (i = 0; i < 125; i++) {
    x = 500 - 2*i;
    y = 250 + 2*i;
    add_edge(center, 250, 250, 0, x, y, 0);
    add_edge(corner1, 500, 500, 0, x, y, 0);

    x = 250 - 2*i;
    y = 500 - 2*i;
    add_edge(center, 250, 250, 0, x, y, 0);
    add_edge(corner2, 0, 500, 0, x, y, 0);
    
    x = 2*i;
    y = 250 - 2*i;
    add_edge(center, 250, 250, 0, x, y, 0);
    add_edge(corner3, 0, 0, 0, x, y, 0);
    
    x = 250 + 2*i;
    y = 2*i;
    add_edge(center, 250, 250, 0, x, y, 0);
    add_edge(corner4, 500, 0, 0, x, y, 0);
  }

  screen s;
  color green, red, blue;
  green.green = 255;
  red.red = 255;
  blue.blue = 255;
  struct matrix *edges;

  clear_screen(s);

  draw_lines(center, s, green);
  draw_lines(corner1, s, blue);
  draw_lines(corner2, s, red);
  draw_lines(corner3, s, blue);
  draw_lines(corner4, s, red);
  

  save_extension(s, "matout.png");

  //display(s);
}
