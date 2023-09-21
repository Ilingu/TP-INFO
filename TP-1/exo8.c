int main() {
    int i;
    printf("Quelle est la borne supérieur de ");
    scanf("%d", &i);

    printf("0! = 1\n");
    unsigned long fact = 1;
    for (unsigned int j = 1; j <= i; j++)
    {
        fact *= j;
        printf("%d! = %d\n", j, fact);
    }
    

    return 0;
}