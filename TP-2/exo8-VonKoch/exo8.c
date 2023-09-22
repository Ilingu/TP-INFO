#include <stdio.h>
#include <stdlib.h>
#include "turtle.h"
#include <math.h>
#include <time.h>

// #include <stdint.h>

unsigned segment_size = 10; // pixels
void von_koch(unsigned n)
{
  int r = rand() % 255; // Returns a pseudo-random integer between 0 and RAND_MAX.
  int g = rand() % 255; // Returns a pseudo-random integer between 0 and RAND_MAX.
  int b = rand() % 255; // Returns a pseudo-random integer between 0 and RAND_MAX.

  turtle_set_pen_color(r, g, b);
  if (n == 0)
  {
    turtle_forward(segment_size);
    return;
  }

  von_koch(n - 1);
  turtle_turn_left(60);
  von_koch(n - 1);
  turtle_turn_right(120);
  von_koch(n - 1);
  turtle_turn_left(60);
  von_koch(n - 1);
}

int main()
{
  srand(time(NULL)); // Initialization, should only be called once.

  unsigned n;
  printf("n=");
  scanf("%d", &n);

  unsigned width = segment_size * pow(3.0, (double)n);
  unsigned height = segment_size * pow(3.0, (double)(n - 1));

  turtle_init(width, height);
  {
    turtle_pen_up();
    turtle_goto(-(int)width / 2, -(int)height / 2);
    turtle_pen_down();
  }
  von_koch(n); // random RGB colors

  turtle_save_bmp("exemple.bmp");
  return EXIT_SUCCESS;
}