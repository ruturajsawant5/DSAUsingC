#define _CRT_RAND_S //secure way to generate random nos

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
typedef long long ssize_t; 
#endif

void fill_array(int* arr, int N);
void validate_sort(int* arr, int N);
void quick_sort(int* arr, int p, int r);
int partition(int* a, int p, int r);

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
    quick_sort(arr, 0, N-1);
    end = clock();

    time_taken = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;

    printf("Time taken = %.2f\n", time_taken);

    validate_sort(arr, N);
    
    free(arr);
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

void quick_sort(int* a, int p, int r)
{
    int q; 

    if(p < r)
    {
        q = partition(a, p, r); 
        quick_sort(a, p, q-1); 
        quick_sort(a, q+1, r); 
    }
}

int partition(int* a, int p, int r)
{
    int i, j; 
    int pivot, tmp; 

    pivot = a[r]; 
    i = p - 1; 
    
    for(j = p; j < r;   ++j)
    {
        if(a[j] <= pivot)
        {
            i = i + 1; 
            tmp = a[i]; 
            a[i] = a[j]; 
            a[j] = tmp; 
        }
    }

    tmp = a[i+1];
    a[i+1] = a[r]; 
    a[r] = tmp; 

    return (i+1); 
}

/*
PS C:\Users\rutur\OneDrive\Documents\GitHub\DSAUsingC\04_Sort> .\app.exe 10
Time taken = 0.00
PS C:\Users\rutur\OneDrive\Documents\GitHub\DSAUsingC\04_Sort> .\app.exe 100
Time taken = 0.00
PS C:\Users\rutur\OneDrive\Documents\GitHub\DSAUsingC\04_Sort> .\app.exe 1000
Time taken = 0.00
PS C:\Users\rutur\OneDrive\Documents\GitHub\DSAUsingC\04_Sort> .\app.exe 10000
Time taken = 1.00
PS C:\Users\rutur\OneDrive\Documents\GitHub\DSAUsingC\04_Sort> .\app.exe 100000
Time taken = 8.00
PS C:\Users\rutur\OneDrive\Documents\GitHub\DSAUsingC\04_Sort> .\app.exe 1000000
Time taken = 96.00
PS C:\Users\rutur\OneDrive\Documents\GitHub\DSAUsingC\04_Sort> .\app.exe 10000000
Time taken = 3115.00
*/