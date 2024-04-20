#ifndef _DLL_H 
#define _DLL_H 

#include <stdio.h> 

#define SUCCESS 1 
#define TRUE 1 
#define FALSE 0 
#define LIST_DATA_NOT_FOUND 2 
#define LIST_EMPTY 3 

typedef int data_t; 
typedef int status_t; 
typedef int len_t; 
typedef struct node node_t; 
typedef node_t dll_t; 

struct node 
{
    data_t data; 
    struct node* prev; 
    struct node* next; 
}; 

dll_t* create_list(void); 
status_t insert_start(dll_t* p_list, data_t new_data); 
status_t insert_end(dll_t* p_list, data_t new_data); 
status_t insert_after(dll_t* p_list, data_t e_data, data_t new_data); 
status_t insert_before(dll_t* p_list, data_t e_data, data_t new_data); 

status_t remove_start(dll_t* p_list); 
status_t remove_end(dll_t* p_list); 
status_t remove_data(dll_t* p_list, data_t r_data); 

status_t get_start(dll_t* p_list, data_t* p_start_data); 
status_t get_end(dll_t* p_list, data_t* p_end_data); 

status_t pop_start(dll_t* p_list, data_t* p_start_data); 
status_t pop_end(dll_t* p_list, data_t* p_end_data); 

status_t clear_list(dll_t* p_list); 

status_t is_list_empty(dll_t* p_list); 
status_t find(dll_t* p_list, data_t f_data); 
len_t get_list_length(dll_t* p_list); 

void show_list(dll_t* p_list, const char* msg); 
status_t destroy_list(dll_t** pp_list); 

/* Inter list routines */
dll_t* get_concatenated_list(dll_t* p_list_1, dll_t* p_list_2); 
status_t concat_lists(dll_t* p_list_1, dll_t* p_list_2); 
dll_t* get_merged_list(dll_t* p_list_1, dll_t* p_list_2); 
data_t* to_array(dll_t* p_list, int* pN); 
dll_t* to_list(data_t* p_array, int N); 
dll_t* get_reversed_list(dll_t* p_list); 
status_t reverse_list(dll_t* p_list); 

static node_t* get_node(data_t new_data); 
static void* xmalloc(size_t size_in_bytes); 

#endif /* _DLL_H */