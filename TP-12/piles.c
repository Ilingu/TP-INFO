#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct argsHanoi
{
  int n;
  char start;
  char aux;
  char end;
} argsHanoi;

typedef argsHanoi any;

// pour adapter facilement le type des éléments des piles

struct stack_s
{
  int capacity;
  int size;
  any *data;
};

typedef struct stack_s stack;

stack *create(int c)
{
  stack *s = malloc(sizeof(stack));

  s->capacity = c;
  s->size = 0;
  s->data = calloc(c, sizeof(any));

  return s;
}

bool is_empty(stack *s)
{
  return s->size == 0;
}
// la pile est-elle vide ?

void push(stack *s, any a)
{
  if (s->size + 1 >= s->capacity)
    assert(false);
  s->data[s->size] = a;
  s->size++;
}
// ajoute l'élément a à la pile s

// void print(stack *s)
// {
//   for (int i = 0; i < s->capacity; i++)
//     printf("%d ", s->data[i]);
//   printf("\n");
// }

any pop(stack *s)
{
  if (is_empty(s))
    assert(false);
  s->size--;
  return s->data[s->size];
}
// extraction d'un élément de la pile s

void free_stack(stack *s)
{
  free(s->data);
  free(s);
}
// libération de la mémoire

int capacity(stack *s)
{
  return s->capacity;
}

any peek(stack *s)
{
  if (is_empty(s))
    assert(false);

  any head = pop(s);
  push(s, head);

  return head;
}

int size(stack *s)
{
  return s->size;
}

stack *copy(stack *s)
{
  stack *st = create(capacity(s));
  stack *sc = create(capacity(s));

  int sizec = size(s);
  for (int i = 0; i < sizec; i++)
    push(st, pop(s));
  for (int i = 0; i < sizec; i++)
  {
    any temp = pop(st);
    push(sc, temp);
    push(s, temp);
  }

  free_stack(st);
  return sc;
}

// bool egal(stack *s, stack *t)
// {
//   stack *sc = copy(s);
//   stack *tc = copy(t);

//   while (!is_empty(sc) && !is_empty(tc) && pop(sc) == pop(tc))
//   {
//   }

//   bool is_ok = is_empty(sc) && is_empty(tc);

//   free_stack(sc);
//   free_stack(tc);

//   return is_ok;
// }

void flush(stack *s)
{
  s->size = 0;
}

// bool egal_bis(stack *s, stack *t)
// {
//   if (size(s) != size(t))
//     return false;

//   for (int i = 0; i < size(s); i++)
//     if (s->data[i] != t->data[i])
//       return false;
//   return true;
// }

void hanoi_aux_rec(int n, char start, char aux, char end)
{
  if (n != 0)
  {
    hanoi_aux_rec(n - 1, start, end, aux);
    printf("%d from %c to %c\n", n, start, end);
    hanoi_aux_rec(n - 1, aux, start, end);
  }
}

// void hanoi_rec(int n)
// {
//   hanoi_aux_rec(n, 'A', 'B', 'C');
// }

void hanoi(int n)
{
  stack *s = create(3 * n);
  push(s, (argsHanoi){n, 'A', 'B', 'C'});
  while (!is_empty(s))
  {
    argsHanoi args = pop(s);
    if (args.aux == '\0')
    {
      printf("%d from %c to %c\n", args.n, args.start, args.end);
      continue;
    }

    if (args.n != 0)
    {
      push(s, (argsHanoi){args.n - 1, args.aux, args.start, args.end});
      push(s, (argsHanoi){args.n, args.start, '\0', args.end});
      push(s, (argsHanoi){args.n - 1, args.start, args.end, args.aux});
    }
  }
  free_stack(s);
}

int main()
{
  /*
  stack *s = create(5);
  print(s);
  push(s, 1);
  push(s, 2);
  assert(size(s) == 2);
  print(s);
  any two = pop(s);
  assert(size(s) == 1);
  assert(two == 2);
  push(s, 3);
  push(s, 4);
  print(s);

  assert(peek(s) == 4);
  assert(size(s) == 3);

  stack *sc = copy(s);
  print(sc);
  assert(egal(s, sc));

  stack *t = create(7);
  push(t, 1);
  assert(!egal(s, t));
  {
    push(t, 3);
    push(t, 4);
  }
  assert(egal(s, t));

  // free and exit
  free_stack(s);
  free_stack(t);
  free_stack(sc);
  */

  hanoi(3);

  return EXIT_SUCCESS;
}