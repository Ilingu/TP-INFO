#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//  _____ __   _ _______  ______  _____
//    |   | \  |    |    |_____/ |     |
//  __|__ |  \_|    |    |    \_ |_____|

typedef uint64_t ui;

#define HEAP_SIZE 32

ui heap[HEAP_SIZE];

ui heap_index(ui *p)
{
  return p - heap;
}

void pre_initialize_heap(void)
{
  for (ui i = 0; i < HEAP_SIZE; i++)
  {
    heap[i] = 0xFFFFFFFF;
  }
}

void print_heap(void)
{
  for (ui i = 0; i < HEAP_SIZE; i++)
  {
    ui x = heap[i];
    if (x == 0xFFFFFFFF)
    {
      printf("... ");
    }
    else
    {
      printf("%3llu ", (long long unsigned)x);
    }
  }
  printf("\n");
}

void set_memory(ui *p, ui size, ui value)
{
  for (ui i = 0; i < size; i++)
  {
    p[i] = value;
  }
}

//  _______ _______                _____  _______
//  |  |  | |_____| |      |      |     | |
//  |  |  | |     | |_____ |_____ |_____| |_____

ui prologue = 3;

void add_begin_chain(ui i)
{
  heap[i] = 0;
  heap[i + 1] = heap[1];
  if (heap[1] != 0)
    heap[heap[1]] = i;
  heap[1] = i;
}

void remove_from_chain(ui i)
{
  heap[heap[i] + 1] = heap[i + 1];
  if (heap[i + 1] != 0)
    heap[heap[i + 1]] = heap[i];
}

void init_heap(void)
{
  heap[0] = 3;
  heap[1] = 0;
  heap[2] = 1;
  heap[3] = 1;
}

bool is_free(ui i)
{
  return heap[i] % 2 == 0;
}

ui read_size(ui i)
{
  return heap[i] - 1;
}

void set_free(ui i, ui size)
{
  heap[i] = size;
  add_begin_chain(i + 1);
  heap[i + size + 1] = size;
}

void set_used(ui i, ui size)
{
  heap[i] = size + 1;
  heap[i + size + 1] = size + 1;
}

ui next(ui i)
{
  return is_free(i) ? i + heap[i] + 2 : i + read_size(i) + 2;
}

ui previous(ui i)
{
  return is_free(i - 1) ? i - heap[i - 1] - 2 : i - read_size(i - 1) - 2;
}

ui *grow_epilogue(ui size)
{
  if (heap[0] - 1 + size + 1 + 2 >= HEAP_SIZE)
    return NULL;

  set_used(heap[0] - 1, size);

  heap[heap[0] - 1 + size + 1 + 1] = 1;
  heap[heap[0] - 1 + size + 1 + 2] = 1;
  ui temp_user = heap[0];
  heap[0] = heap[0] - 1 + size + 1 + 2;

  return &heap[temp_user];
}

ui *malloc_ui64(ui size)
{
  if (size == 0)
    return NULL;
  if (size % 2 == 1)
    size++;

  if (heap[0] == 3)
  {
    if (2 + 2 + 1 + size + 1 + 2 >= HEAP_SIZE)
      return NULL;

    set_used(4, size);

    heap[1 + 2 + 1 + size + 1 + 1] = 1;
    heap[1 + 2 + 1 + size + 1 + 2] = 1;
    heap[0] = 1 + 2 + 1 + size + 1 + 2;

    return &heap[5];
  }

  if (heap[1] == 0)
    return grow_epilogue(size);

  ui free_space = heap[1];
  while (heap[free_space - 1] < size)
  {
    if (heap[free_space + 1] == 0)
      return grow_epilogue(size);

    free_space = heap[free_space + 1];
  }
  free_space--;

  // realloc
  remove_from_chain(free_space + 1);
  if (heap[free_space] - size >= 4)
  {
    ui remaining_size = heap[free_space] - size - 2;
    heap[free_space + size + 2] = remaining_size;
    add_begin_chain(free_space + size + 2 + 1);
    heap[free_space + size + 2 + remaining_size + 1] = remaining_size;
  }
  else
    size = heap[free_space];

  set_used(free_space, size);
  return &heap[free_space + 1];
}

void free_ui64(ui *p)
{
  ui i = heap_index(p) - 1;
  set_free(i, read_size(i));
  while (is_free(i - 1) && is_free(i))
  {
    remove_from_chain(i + 1);

    ui n = next(i), p = previous(i);
    remove_from_chain(p + 1);

    ui new_size = heap[i - 1] + heap[i] + 2;
    heap[n - 1] = new_size;
    heap[p] = new_size;
    add_begin_chain(p + 1);

    // epilogue
    if (n == heap[0] - 1)
    {
      remove_from_chain(p + 1);
      heap[p] = 1;
      heap[p + 1] = 1;
      heap[0] = p + 1;
      break;
    }
    i = n;
  }
}

int main(void)
{
  pre_initialize_heap();

  init_heap();
  print_heap();

  ui *p1 = malloc_ui64(2);
  set_memory(p1, 2, 42);
  print_heap();
  ui *p2 = malloc_ui64(2);
  set_memory(p2, 2, 52);
  print_heap();
  ui *p3 = malloc_ui64(2);
  set_memory(p3, 2, 62);
  print_heap();
  ui *p4 = malloc_ui64(2);
  set_memory(p4, 2, 72);
  print_heap();
  ui *p5 = malloc_ui64(1);
  set_memory(p5, 1, 82);
  print_heap();
  ui *p6 = malloc_ui64(1);
  set_memory(p6, 1, 92);
  print_heap();

  printf("\nFin des allocations initiales \n");

  free_ui64(p1);
  print_heap();
  free_ui64(p5);
  print_heap();
  free_ui64(p3);
  print_heap();
  free_ui64(p6);
  print_heap();
  free_ui64(p2);
  print_heap();

  printf("\nAllocation d'un bloc de taille 10, initialisé à 69.\n");
  ui *p7 = malloc_ui64(10);
  set_memory(p7, 10, 69);
  print_heap();

  printf("\nLibération de ce bloc.\n");
  free_ui64(p7);
  print_heap();

  printf("\nAllocation de taille 8.\n");
  p7 = malloc_ui64(8);
  set_memory(p7, 8, 99);
  print_heap();
}
