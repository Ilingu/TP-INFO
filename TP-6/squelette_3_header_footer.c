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

ui prologue = 2;

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

void init_heap(void)
{
  heap[0] = 2;
  heap[1] = 1;
  heap[2] = 1;
}

ui *malloc_ui64(ui size)
{
  if (size == 0)
    return NULL;
  if (size % 2 == 1)
    size++;

  if (heap[0] == 2)
  {
    if (2 + 1 + size + 1 + 2 >= HEAP_SIZE)
      return NULL;

    set_used(3, size);

    heap[2 + 1 + size + 1 + 1] = 1;
    heap[2 + 1 + size + 1 + 2] = 1;
    heap[0] = 2 + 1 + size + 1 + 2;

    return &heap[4];
  }

  for (unsigned i = 3; i < HEAP_SIZE;)
  {
    if (is_free(i))
    {
      if (heap[i] < size)
        continue;

      // realloc
      if (heap[i] - size > 2)
      {
        ui remaining_size = heap[i] - size - 2;
        heap[i + size + 2] = remaining_size;
        heap[i + size + 2 + remaining_size + 1] = remaining_size;
      }
      set_used(i, size);

      return &heap[i + 1];
    }

    // epilogue
    if (i == heap[0] - 1)
    {
      if (i + size + 1 + 2 >= HEAP_SIZE)
        return NULL;

      set_used(i, size);

      heap[i + size + 1 + 1] = 1;
      heap[i + size + 1 + 2] = 1;
      heap[0] = i + size + 1 + 2;

      return &heap[i + 1];
    }
    i = next(i);
  }
  return NULL;
}

void free_ui64(ui *p)
{
  ui i = heap_index(p) - 1;
  set_free(i, read_size(i));
  if (is_free(i - 1))
  {
    ui n = next(i), p = previous(i);
    ui new_size = heap[i - 1] + heap[i] + 2;
    heap[n - 1] = new_size;
    heap[p] = new_size;

    // epilogue
    if (n == heap[0] - 1)
    {
      heap[p] = 1;
      heap[p + 1] = 1;
      heap[0] = p + 1;
    }
  }
}

int main(void)
{
  pre_initialize_heap();
  init_heap();

  ui *p = malloc_ui64(8);
  set_memory(p, 8, 33);

  ui *q = malloc_ui64(2);
  set_memory(q, 2, 44);

  free_ui64(p);
  print_heap();

  ui *r = malloc_ui64(7);
  set_memory(r, 7, 55);

  free_ui64(r);
  free_ui64(q);
  print_heap();

  ui *p1 = malloc_ui64(6);
  ui *p2 = malloc_ui64(7);
  ui *p3 = malloc_ui64(1);
  print_heap();

  set_memory(p1, 6, 42);
  set_memory(p2, 7, 52);
  set_memory(p3, 1, 62);
  print_heap();

  free_ui64(p2);
  print_heap();

  ui *p4 = malloc_ui64(2);
  set_memory(p4, 2, 72);
  print_heap();

  free_ui64(p3);
  print_heap();
}
