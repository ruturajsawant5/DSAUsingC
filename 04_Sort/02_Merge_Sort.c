#define _CRT_RAND_S //secure way to generate random nos

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
typedef long long ssize_t; 
#endif

void fill_array(int* arr, int N);
void validate_sort(int* arr, int N);
void merge_sort(int* arr, int p, int r);
void merge(int* arr, int p, int q, int r);

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
    merge_sort(arr, 0, N-1);
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

void merge_sort(int* arr, int p, int r)
{
    int q;

    if(p < r)
    {
        q = (p + r) / 2;
        merge_sort(arr, p, q); 
        merge_sort(arr, q+1, r); 
        merge(arr, p, q, r); 
    }
}

void merge(int* arr, int p, int q, int r)
{
    int* a1;
    int* a2;

    int N1 = q - p + 1;
    int N2 = r - q;

    int i, j, k;

    a1 = (int*)malloc(sizeof(int) * N1);
    if(a1 == NULL)
    {
        puts("malloc() failed");
        exit(EXIT_FAILURE);
    }

    a2 = (int*)malloc(sizeof(int) * N2);
    if(a2 == NULL)
    {
        puts("malloc() failed");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < N1; ++i)
        a1[i] = arr[p+i]; 

    for(i = 0; i < N2; ++i)
        a2[i] = arr[q+1+i]; 

    i = 0;
    j = 0;
    k = 0;

    while(1)
    {
        if(a1[i] < a2[j])
        {
            arr[p + k] = a1[i];
            i++;
            k++;

            if(i == N1)
            {
                while(j < N2)
                {
                    arr[p + k] = a2[j];
                    j++;
                    k++;
                }
                break;
            }
        }
        else
        {
            arr[p + k] = a2[j];
            j++;
            k++;

            if(j == N2)
            {
                while(i < N1)
                {
                    arr[p + k] = a1[i];
                    i++;
                    k++;
                }
                break;
            }
        }
    }

    free(a1);
    free(a2);
}

/*
PS C:\Users\rutur\OneDrive\Documents\GitHub\DSAUsingC\04_Sort> .\app.exe 10
Time taken = 0.00
PS C:\Users\rutur\OneDrive\Documents\GitHub\DSAUsingC\04_Sort> .\app.exe 100
Time taken = 0.00
PS C:\Users\rutur\OneDrive\Documents\GitHub\DSAUsingC\04_Sort> .\app.exe 1000
Time taken = 0.00
PS C:\Users\rutur\OneDrive\Documents\GitHub\DSAUsingC\04_Sort> .\app.exe 10000
Time taken = 4.00
PS C:\Users\rutur\OneDrive\Documents\GitHub\DSAUsingC\04_Sort> .\app.exe 100000
Time taken = 19.00
PS C:\Users\rutur\OneDrive\Documents\GitHub\DSAUsingC\04_Sort> .\app.exe 1000000
Time taken = 193.00
*/