#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"


/*======== void parse_file () ==========
Inputs:   char * filename 
          struct matrix * transform, 
          struct matrix * pm,
          screen s
Returns: 

Goes through the file named filename and performs all of the actions listed in that file.
The file follows the following format:
     Every command is a single character that takes up a line
     Any command that requires arguments must have those arguments in the second line.
     The commands are as follows:
         line: add a line to the edge matrix - 
	    takes 6 arguemnts (x0, y0, z0, x1, y1, z1)
	 ident: set the transform matrix to the identity matrix - 
	 scale: create a scale matrix, 
	    then multiply the transform matrix by the scale matrix - 
	    takes 3 arguments (sx, sy, sz)
	 translate: create a translation matrix, 
	    then multiply the transform matrix by the translation matrix - 
	    takes 3 arguments (tx, ty, tz)
	 rotate: create an rotation matrix,
	    then multiply the transform matrix by the rotation matrix -
	    takes 2 arguments (axis, theta) axis should be x y or z
	 apply: apply the current transformation matrix to the 
	    edge matrix
	 display: draw the lines of the edge matrix to the screen
	    display the screen
	 save: draw the lines of the edge matrix to the screen
	    save the screen to a file -
	    takes 1 argument (file name)
	 quit: end parsing

See the file script for an example of the file format


IMPORTANT MATH NOTE:
the trig functions int math.h use radian mesure, but us normal
humans use degrees, so the file will contain degrees for rotations,
be sure to conver those degrees to radians (M_PI is the constant
for PI)
====================*/
void parse_file ( char * filename, 
                  struct matrix * transform, 
                  struct matrix * edges,
                  screen s) {
  FILE *f;
  char line[256], argline[256];

  //color
  color c;
  c.green = MAX_COLOR;
  c.red = 0;
  c.blue = 0;
  //end color
  
  clear_screen(s);

  if ( strcmp(filename, "stdin") == 0 ) 
    f = stdin;
  else
    f = fopen(filename, "r");

  while ( fgets(line, 255, f) != NULL ) {

    line[strlen(line)-1]='\0'; //remove new line
    printf(":%s\n", line);

    if (!strcmp(line, "line")) {
      double *args = malloc(6 * sizeof(double));
      int nargs;
      if (!fgets(argline, 255, f) ||
	  ((nargs = sscanf(argline, "%lf %lf %lf %lf %lf %lf",
			   args, args+1, args+2, args+3, args+4, args+5)) != 6)) {
	printf("Error: 'line' requires 6 arguments of type double, found %d\n", nargs);
      } else {
	add_edge(edges, args[0], args[1], args[2], args[3], args[4], args[5]);
      }
      free(args);
    } else if (!strcmp(line, "ident")) {
      ident(transform);
    } else if (!strcmp(line, "scale")) {
      double *args = malloc(3 * sizeof(double));
      int nargs;
      if (!fgets(argline, 255, f) ||
	  ((nargs = sscanf(argline, "%lf %lf %lf", args, args+1, args+2)) != 3)) {
	printf("Error: 'scale' requires 3 arguments of type double, found %d\n", nargs);
      } else {
	transform = matrix_mult(make_scale(args[0], args[1], args[2]), transform);
      }
      
      free(args);
      
    } else if (!strcmp(line, "translate")) {
      double *args = malloc(3 * sizeof(double));
      int nargs;
      if (!fgets(argline, 255, f) ||
	  ((nargs = sscanf(argline, "%lf %lf %lf", args, args+1, args+2)) != 3)) {
	printf("Error: 'translate' requires 3 arguments of type double, found %d\n", nargs);
      } else {
	transform = matrix_mult(make_translate(args[0], args[1], args[2]), transform);
      }
      printf("\nTransform now: ");
      print_matrix(transform);
      free(args);
    } else if (!strcmp(line, "rotate")) {
      char *axis = malloc(1);
      double *theta = malloc(sizeof(double));
      if (!fgets(argline, 255, f) || (sscanf(argline, "%c %lf", axis, theta) != 2)) {
	printf("Error: 'rotate' requires both an axis and an angle\n");
      } else {
	if (*axis == 'x' || *axis == 'X') {
	  transform = matrix_mult(make_rotX(*theta), transform);
	} else if (*axis == 'y' || *axis == 'Y') {
	  transform = matrix_mult(make_rotY(*theta), transform);
	} else if (*axis == 'z' || *axis == 'Z') {
	  transform = matrix_mult(make_rotZ(*theta), transform);
	} else {
	  printf("Error: %c is not a valid axis\n", *axis);
	}
      }
      
    } else if (!strcmp(line, "apply")) {
      printf("\nEdges before transform: ");
      print_matrix(edges);
      edges = matrix_mult(transform, edges);
      printf("\nEdges now: ");
      print_matrix(edges);
    } else if (!strcmp(line, "display")) {
      draw_lines(edges, s, c);
    } else if (!strcmp(line, "save")) {
      draw_lines(edges, s, c);
      
      char *filename = malloc(32);
      if (!fgets(argline, 255, f) || (sscanf(argline, "%s", filename) == 0)) {
	printf("Error: 'save' requires a filename, none given\n");
      } else {
	printf("saving\n");
	save_ppm(s, filename);
      }
      free(filename);
    } else if (!strcmp(line, "quit")) {
      printf("Parse terminated\n");
      exit(0);
    } else {
      printf("Error: unrecognized command '%s'\n", line);
    }
			  
  }
}
  
