#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>

typedef uint32_t ui;

const int BLOCK_SIZE = 2;
const int RADIX = 1<<BLOCK_SIZE;
const int MASK = RADIX-1;

void print_array(ui* t, int len){
    if (len > 20) { len = 20; }
    for (int i = 0; i < len; i++){
        printf("%llu\n", (long long unsigned)t[i]);
    }
    printf("\n");
}

bool is_sorted(ui *arr, int len){
    for (int i = 0; i < len - 1; i++){
        if (arr[i] > arr[i + 1]){
            return false;
        }
    }
    return true;
}

ui* rand_array(int len){
    ui* t = malloc(len * sizeof(ui));
    for (int i = 0; i < len; i++){
        t[i] = (ui)rand() * (ui)rand();
    }
    return t;
}


void copy(ui* out, ui* in, int len) {
    for (int i = 0; i < len; i++)
        out[i] = in[i];
}

void zero_out(ui* arr, int len) {
    for (int i = 0; i < len; i++)
        arr[i] = 0;
}

ui extract_digit(ui n, int k) {
    return (n>>(k*BLOCK_SIZE))&MASK;
}

ui* histogram(ui* arr, int len, int k) {
    ui* hist = calloc(RADIX, sizeof(ui));
    for (int i = 0; i<RADIX; i++) {
        hist[extract_digit(arr[i], k)]++;
    }
    return hist;
}

ui* prefix_sums(ui* hist, int len) {
    ui* sums = calloc(RADIX, sizeof(ui));
    for (int i=0; i<RADIX; i++) {
        ui sum = 0;
        for (int j = 0; j<=i-1; j++) {
            sum+=hist[j];
        }
    }
    return sums;
}

void radix_pass(ui* out, ui* in, int len, int k) {
    ui* hist = histogram(in, len, k);
    ui* sums = prefix_sums(hist, len);
    for (int i = 0; i<len; i++) {
        
    }
}

int main(void){
    // 11 01 01 11 01
    printf("%u\n", extract_digit(861, 5));
    return EXIT_SUCCESS;
}
