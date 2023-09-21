#include <stdio.h>
#include <stdlib.h>

float ABS(float n)
{
    return n < 0 ? -n : n;
}

float f(float x, float k)
{
    return x * x - k;
}

float dichotomie(float a, float b, float k)
{
    float avg_x = (a + b) / 2.0;
    if (ABS(f(avg_x, k)) < 0.001)
        return avg_x;
    if (f(avg_x, k) < 0)
        return dichotomie(avg_x, b, k);
    else
        return dichotomie(a, avg_x, k);
}

int main(void)
{
    float k;
    printf("racine de ");
    scanf("%f", &k);

    if (k < 0)
        return EXIT_FAILURE;

    // resolvons par dicothomie: x²-k=0
    printf("la racine est %f\n", dichotomie(1.0, k, k));

    return EXIT_SUCCESS;
}
