#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

int linear_search(int* arr, int size, int search_term);

int main(int argc, char* argv[])
{
    int N;
    int* arr;
    int search_term = INT_MAX;
    int i;
    clock_t start, end;
    double time_taken;
    int res;

    srand((unsigned int)time(NULL));//seed

    if(argc < 2)
    {
        puts("Usage Error: Missing argument");
        exit(EXIT_FAILURE);
    }

    N = atoi(argv[1]);

    arr = (int*)malloc(sizeof(int) * N);
    if(arr == NULL)
    {
        puts("malloc() failed");
        exit(EXIT_FAILURE);
    }
    
    for(i = 0; i < N; i++)
        arr[i] = rand() % N;

    start = clock();
    res = linear_search(arr, N, search_term);
    end = clock();

    time_taken = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
    printf("Result = %d Time taken = %.2f", res, time_taken);
}

int linear_search(int* arr, int size, int search_term)
{
    int i;

    for(i = 0; i < size; i++)
    {
        if(arr[i] == search_term)
            return TRUE;
    }

    return FALSE;
}

