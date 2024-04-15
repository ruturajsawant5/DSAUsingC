#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int** pparr;
    int N = 200;
    int i;

    srand((unsigned int)time(NULL)); //seed

    pparr = (int**)malloc(N * sizeof(int *));
    if(pparr == NULL)
    {
        puts("malloc() failed");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < N; i++)
    {
        pparr[i] = (int*)malloc(sizeof(int));
        if(pparr[i] == NULL)
        {
            puts("malloc() failed");
            exit(EXIT_FAILURE);
        }
    }

    for(i = 0; i < N; i++)
        *pparr[i] = rand();

    for(i = 0; i < N; i++)
        printf("%d=%d\n", i+1, *pparr[i]);


    for(i = 0; i < N; i++)
    {
        free(pparr[i]);
        pparr[i] = NULL;
    }

    free(pparr);
}