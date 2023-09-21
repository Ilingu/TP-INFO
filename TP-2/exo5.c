#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

typedef uint64_t u64;

typedef struct couple
{
  int fst;
  int snd;
} couple;

int pgcd(int a, int b)
{
  if (b == 0)
    return a;
  return pgcd(b, a % b);
}

couple bezout(int a, int b)
{
  
}

int main()
{
  return EXIT_SUCCESS;
}