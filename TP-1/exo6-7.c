#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int print_if_even(int i) {
    if (i%2==0) printf("%d est pair\n", i);
} 

int main(void) {
    int i;
    printf("a=");
    scanf("%d", &i);

    printf("|a|=%d\n", abs(i));
    print_if_even(i);

    return 0;
}