#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* get_array(int* pN);
void get_array2(int** parr, int* pN);
void fill_array(int* arr, int N);
void show_array(int* arr, int N);

int main()
{
    int N;
    int* arr1;
    int* arr2;

    srand((unsigned int)time(NULL)); //seed

    arr1 = get_array(&N);
    fill_array(arr1, N);
    show_array(arr1, N);

    get_array2(&arr2, &N);
    fill_array(arr2, N);
    show_array(arr2, N);
    
    free(arr1);
    free(arr2);
}

int* get_array(int* pN)
{
    int* ptr;
    int N = 50;

    ptr = (int*)malloc(sizeof(int) * N);
    if(ptr == NULL)
    {
        puts("malloc() failed");
        exit(EXIT_FAILURE);
    }

    *pN = N;

    return ptr;
}

void get_array2(int** parr, int* pN)
{
    int* ptr;
    int N = 100;

    ptr = (int*)malloc(sizeof(int) * N);
    if(ptr == NULL)
    {
        puts("malloc() failed");
        exit(EXIT_FAILURE);
    }

    *pN = N;
    *parr = ptr;
}

void fill_array(int* arr, int N)
{
    int i;
    
    for(i = 0; i < N; i++)
        arr[i] = rand();

}
void show_array(int* arr, int N)
{
    int i;
    
    printf("\nARRAY CONTENT\n");
    for(i = 0; i < N; i++)
        printf("%d=%d\n", i+1, arr[i]);

}