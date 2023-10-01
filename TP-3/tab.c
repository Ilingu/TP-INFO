#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  █████╗
// ██╔══██╗
// ███████║
// ██╔══██║
// ██║  ██║
// ╚═╝  ╚═╝

unsigned indice_max(int tab[], unsigned len)
{
  unsigned max_indice = 0;
  for (unsigned i = 0; i < len; i++)
    if (tab[i] > tab[max_indice])
      max_indice = i;
  return max_indice;
}

unsigned nb_occurrences_max(int tab[], unsigned len)
{
  int max = tab[0];
  unsigned occ_max = 0;
  for (unsigned i = 0; i < len; i++)
    if (tab[i] > max)
    {
      occ_max = 1;
      max = tab[i];
    }
    else if (tab[i] == max)
      occ_max++;
  return occ_max;
}

double deuxieme_plus_grand(double tab[], unsigned len)
{
  double max = tab[0] > tab[1] ? tab[0] : tab[1];
  double second_max = tab[0] > tab[1] ? tab[1] : tab[0];

  for (unsigned i = 0; i < len; i++)
  {
    if (tab[i] > max)
    {
      second_max = max;
      max = tab[i];
    }
    else if (tab[i] > second_max && tab[i] != max)
      second_max = tab[i];
  }
  return second_max;
}

double plus_petite_distance(double tab[], unsigned len)
{
  double min_dist = tab[0] - tab[1] > 0 ? tab[0] - tab[1] : tab[1] - tab[0];
  for (unsigned i = 0; i < len; i++)
    for (unsigned j = 0; j < len; j++)
    {
      if (i == j)
        continue;
      double dist = tab[j] - tab[i] > 0 ? tab[j] - tab[i] : tab[i] - tab[j];
      if (dist < min_dist)
        min_dist = dist;
    }
  return min_dist;
}

double plus_petite_distance_trie(double tab[], unsigned len)
{
  double min_dist = tab[1] - tab[0];
  for (unsigned i = 0; i < len - 1; i++)
  {
    double dist = tab[i + 1] - tab[i];
    if (dist < min_dist)
      min_dist = dist;
  }
  return min_dist;
}

bool maximum_local(int t[], unsigned len, unsigned i)
{
  return i != 0 && i != len - 1 && t[i - 1] < t[i] && t[i] > t[i + 1];
}

bool vrai_maximum_local(int t[], unsigned len, unsigned i)
{
  if (i == 0 && i == len - 1)
    return false;
  unsigned jlim = i > (len - i) ? i : len - i;
  for (unsigned j = 1; j < jlim; j++)
  {
    printf("%d - %d - %d", i - j, i, i + j);
    if (t[i - j] < t[i] && t[i] > t[i + j])
      return true;
  }
  return false;
}

// ██████╗
// ██╔══██╗
// ██████╔╝
// ██╔══██╗
// ██████╔╝
// ╚═════╝

void moyenne_des_elements_precedents(double t[], unsigned n)
{
  double sum = 0;
  for (unsigned i = 0; i < n; i++)
  {
    sum += t[i];
    t[i] = sum / (i + 1);
  }
}

void swap(int t[], unsigned i, unsigned j)
{
  int temp = t[i];
  t[i] = t[j];
  t[j] = temp;
}

void max_in_last_place(int t[], unsigned len)
{
  unsigned max_i = indice_max(t, len);
  swap(t, max_i, len - 1);
}

void selection_sort(int t[], int len)
{
  for (unsigned i = len; i > 1; i--)
    max_in_last_place(t, i);
}

bool is_increasing(int t[], unsigned len)
{
  for (unsigned i = 0; i < len - 1; i++)
    if (t[i] > t[i + 1])
      return false;
  return true;
}

//  ██████╗
// ██╔════╝
// ██║
// ██║
// ╚██████╗
//  ╚═════╝

unsigned longueur_chaine(char s[])
{
  unsigned len = 0;
  for (unsigned i = 0; s[i] != '\0'; i++)
    len++;
  return len;
}

void copie_chaine(char cible[], char source[])
{
  for (unsigned i = 0; source[i] != '\0'; i++)
    cible[i] = source[i];
}

void retirer_parc(char s[])
{
  for (unsigned i = 0; s[i] != '\0';)
    if (s[i] == 'p' || s[i] == 'a' || s[i] == 'r' || s[i] == 'c')
      for (unsigned j = i; s[j] != '\0'; j++)
        s[j] = s[j + 1];
    else
      i++;
}

// void rot13(char s[]);

// ███╗   ███╗ █████╗ ██╗███╗   ██╗
// ████╗ ████║██╔══██╗██║████╗  ██║
// ██╔████╔██║███████║██║██╔██╗ ██║
// ██║╚██╔╝██║██╔══██║██║██║╚██╗██║
// ██║ ╚═╝ ██║██║  ██║██║██║ ╚████║
// ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝

