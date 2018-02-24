#ifndef MATRIX_H
#define MATRIX_H
#include <assert.h>

struct matrix {
  double **m;
  int rows, cols;
  int lastcol;
} matrix;

//Basic matrix manipulation routines
struct matrix *new_matrix(int rows, int cols);
void free_matrix(struct matrix *m);
void grow_matrix(struct matrix *m, int newcols);
void copy_matrix(struct matrix *a, struct matrix *b);

//functions students need to complete
void print_matrix(struct matrix *m);
void ident(struct matrix *m);
struct matrix *matrix_mult(struct matrix *a, struct matrix *b);

#endif
