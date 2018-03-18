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
void add_point(struct matrix * points, double x, double y, double z) {
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

void add_edge(struct matrix * points, 
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
void draw_lines(struct matrix * points, screen s, color c) {
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
  int x = x0 - ddx;

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

  int y = y0 - ddy;

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
  //printf("Drawing line (%d, %d) -> (%d, %d)\n", x0, y0, x1, y1);
  
  if (x0 == x1) {
    int y;
    int dy = (y1 > y0)? 1: -1;;
    for (y = y0; y != y1; y += dy) {
      plot(s, c, x0, y);
    }
  } else if (y0 == y1) {
    int x;
    int dx = (x1 > x0)? 1: -1;
    for (x = x0; x != x1; x += dx) {
      plot(s, c, x, y0);
    }
  } else if (abs(y1 - y0) == abs(x1 - x0)) {
    int dx = (x1 > x0)? 1: -1;
    int dy = (y1 > y0)? 1: -1;
    int i, x = x0, y = y0;
    for (i = 0; i <= abs(x1 - x0); i++) {
      plot(s, c, x, y);
      x += dx;
      y += dy;
    }
  } else if (abs(y1 - y0) < abs(x1 - x0)) {
    draw_shallow(x0, y0, x1, y1, s, c);
  } else {
    draw_steep(x0, y0, x1, y1, s, c);
  }
  /*color cr;
  cr.red = 255;
  cr.green = 0;
  cr.blue = 0;
  plot(s, cr, x0, y0);
  plot(s, cr, x1, y1);*/
}

/*======== void add_circle() ==========
  Inputs:   struct matrix * points
            double cx
            double cy
            double r
            double step
  Returns:
>
  Adds the circle at (cx, cy) with radius r to points
  ====================*/
void add_circle(struct matrix * points,
                 double cx, double cy, double cz,
                 double r, double step ) {
  double steps = -1 * step;
  while ((steps += step) <= 1) {
    add_edge(points,
	     cx + r * cos(TAO * steps), cy + r * sin(TAO * steps), cz,
	     cx + r * cos(TAO * (steps + step)), cy + r * sin(TAO * (steps + step)), cz);
  }
}

/*
Adds the curve bounded by the 4 points passsed as parameters
of type specified in type (see matrix.h for curve type constants)
to the matrix points
====================*/
void add_curve(struct matrix *points,
                double x0, double y0,
                double x1, double y1,
                double x2, double y2,
                double x3, double y3,
                double step, int type ) {
  struct matrix *coeff_trans;
  if (type == BEZIER) {
    coeff_trans = make_bezier();
  } else if (type == HERMITE) {
    coeff_trans = make_hermite();
  } else {
    printf("Error invalid curve type %d, expected 0 (HERMITE) or 1 (BEZIER)\n", type);
    return;
  }

  struct matrix *coeff = new_matrix(4, 2);
  coeff->m[0][0] = x0;
  coeff->m[0][1] = y0;
  coeff->m[1][0] = x1;
  coeff->m[1][1] = y1;
  coeff->m[2][0] = x2;
  coeff->m[2][1] = y2;
  coeff->m[3][0] = x3;
  coeff->m[3][1] = y3;
  coeff->lastcol = 1;

  coeff = matrix_mult(coeff_trans, coeff);

  double steps = -1 * step;
  struct matrix *time = new_matrix(1, 4);
  struct matrix *prev_point = NULL;
  struct matrix *point = NULL;
  while ((steps += step) <= 1) {
    time->m[0][0] = 1;
    time->m[0][1] = steps;
    time->m[0][2] = steps * steps;
    time->m[0][3] = steps * steps * steps;
    time->lastcol = 3;
    point = matrix_mult(time, coeff);

    if (prev_point)
      add_edge(points, prev_point->m[0][0], prev_point->m[0][1], 0,
	       point->m[0][0], point->m[0][1], 0);

    prev_point = point;
  }
}
	     
void add_box(struct matrix *points, double x, double y, double z, double x_depth, double y_depth, double z_depth) {
  double vals[3] = {x, y, z};
  double depths[3] = {x_depth, y_depth, z_depth};
  int i, a, b;
  for (i = 0; i < 3; i++) {
    for (a = 0; a < 2; a++) {
      for (b = 0; b < 2; b++) {
	double xyz0[3], xyz1[3];
	xyz0[i] = vals[i];
	xyz0[(i + 1) % 3] = vals[(i + 1) % 3] + a * depths[(i + 1) % 3];	
	xyz0[(i + 2) % 3] = vals[(i + 2) % 3] + b * depths[(i + 2) % 3];

	xyz1[i] = vals[i] + depths[i];
	xyz1[(i + 1) % 3] = xyz0[(i + 1) % 3];
	xyz1[(i + 2) % 3] = xyz0[(i + 2) % 3];
	add_edge(points, xyz0[0], xyz0[1], xyz0[2], xyz1[0], xyz1[1], xyz1[2]);
      }
    }
  }
}

struct matrix *generate_sphere(double cx, double cy, double cz, double r, double step) {
  assert(r > 0);
  struct matrix *points = new_matrix(4, 100);

  double steps1 = -1 * step;
  double z, cr, step2, steps2;
  while ((steps1 += step) <= 1) {
    z = cz + r * cos(PI * steps1);
    cr = r * sin(PI * steps1);
    
    step2 = cr < .01? 2: step * r / cr;
    steps2 = -1 * step2;
    while ((steps2 += step2) <= 1) {
      add_point(points, cx + cr * cos(TAO * steps2), cy + cr * sin(TAO * steps2), z);
    }
  }
  
  return points;
}

void add_sphere(struct matrix *points, double cx, double cy, double cz, double r, double step) {
  struct matrix *sphere_points = generate_sphere(cx, cy, cz, r, step);
  print_matrix("sphere points", sphere_points);
  int i;
  for (i = 0; i <= sphere_points->lastcol; i++) {
    add_circle(points, sphere_points->m[0][i], sphere_points->m[1][i], sphere_points->m[2][i], 1, step);
  }
}

  
    
