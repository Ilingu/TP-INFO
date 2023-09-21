#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint64_t u64;

u64 binom(u64 n, u64 p)
{
  u64 result = 1;
  for (u64 i = 1; i <= p; i++)
    result *= ((n + 1 - i) / i);
  return result;
}

int main()
{
  printf("Test de la fonction binom:\n");
  for (u64 n = 0; n < 10; n++)
  {
    for (u64 p = 0; p < 10; p++)
    {
      if (p > n)
        continue;
      printf("%ld ", binom(n, p));
    }
    printf("\n");
  }

  return EXIT_SUCCESS;
}