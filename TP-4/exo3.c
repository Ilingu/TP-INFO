#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct intarr
{
  unsigned len;
  int *data;
} intarr;

intarr *new_array(unsigned len)
{
  intarr *t = malloc(sizeof(intarr));
  int *data = calloc(len, sizeof(int));

  t->len = len;
  t->data = data;

  return t;
}

int array_get(intarr *t, unsigned i)
{
  assert(i <= t->len - 1);
  return t->data[i];
}

void array_set(intarr *t, int i, int x)
{
  assert(i <= t->len - 1);
  t->data[i] = x;
}

void array_clear(intarr *t)
{
  free(t);
}

void display_array(intarr *t)
{
  for (unsigned i = 0; i < t->len; i++)
    printf("%d, ", t->data[i]);
  printf("\n");
}

const unsigned LEN = 5;

int main()
{
  intarr *t = new_array(LEN);
  display_array(t);
  array_set(t, 2, 4);
  printf("%d\n", array_get(t, 2));
  display_array(t);
  array_clear(t);

  return EXIT_SUCCESS;
}