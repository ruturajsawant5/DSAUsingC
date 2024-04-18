#ifndef _ARRAY_H
#define _ARRAY_H

#ifdef _WIN
typedef long long ssize_t;
#endif

#define SUCCESS             1 
#define INDEX_OUT_OF_RANGE  2

typedef int data_t; 
typedef int status_t; 
typedef long long ssize_t; 
typedef ssize_t index_t; 

typedef struct array
{
    data_t* arr;
    ssize_t N;
}array_t;

/* Interface Functions */
array_t* create_array(ssize_t N); 
status_t get(array_t* p_arr, index_t index, data_t* p_data); 
status_t set(array_t* p_arr, index_t index, data_t new_val); 
status_t sort(array_t* p_arr); // Use quick sort 
index_t search(array_t* p_arr, data_t search_element); 
ssize_t size(array_t* p_arr); 
void show(array_t* p_arr, const char* msg); 
status_t destroy_array(array_t** pp_array); 

/* Auxillary Functions */
void quick_sort(int* arr, int p, int r);
int partition(int* a, int p, int r);

#endif /* _ARRAY_H*/