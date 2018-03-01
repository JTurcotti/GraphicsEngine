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
  
  
  /*
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
  color green, red, blue, yellow, purple;
  green.green = 255;
  yellow.green = 255;
  red.red = 255;
  purple.red = 255;
  yellow.red = 255;
  blue.blue = 255;
  purple.blue = 255;
  
  clear_screen(s);

  draw_lines(center, s, green);
  draw_lines(corner1, s, red);
  draw_lines(corner2, s, blue);
  draw_lines(corner3, s, yellow);
  draw_lines(corner4, s, purple);
  

  save_extension(s, "matout.png");

  clear_screen(s);
  
  struct matrix *main = new_matrix(4, 250);
  add_matrix(main, center);
  add_matrix(main, corner1);
  add_matrix(main, corner2);
  add_matrix(main, corner3);
  add_matrix(main, corner4);

  draw_lines(main, s, green);

  save_extension(s, "matout2.png");
  */
  //display(s);
}
