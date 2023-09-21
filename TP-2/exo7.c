#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int josephe(int n)
{
  if (n == 2)
    return 1;
  if (n == 3)
    return 3;

  int p = n / 2;
  if (n % 2 == 0)
    return 2 * josephe(p) - 1;

  int res = josephe(p + 1);
  if (res == 1)
    return n;
  return 2 * res - 3;
}

int main()
{
  int n;
  printf("n=");
  scanf("%d", &n);

  printf("j(%d)=%d\n", n, josephe(n));

  return EXIT_SUCCESS;
}