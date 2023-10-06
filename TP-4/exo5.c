#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

typedef struct complexe
{
  double re;
  double im;
} complexe;

double xmin = -2.0;
double xmax = 1.0;
double ymin = -1.5;
double ymax = 1.5;

void next(complexe *z, complexe *c)
{
  complexe zn1;
  zn1.re = (z->re * z->re) - (z->im * z->im) + c->re;
  zn1.im = 2.0 * z->re * z->im + c->im;

  z->re = zn1.re;
  z->im = zn1.im;
}

double modulus_square(complexe *z)
{
  return z->re * z->re + z->im * z->im;
}

int divergence(complexe *c, int itermax)
{
  complexe z;
  {
    z.re = 0;
    z.im = 0;
  }

  for (int n = 0; n < itermax; n++)
  {
    if (modulus_square(&z) > 4)
      return n;
    next(&z, c);
  }
  return itermax + 1;
}

complexe indices_vers_complexe(int ligne, int colonne, int n)
{
  complexe z;
  z.re = xmin + ((xmax - xmin) / n) * colonne;
  z.im = ymin + ((ymax - ymin) / n) * ligne;
  return z;
}

void remplir_matrice(int **t, int n, int itermax)
{
  for (int ligne = 0; ligne < n; ligne++)
    for (int colonne = 0; colonne < n; colonne++)
    {
      complexe c = indices_vers_complexe(ligne, colonne, n);
      t[ligne][colonne] = divergence(&c, itermax);
    }
}

void afficher_matrice(int **t, int n, int itermax)
{
  printf("P2\n");
  printf("%d %d\n", n, n);
  printf("%d\n", itermax + 1);
  for (int ligne = 0; ligne < n; ligne++)
  {
    for (int colonne = 0; colonne < n; colonne++)
      if (colonne == n - 1)
        printf("%d", t[ligne][colonne]);
      else
        printf("%d ", t[ligne][colonne]);
    printf("\n");
  }
}

int main(int argc, char const *argv[])
{
  int n = 100, itermax = 20;
  // Gestion des arguments de la ligne de commandes
  for (unsigned i = 1; i < (unsigned)argc; i++)
  {
    if (strcmp(argv[i], "-z") == 0 && i + 4 < (unsigned)argc)
      xmin = atof(argv[i + 1]), xmax = atof(argv[i + 2]), ymin = atof(argv[i + 3]), ymax = atof(argv[i + 4]);

    if (strcmp(argv[i], "-imax") == 0 && i + 1 < (unsigned)argc)
      itermax = atoi(argv[i + 1]);
    if (strcmp(argv[i], "-n") == 0 && i + 1 < (unsigned)argc)
      n = atoi(argv[i + 1]);
  }

  // Création de la matrice sur le tas
  int **t = malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++)
    t[i] = malloc(n * sizeof(int));

  // Travail sur la matrice
  remplir_matrice(t, n, itermax);
  afficher_matrice(t, n, itermax);

  // on libère la mémoire !
  for (int i = 0; i < n; i++)
    free(t[i]);
  free(t);

  return 0;
}
