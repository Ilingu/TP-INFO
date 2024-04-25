#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct noeud {
  int etiquette;
  struct noeud* g;
  struct noeud* d;
};

typedef struct noeud arbre;

arbre* cn(int n, arbre* g, arbre* d) {
    arbre* new_noeud = malloc(sizeof(arbre));
    new_noeud->etiquette = n;
    new_noeud->g = g;
    new_noeud->d = d;
    return new_noeud;
}

arbre* cf(int n) {
    return cn(n, NULL, NULL);
}

void libere_arbre(arbre* a) {
  if (a->g != NULL) libere_arbre(a->g);
  if (a->d != NULL) libere_arbre(a->d);
  if (a != NULL) free(a);
}

// arbre* reconstruction(int* parcours, int n) {} TODO

struct noeud_cousu {
  int etiquette;
  bool sous_arbre_droit;
  struct noeud_cousu* g;
  struct noeud_cousu* d;
};

typedef struct noeud_cousu arbre_cousu;

arbre_cousu* atelier_de_couture_aux(arbre* t, arbre_cousu* couture, arbre_cousu* last_infixe) {
  couture->etiquette=t->etiquette;
  couture->sous_arbre_droit= t->d != NULL;

  arbre_cousu* sacd = malloc(sizeof(arbre_cousu));
  arbre_cousu* sacg = malloc(sizeof(arbre_cousu));

  arbre_cousu* g;
  arbre_cousu* d;

  if (t->g == NULL) g = NULL;
  else g = atelier_de_couture_aux(t->g, sacg, couture);

  if (t->d == NULL) d = last_infixe;
  else d = atelier_de_couture_aux(t->d, sacd, last_infixe);

  couture->g = g;
  couture->d = d;

  return couture;
}

arbre_cousu* atelier_de_couture(arbre* t) {
  arbre_cousu* sac = malloc(sizeof(arbre_cousu));
  return atelier_de_couture_aux(t, sac, sac);
}

void libere_arbre_cousu(arbre_cousu* a) {
  if (a->g != NULL) libere_arbre_cousu(a->g);
  if (a->sous_arbre_droit) libere_arbre_cousu(a->d);
  if (a != NULL) free(a);
}

void push_char(char** str, char c) {
    size_t len = strlen(*str);
    *str = realloc(*str, len + 2); // Allocate space for the new character and the null terminator
    if (*str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    (*str)[len] = c; // Insert the new character
    (*str)[len + 1] = '\0'; // Update the null terminator
}


void print_arbre_cousu(arbre_cousu* a, char* space) {
  printf("%s%d\n", space, a->etiquette);
  push_char(&space,' ');
  if (a->g != NULL) print_arbre_cousu(a->g, space);
  if (a->d != NULL) print_arbre_cousu(a->d, space);
}


int main(void) {
  char* space = malloc(sizeof(char));
  arbre* a = cn(1, cn(2, cf(3), cn(4, cf(5), cf(6))), cn(7, NULL, cn(8, cf(9), NULL)));
  arbre_cousu* ac = atelier_de_couture(a);
  print_arbre_cousu(ac, space);

  free(space);
  libere_arbre(a);
  libere_arbre_cousu(ac);
  return EXIT_SUCCESS;
}