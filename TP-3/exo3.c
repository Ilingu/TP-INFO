#include <stdlib.h>
#include <stdio.h>

void minmax(int x, int y, int *min, int *max)
{
  *max = x > y ? x : y;
  *min = x > y ? y : x;
}

int main()
{
  int max_value;
  int min_value;

  minmax(4, 6, &min_value, &max_value);
  printf("max=%d\nmin=%d", max_value, min_value);

  return EXIT_SUCCESS;
}