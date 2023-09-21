#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

double pythagore(double a, double b)
{
  return sqrt(a * a + b * b);
}

int main()
{
  double x, y;
  printf("x=");
  scanf("%lf", &x);
  printf("y=");
  scanf("%lf", &y);

  printf("l'hypothénuse = %lf", pythagore(x, y));

  printf("Test de la fonction pythagore:\n");
  assert(fabs(pythagore(3, 4) - 5) < 0.00001);
  assert(fabs(pythagore(1, 1) - sqrt(2)) < 0.00001);
  assert(fabs(pythagore(2.25, 10) - 10.25) < 0.00001);
  printf("La fonction pythagore semble bonne...\n\n");

  return EXIT_SUCCESS;
}