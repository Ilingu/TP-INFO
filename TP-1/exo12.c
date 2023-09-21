#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(unsigned n);

int main()
{
  unsigned n;
  printf("Quelle est la borne supérieur ? ");
  scanf("%d", &n);

  // O(n*sqrt(n)), I didn't want to implement Sieve of Eratosthenes in c due to the lack of data structures...
  for (unsigned i = 1; i <= n; i++)
    printf("%d%s\n", i, is_prime(i) ? " est premier" : " n'est pas premier");

  return EXIT_SUCCESS;
}

bool is_prime(unsigned n)
{
  if (n == 1)
    return false;

  for (unsigned i = 2; i <= sqrt(n); i++)
    if (n % i == 0)
      return false;
  return true;
}