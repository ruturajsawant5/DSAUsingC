#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

array_t* create_array(ssize_t N)
{
    array_t* p_arr;

    if(N <= 0)
    {
        return NULL;
    }

    p_arr = (array_t*)malloc(sizeof(array_t));

    p_arr->N = N;
    p_arr->arr = (int*)malloc(sizeof(int) * N);
    if(p_arr->arr == NULL)
    {
        return NULL;
    }

    return p_arr;
}

status_t get(array_t* p_arr, index_t index, data_t* p_data)
{
    if(index < 0 || index >= p_arr->N)
        return INDEX_OUT_OF_RANGE;
    
    *p_data = p_arr->arr[index];
    return SUCCESS;
} 
status_t set(array_t* p_arr, index_t index, data_t new_val)
{
    if(index < 0 || index >= p_arr->N)
        return INDEX_OUT_OF_RANGE;
    
    p_arr->arr[index] = new_val;
    return SUCCESS;
}

status_t sort(array_t* p_arr)
{
    quick_sort(p_arr->arr, 0, p_arr->N - 1);
    return SUCCESS;
}

index_t search(array_t* p_arr, data_t search_element)
{
    int i;

    for(i = 0; i < p_arr->N; ++i)
    {
        if(p_arr->arr[i] == search_element)
            return i;
    }

    return -1;
}

ssize_t size(array_t* p_arr)
{
    return p_arr->N;
}

void show(array_t* p_arr, const char* msg)
{
    int i;
    puts(msg);
    
    for(i = 0; i < p_arr->N; ++i)
        printf("%d\n", p_arr->arr[i]);
}

status_t destroy_array(array_t** pp_array)
{
    free((*pp_array)->arr);
    free(*pp_array);
    *pp_array = NULL;
    return SUCCESS;
}