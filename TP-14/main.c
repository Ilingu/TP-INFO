#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

struct noeud {
  int etiquette;
  struct noeud* g;
  struct noeud* d;
};
typedef struct noeud tree;

tree* new_node(int x, tree*g, tree*d) {
  tree* t = malloc(sizeof(tree));
  t->d=d;
  t->g=g;
  t->etiquette=x;
  return t;
}

tree* new_leaf(int x) {
  return new_node(x, NULL, NULL);
}

void destruction(tree* t) {
  if (t==NULL) return;

  destruction(t->d);
  destruction(t->g);

  free(t);
}

int taille(tree *t) {
  if(t==NULL) return 0;
  return taille(t->d) + taille(t->g) + 1;
}

int hauteur(tree *t) {
  if(t==NULL) return 0;
  return (taille(t->d) > taille(t->g) ? taille(t->d):taille(t->g)) + 1;
}

bool est_parfait(tree* t) {
  return (double)taille(t) == pow(2.0, (double)hauteur(t))-1.0;
}

int main(void) {
  tree *t = new_node(1, new_leaf(2), new_node(3, new_leaf(2),new_leaf(2)));
  printf("%d\n", est_parfait(t));

  destruction(t);
  return EXIT_SUCCESS;
}