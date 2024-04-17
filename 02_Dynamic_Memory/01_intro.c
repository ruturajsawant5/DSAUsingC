#include <stdio.h>
#include <stdlib.h>

int main()
{
    int* ptr;

    ptr = (int*)malloc(sizeof(int));
    if(ptr == NULL)
    {
        printf("malloc() failed\n");
        exit(EXIT_FAILURE);
    }

    *ptr = 100;
    printf("*ptr = %d\n", *ptr);

    free(ptr);
    ptr = NULL;

    exit(EXIT_SUCCESS);
}