int main(void)
{
  {
    int t[] = {3, 4, 8};
    assert(indice_max(t, 3) == 2);
    int u[] = {2};
    assert(indice_max(u, 1) == 0);
    int v[] = {1, 1, 0, 1, 1, 0};
    assert(indice_max(v, 6) == 0);
  }
  {
    int t[] = {3, 4, 2, 4, 4};
    assert(nb_occurrences_max(t, 5) == 3);
    int u[] = {2, 2, 2, 1, 2};
    assert(nb_occurrences_max(u, 5) == 4);
    int v[] = {3, 5, 2, 0, 8};
    assert(nb_occurrences_max(v, 5) == 1);
  }
  {
    double t[] = {3., 4., 2., 8., 6.5, 5.};
    assert(deuxieme_plus_grand(t, 6) == 6.5);
    double u[] = {1., 1.5, 2., 2., 2.};
    assert(deuxieme_plus_grand(u, 5) == 1.5);
    double v[] = {0.5, -0.5};
    assert(deuxieme_plus_grand(v, 2) == -0.5);
    double w[] = {-0.5, 0.5};
    assert(deuxieme_plus_grand(w, 2) == -0.5);
  }
  {
      // double tab[] = {0, -4.3, 6.3, 5.6, 1., -3.1};
      // double d = plus_petite_distance(tab, 6);
      // printf("%b\n", d - .7 < 0.00001);
      // printf("%b\n", d - .7 > -0.00001);

      // assert((d - .7) < 0.00001 && (d - .7) > -0.00001);
  } {
    double tab[] = {-4.3, -3.1, 0, 1.2, 5.6, 6.3};
    double d = plus_petite_distance_trie(tab, 6);
    assert((d - .7) < 0.00001 && (d - .7) > -0.00001);
  }
  {
    int t[] = {1, 2, 3, 2, 1, -1, -2, -1, -3, 5, 5, 2};
    assert(!(maximum_local(t, 12, 0)));
    assert(maximum_local(t, 12, 2));
    assert(maximum_local(t, 12, 7));
    assert(!(maximum_local(t, 12, 9)));
    assert(!(maximum_local(t, 12, 11)));
  }
  // {
  //   int tab[] = {1, 2, 3, 2, 1, -1, -2, -1, -3, 5,
  //                5, 2, 3, 3, 3, 3, 1, 4, 4, 4};
  //   assert(!vrai_maximum_local(tab, 20, 0));
  //   assert(vrai_maximum_local(tab, 20, 2));
  //   assert(vrai_maximum_local(tab, 20, 7));
  //   assert(vrai_maximum_local(tab, 20, 9));
  //   assert(vrai_maximum_local(tab, 20, 12));
  //   assert(vrai_maximum_local(tab, 20, 13));
  //   assert(vrai_maximum_local(tab, 20, 14));
  //   assert(vrai_maximum_local(tab, 20, 15));
  //   assert(!vrai_maximum_local(tab, 20, 16));
  //   assert(!vrai_maximum_local(tab, 20, 18));
  //   assert(!vrai_maximum_local(tab, 20, 19));
  // }
  {
    double t[] = {1.0, 4.0, 9.0, 19.0, 29.0, 31.0, 10.0, 30.0, 15.0, 31.0,
                  2.0, 19.0, 20.0, 25.0, 41.0, 28.0, 24.0, 36.0, 16.0, 16.0};
    moyenne_des_elements_precedents(t, 20);
    assert(t[0] == 1.0);
    assert(t[1] == 2.5);
    assert(t[9] == 17.9);
    assert(t[19] == 20.3);
  }
  {
    int t[] = {1, 2, 3, 2, 1, -1, -2, -1, -3, 5, 5, 2};
    selection_sort(t, 12);
    assert(is_increasing(t, 12));
    int u[] = {861};
    selection_sort(u, 1);
    assert(is_increasing(u, 1));
    int v[] = {1, 4, 9, 19, 29, 31, 10, 30, 15, 31,
               2, 19, 20, 25, 41, 28, 24, 36, 16, 16};
    selection_sort(v, 20);
    assert(is_increasing(v, 20));
  }
  // {
  //   char s[] =
  //       "object-oriented programming is an exceptionally bad idea which could "
  //       "only have originated in california. -- Dijkstra";
  //   assert(nb_occurrences('a', s) == 10);
  //   assert(nb_occurrences(' ', s) == 15);
  //   assert(nb_occurrences('z', s) == 0);
  // }
  {
    char src[] = "abcdefghijklmnopqrstuvwxyz";
    char tgt[] = "zyxwvutsrqponmlkjihgfedcba";
    copie_chaine(tgt, src);
    assert(strcmp(src, tgt) == 0);
  }
  {
    char s[] =
        "object-oriented programming is an exceptionally bad idea which could "
        "only have originated in california. -- Dijkstra";
    retirer_parc(s);
    char res[] =
        "objet-oiented ogmming is n exetionlly bd ide whih ould only hve "
        "oiginted in lifoni. -- Dijkst";
    assert(strcmp(s, res) == 0);
  }
  return 0;
}
