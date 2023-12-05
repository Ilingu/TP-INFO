#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define seed 603
// #define dodu_seed = 861;

#define TAILLE 100000

uint64_t U[TAILLE + 1];

uint64_t suite(uint64_t n, uint64_t u0)
{
  uint64_t un = u0;
  for (unsigned i = 0; i < n; i++)
  {
    un = (1234567891 * un + 9876543211) % 861861023;
  }
  return un;
}

void remplir_tab(uint64_t u0)
{
  U[0] = u0;
  for (uint64_t i = 1; i <= TAILLE; i++)
    U[i] = (1234567891 * (U[i - 1]) + 9876543211) % 861861023;
}

void print_tab()
{
  for (size_t i = 0; i <= TAILLE; i++)
  {
    printf("%ld ", U[i]);
  }
  printf("\n");
}

#define d 20232024

uint64_t Rn(uint64_t n)
{
  uint64_t res = 0;
  for (uint64_t i = 0; i < n; i++)
  {
    uint64_t ukmod = U[i] % d;
    uint64_t powres = (ukmod * ukmod) % d;

    for (uint64_t j = 0; j < (U[i + 1] - 2); j++)
      powres = (powres * ukmod) % d;
    res += powres;
  }
  return res;
}

uint64_t *compute_u42()
{
  uint64_t *u42 = malloc(sizeof(uint64_t) * (TAILLE + 1));
  for (uint64_t i = 0; i <= TAILLE; i++)
    u42[i] = U[i] % 42;
  return u42;
}

uint64_t Hn(uint64_t n)
{
  uint64_t *u42 = compute_u42();

  uint64_t area_max = 0;
  for (uint64_t i = 0; i < n; i++)
  {
    uint64_t hi = u42[i];
    uint64_t mostr = n - i;
    uint64_t mostl = i + 1;

    for (uint64_t delta_r = 1; delta_r <= (n - i - 1); delta_r++)
      if (u42[i + delta_r] < hi)
      {
        mostr = delta_r;
        break;
      }

    for (uint64_t delta_l = 1; delta_l <= i; delta_l++)
      if (u42[i - delta_l] < hi)
      {
        mostl = delta_l;
        break;
      }

    uint64_t area_hi = (mostr + mostl - 1) * hi;
    if (area_hi > area_max)
      area_max = area_hi;
  }

  free(u42);
  return area_max;
}

int main(void)
{
  remplir_tab(seed);
  printf("%lu\n", Hn(TAILLE));
  return EXIT_SUCCESS;
}
