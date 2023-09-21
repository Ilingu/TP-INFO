#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void hanoi(unsigned nb_disque)
{
  unsigned a[nb_disque];
  unsigned b[nb_disque];
  unsigned c[nb_disque];
  for (unsigned i = 0; i < nb_disque; i++)
  {
    a[i] = 0;
    b[i] = 0;
    c[i] = 0;
  }

  for (size_t i = 0; i < nb_disque; i++)
    printf("%d\n", a[i]);
}

int main()
{
  hanoi(10);

  return EXIT_SUCCESS;
}