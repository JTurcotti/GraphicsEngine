#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
  assert(points->rows == 4);
  
  int col = points->lastcol + 1;

  if (col >= points->cols) {
    grow_matrix(points, col * 2);
  }

  points->m[0][col] = x;
  points->m[1][col] = y;
  points->m[2][col] = z;
  points->m[3][col] = 1;

  points->lastcol++;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/

int check_even(struct matrix *points) {
  if (points->lastcol % 2 == 0) {
    printf("Error: noneven number of points, adding origin\n");
    add_point(points, 0, 0, 0);
    return 1;
  }
  return 0;
}

void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
  check_even(points);
  
  add_point(points, x0, y0, z0);
  add_point(points, x1, y1, z1);
}

void add_matrix(struct matrix *points, struct matrix *mo_points) {

  assert(points->rows == 4 && mo_points->rows == 4);
  check_even(points);

  int col;
  for (col = 0; col <= mo_points->lastcol; col++) {

    add_point(points, mo_points->m[0][col],
	      mo_points->m[1][col], mo_points->m[2][col]);
  }

}	   

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
  assert(points->rows == 4);
  
  int i;

  for (i = 0; i < (points->lastcol + 1) / 2; i++) {
    draw_line(points->m[0][2 * i], points->m[1][2 * i],
	      points->m[0][2 * i + 1], points->m[1][2 * i + 1], s, c);
  }
}

int abs(int a) {
  return a >= 0? a: -1 * a;
}

void draw_shallow(int x0, int y0, int x1, int y1, screen s, color c) {
  //printf("Shallow Input (%d, %d) -> (%d, %d)\n", x0, y0, x1, y1);

  //ternary operators account for both positive and negative slopes

  int dx = abs(x1 - x0);
  int ddx = (x1 >= x0)? 1: -1;

  int dy = abs(y0 - y1);
  int ddy =  (y1 >= y0)? 1: -1;
  
  int line_sum = 2 * dy - dx;
  int y = y0;
  int x = x0 - 1;

  //  printf("Initial (%d, %d); ddy: %d\n", x, y, ddy);
  
  while ((x += ddx) != x1) {
    plot(s, c, x, y);

    if (line_sum > 0) {
      y += ddy;
      line_sum -= 2 * dx;
    }

    line_sum += 2 * dy;
  }
}

void draw_steep(int x0, int y0, int x1, int y1, screen s, color c) {
  //  printf("Steep Input (%d, %d) -> (%d, %d)\n", x0, y0, x1, y1);
  
  //x and y switched from abovex
  int dx = abs(x1 - x0);
  int ddx = (x1 >= x0)? 1: -1;

  int dy = abs(y0 - y1);
  int ddy =  (y1 >= y0)? 1: -1;
	    
  int line_sum = 2 * dx - dy;
  int x = x0;

  int y = y0 - 1;

  //  printf("Initial (%d, %d); ddx: %d\n", x, y, ddx);
  
  while ((y += ddy) != y1) {

    plot(s, c, x, y);
    
    if (line_sum > 0) {
      x += ddx;
      line_sum -= 2 * dy;
    }
    
    line_sum += 2 * dx;
  }
}

//Insert your line algorithm here
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  if (abs(y1 - y0) < abs(x1 - x0))
    draw_shallow(x0, y0, x1, y1, s, c);
  else
    draw_steep(x0, y0, x1, y1, s, c);
}
