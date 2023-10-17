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

const ui block_size = 8;

void init_heap(void)
{
  heap[0] = 1;
}

bool is_free(ui i)
{
  return heap[i] == 0;
}

void set_free(ui i)
{
  heap[i] = 0;
}

void set_used(ui i)
{
  heap[i] = 1;
}

ui *malloc_ui64(ui size)
{
  if (size >= 8)
    return NULL;

  for (unsigned i = 0; i < (HEAP_SIZE / 8) - 1; i++)
  {
    unsigned block_index = 8 * i + 1;
    if (is_free(block_index))
    {
      heap[0] += 8;
      set_used(block_index);
      return &heap[block_index + 1];
    }
  }
  return NULL;
}

void free_ui64(ui *p)
{
  ui block_index = heap_index(p) - 1;
  set_free(block_index);
  if (block_index == heap[0])
    heap[0] -= 8;
}

int main(void)
{
  init_heap();
  ui *p1 = malloc_ui64(6);
  ui *p2 = malloc_ui64(3);
  set_memory(p1, 6, 42);
  set_memory(p2, 3, 52);
  print_heap();
  ui *p3 = malloc_ui64(5);
  set_memory(p3, 5, 62);
  print_heap();
  free_ui64(p2);
  print_heap();
  free_ui64(p3);
  print_heap();
}
