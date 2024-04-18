#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
typedef long long ssize_t; 
#endif

void quick_sort(int* arr, int p, int r);
int partition(int* a, int p, int r);


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
