#define _CRT_RAND_S //secure way to generate random nos

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef long long ssize_t; 

void fill_array(int* arr, int N);
void insertion_sort(int* arr, int N);
void validate_sort(int* arr, int N);

int main(int argc, char* argv[])
{
    int* arr;
    ssize_t N;
    clock_t start, end;
    double time_taken;

    if(argc < 2)
    {
        puts("Usage Error: Expect Number Argument");
        exit(EXIT_FAILURE);
    }

    N = atoll(argv[1]);

    if(N <= 0)
    {
        puts("Argument N cant be less that or equal to zero");
        exit(EXIT_FAILURE);
    }

    arr = (int*)malloc(sizeof(int) * N);
    if(arr ==  NULL)
    {
        puts("malloc() failed");
        exit(EXIT_FAILURE);
    }

    fill_array(arr, N);

    start = clock();
    insertion_sort(arr, N);
    end = clock();

    time_taken = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;

    printf("Time taken = %.2f\n", time_taken);

    validate_sort(arr, N);

}

void fill_array(int* arr, int N)
{
    int i;
    srand((unsigned int)time(NULL)); //seed

    for(i = 0; i < N; i++)
    {
        arr[i] = rand();
    }
}

void insertion_sort(int* arr, int N)
{
    ssize_t i, j;
    int key;

    for(i = 1; i < N; ++i)
    {
        key = arr[i];
        j = i - 1;

        while(j > -1 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j--;
        }

        arr[j+1] = key;
    }
}

void validate_sort(int* arr, int N)
{
    int i;

    for(int i = 1; i < N; i++)
    {
        if(arr[i] < arr[i-1])
        {
            printf("Sort Not working properly");
            exit(EXIT_FAILURE);
        }
    }
}

/*
PS C:\Users\rutur\OneDrive\Documents\GitHub\DSAUsingC\04_Sort> .\app.exe 10
Time taken = 0.00
PS C:\Users\rutur\OneDrive\Documents\GitHub\DSAUsingC\04_Sort> .\app.exe 100
Time taken = 0.00
PS C:\Users\rutur\OneDrive\Documents\GitHub\DSAUsingC\04_Sort> .\app.exe 1000
Time taken = 1.00
PS C:\Users\rutur\OneDrive\Documents\GitHub\DSAUsingC\04_Sort> .\app.exe 10000
Time taken = 99.00
PS C:\Users\rutur\OneDrive\Documents\GitHub\DSAUsingC\04_Sort> .\app.exe 100000
Time taken = 9737.00
PS C:\Users\rutur\OneDrive\Documents\GitHub\DSAUsingC\04_Sort> .\app.exe 1000000
Time taken = 2159478.00
*/