#include <stdio.h>
#include <stdlib.h>

const int ASCII_LETTER = 97; // translation de l'alphabet, a=97-z=122
int max(int a, int b) { return a >= b ? a : b; }
int abs(int n) { return n >= 0 ? n : -n; }
char letter_pos_to_char(int pos) { return (char)(ASCII_LETTER + pos); }

int main()
{
  int nl;
  printf("Quelle est le nombres de lettres de la cible ? ");
  scanf("%d", &nl);

  if (nl < 1 || nl > 26)
    return EXIT_FAILURE;

  // point centré en (nl-1,nl-1)
  int xc = nl - 1, yc = nl - 1;

  int outer_ring_len = 2 * nl - 1;
  for (int y = 0; y < outer_ring_len; y++)
  {
    for (int x = 0; x < outer_ring_len; x++)
    {
      int dist_from_origin = max(abs(xc - x), abs(yc - y));
      int letter_pos = nl - 1 - dist_from_origin;
      printf("%c", letter_pos_to_char(letter_pos));
    }
    printf("\n");
  }

  return EXIT_SUCCESS;
}
