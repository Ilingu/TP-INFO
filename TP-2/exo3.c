#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

typedef uint64_t u64;

u64 quotient(u64 a, u64 b)
{
  u64 i = 0;
  while (a > 0)
  {
    if (a < b)
      return i;
    a -= b;
    i++;
  }
  return i;
}

int main()
{
  // double x, y;
  // printf("x=");
  // scanf("%lf", &x);
  // printf("y=");
  // scanf("%lf", &y);

  // printf("le quotient est de %d", quotient(x, y));

  printf("Test de la fonction quotient:\n");
  assert(quotient(100, 2) == 50);
  assert(quotient(101, 2) == 50);
  assert(quotient(101, 3) == 33);
  assert(quotient(102, 3) == 34);
  assert(quotient(861, 5) == 172);
  assert(quotient(861, 7) == 123);
  assert(quotient(861, 11) == 78);
  assert(quotient(861, 13) == 66);
  assert(quotient(861, 17) == 50);
  assert(quotient(861, 19) == 45);
  assert(quotient(861, 23) == 37);
  //   Vous pouvez décommenter le dernier test si vous avez confiance dans
  //   l'efficacité de votre fonction...
  assert(quotient((1ull << 60) - 1, 3) == 384307168202282325); // 10**60-1, 3
  printf("La fonction quotient semble bonne...\n\n");

  return EXIT_SUCCESS;
}