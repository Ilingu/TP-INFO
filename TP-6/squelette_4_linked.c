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

ui heap_index(ui* p) {
  return p - heap;
}

void pre_initialize_heap(void) {
  for (ui i = 0; i < HEAP_SIZE; i++) {
    heap[i] = 0xFFFFFFFF;
  }
}

void print_heap(void) {
  for (ui i = 0; i < HEAP_SIZE; i++) {
    ui x = heap[i];
    if (x == 0xFFFFFFFF) {
      printf("... ");
    } else {
      printf("%3llu ", (long long unsigned)x);
    }
  }
  printf("\n");
}

void set_memory(ui* p, ui size, ui value) {
  for (ui i = 0; i < size; i++) {
    p[i] = value;
  }
}

//  _______ _______                _____  _______
//  |  |  | |_____| |      |      |     | |
//  |  |  | |     | |_____ |_____ |_____| |_____

ui prologue = 3;

void add_begin_chain(ui i);

void remove_from_chain(ui i);

void init_heap(void);

ui* malloc_ui64(ui size);

void free_ui64(ui* p);

int main(void) {
  pre_initialize_heap();

  init_heap();
  print_heap();

  ui* p1 = malloc_ui64(2);
  set_memory(p1, 2, 42);
  print_heap();
  ui* p2 = malloc_ui64(2);
  set_memory(p2, 2, 52);
  print_heap();
  ui* p3 = malloc_ui64(2);
  set_memory(p3, 2, 62);
  print_heap();
  ui* p4 = malloc_ui64(2);
  set_memory(p4, 2, 72);
  print_heap();
  ui* p5 = malloc_ui64(1);
  set_memory(p5, 1, 82);
  print_heap();
  ui* p6 = malloc_ui64(1);
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
  ui* p7 = malloc_ui64(10);
  set_memory(p7, 10, 69);
  print_heap();

  printf("\n Libération de ce bloc, puis allocation de taille 8.\n");
  free_ui64(p7);
  p7 = malloc_ui64(8);
  set_memory(p7, 8, 99);
  print_heap();
}
