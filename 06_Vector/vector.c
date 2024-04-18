#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

vector_t* create_vector(ssize_t N)
{
    vector_t* vec;

    if(N <= 0)
        return NULL;

    vec = (vector_t*)malloc(sizeof(vector_t));
    if(vec == NULL)
    {
        puts("Out of Memory");
        exit(EXIT_FAILURE);
    }

    vec->arr = (data_t*)malloc(sizeof(data_t) * N);
    if(vec->arr == NULL)
    {
        puts("Out of Memory");
        exit(EXIT_FAILURE);
    }

    vec->N = N;

    return vec;
}

status_t get(vector_t* p_vec, index_t index, data_t* p_data)
{
    if(index < 0 || index >= p_vec->N)
        return INDEX_OUT_OF_RANGE;

    *p_data = p_vec->arr[index];
    return SUCCESS;
}

status_t set(vector_t* p_vec, index_t index, data_t new_val)
{
    if(index < 0 || index >= p_vec->N)
        return INDEX_OUT_OF_RANGE;

    p_vec->arr[index] = new_val;
    return SUCCESS;
} 

status_t push_back(vector_t* p_vec, data_t new_val)
{
    //Correct later
    p_vec->arr = (data_t*)realloc(p_vec->arr, sizeof(data_t) * (p_vec->N + 1));
    if(p_vec->arr == NULL)
    {
        puts("Out of Memory");
        exit(EXIT_FAILURE);
    }
    
    p_vec->N = p_vec->N + 1;
    p_vec->arr[p_vec->N - 1] = new_val;
    return SUCCESS; 
}

status_t pop_back(vector_t* p_vec, data_t* p_poped_val)
{
    if(p_vec->N == 0)
        return VECTOR_EMPTY;
    
    *p_poped_val = p_vec->arr[p_vec->N - 1];

    p_vec->arr = (data_t*)realloc(p_vec->arr, sizeof(data_t) * (p_vec->N - 1));
    if(p_vec->arr == NULL)
    {
        puts("Out of Memeory");
        exit(EXIT_FAILURE);
    }

    p_vec->N -= 1;

    if(p_vec->N == 0)
        p_vec->arr = NULL;

    return SUCCESS;
}
status_t sort(vector_t* p_vec)
{
    quick_sort(p_vec->arr, 0, p_vec->N - 1);
    return SUCCESS;
}

index_t search(vector_t* p_vec, data_t search_element) 
{
    index_t i;

    for(i = 0; i < p_vec->N; i++)
    {
        if(p_vec->arr[i] == search_element)
            return i;
    }
    
    return -1;
}
ssize_t size(vector_t* p_vec)
{
    return p_vec->N;
}

void show(vector_t* p_vec, const char* msg)
{
    index_t i;
    puts(msg);

    for(i = 0; i < p_vec->N; i++)
    {
        printf("%d\n", p_vec->arr[i]);
    }
} 
status_t destroy_vector(vector_t** pp_vec)
{
    free((*pp_vec)->arr);
    free(*pp_vec);
    *pp_vec = NULL;
    return SUCCESS;
}