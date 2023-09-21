#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char minuscule(char c)
{
  if (c >= 65 && c <= 90)
    return c + 6 + 26;
  return c;
}

int main()
{
  char c;
  scanf("%c", &c);

  printf("%c\n", minuscule(c));

  printf("Test de la fonction miniscule:\n");
  assert(minuscule('A') == 'a');
  assert(minuscule('a') == 'a');
  assert(minuscule('1') == '1');
  printf("La fonction miniscule semble bonne...\n\n");

  return EXIT_SUCCESS;
}