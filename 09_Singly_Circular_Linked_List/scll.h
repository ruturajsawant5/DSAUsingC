#ifndef _SCLL_H 
#define _SCLL_H 

#define SUCCESS 1 
#define TRUE 1 
#define FALSE 0 
#define LIST_DATA_NOT_FOUND 2 
#define LIST_EMPTY 3 

typedef int data_t; 
typedef int status_t; 
typedef int len_t; 
typedef struct node node_t; 
typedef node_t scll_t; 

struct node 
{
    data_t data; 
    struct node* next; 
}; 

scll_t* create_list(void); 
status_t insert_start(scll_t* p_list, data_t new_data); 
status_t insert_end(scll_t* p_list, data_t new_data); 
status_t insert_after(scll_t* p_list, data_t e_data, data_t new_data); 
status_t insert_before(scll_t* p_list, data_t e_data, data_t new_data); 

status_t remove_start(scll_t* p_list); 
status_t remove_end(scll_t* p_list); 
status_t remove_data(scll_t* p_list, data_t r_data); 

status_t get_start(scll_t* p_list, data_t* p_start_data); 
status_t get_end(scll_t* p_list, data_t* p_end_data); 

status_t pop_start(scll_t* p_list, data_t* p_start_data); 
status_t pop_end(scll_t* p_list, data_t* p_end_data); 

status_t clear_list(scll_t* p_list); 

status_t is_list_empty(scll_t* p_list); 
status_t find(scll_t* p_list, data_t f_data); 
len_t get_list_length(scll_t* p_list); 

void show_list(scll_t* p_list, const char* msg); 
status_t destroy_list(scll_t** pp_list); 

/* Inter-list routines */
scll_t* get_concatenated_list(scll_t* p_list_1, scll_t* p_list_2); 
status_t concat_lists(scll_t* p_list_1, scll_t* p_list_2); 
scll_t* merge_lists(scll_t* p_list_1, scll_t* p_list_2); 
data_t* to_array(scll_t* p_list, int* pN); 
scll_t* to_list(data_t* p_array, int N); 
scll_t* get_reversed_list(scll_t* p_list); 
status_t reverse_list(scll_t* p_list); 

static node_t* get_node(data_t new_data); 
static void* xmalloc(size_t size_in_bytes); 

#endif /* _SCLL_H */