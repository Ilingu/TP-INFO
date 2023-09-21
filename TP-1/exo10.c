#include <stdio.h>
#include <stdlib.h>

int main()
{
  unsigned int bs;
  printf("Quelle est la borne supérieur ? ");
  scanf("%d", &bs);

  float n, Hn = 0;
  for (float x = 0.0; x <= bs; x += 0.5)
  {
    while (Hn < x)
    {
      n += 1;
      Hn += 1 / n;
    }
    printf("f(%f) = %f\n", x, n);
  }

  return EXIT_SUCCESS;
}
