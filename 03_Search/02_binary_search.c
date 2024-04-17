#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

int binary_search(int* arr, int start, int end,  int search_term);
int compare_func(const void* a, const void* b);

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


    qsort(arr, N, sizeof(int), compare_func);//sort array
    start = clock();
    res = binary_search(arr, 0, N-1, search_term);
    end = clock();

    time_taken = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
    printf("Result = %d Time taken = %.2f\n", res, time_taken);

    free(arr);
}

int binary_search(int* arr, int start, int end, int search_term)
{
    int mid;

    if(start <= end)
    {
        mid = (start + end) / 2;
        
        if(search_term == arr[mid])
            return TRUE;
        else if(search_term < arr[mid])
            return binary_search(arr, start, mid-1, search_term);
        else
            return binary_search(arr, mid+1, end, search_term);
    }


    return FALSE;
}

int compare_func(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}
