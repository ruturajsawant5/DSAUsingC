#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include "dcll.h"

dcll_t* create_list(void)
{
    dcll_t* p_list = NULL; 

    p_list = get_node(0); 
    p_list->prev = p_list; 
    p_list->next = p_list; 

    return (p_list); 
}

status_t insert_start(dcll_t* p_list, data_t new_data)
{
    node_t* new_node = get_node(new_data);
    
    new_node->prev = p_list;
    new_node->next = p_list->next;
    p_list->next->prev = new_node;
    p_list->next = new_node;

    return (SUCCESS); 
} 

status_t insert_end(dcll_t* p_list, data_t new_data)
{
    node_t* new_node = get_node(new_data);

    new_node->prev = p_list->prev;
    new_node->next = p_list;
    p_list->prev->next = new_node;
    p_list->prev = new_node;

    return (SUCCESS); 
}

status_t insert_after(dcll_t* p_list, data_t e_data, data_t new_data)
{
    node_t* e_node = NULL;
    node_t* new_node = NULL;

    e_node = search_node(p_list, e_data); 
    if(e_node == NULL)
        return (LIST_DATA_NOT_FOUND); 

    new_node = get_node(new_data);

    new_node->prev = e_node;
    new_node->next = e_node->next;
    e_node->next->prev = new_node;
    e_node->next = new_node;

    return (SUCCESS); 
}

status_t insert_before(dcll_t* p_list, data_t e_data, data_t new_data)
{
    node_t* e_node = NULL;
    node_t* new_node = NULL;

    e_node = search_node(p_list, e_data); 
    if(e_node == NULL)
        return (LIST_DATA_NOT_FOUND); 

    new_node = get_node(new_data);

    new_node->prev = e_node->prev;
    new_node->next = e_node;
    e_node->prev->next = new_node;
    e_node->prev = new_node;

    return (SUCCESS); 
}

status_t remove_start(dcll_t* p_list)
{
    node_t* p_del = NULL;

    if(is_list_empty(p_list))
        return (LIST_EMPTY); 

    p_del = p_list->next;

    p_del->next->prev = p_del->prev;
    p_del->prev->next = p_del->next;
    
    return (SUCCESS); 
}

status_t remove_end(dcll_t* p_list)
{
    node_t* p_del = NULL;

    if(is_list_empty(p_list))
        return (LIST_EMPTY);

    p_del = p_list->prev;
    
    p_del->next->prev = p_del->prev;
    p_del->prev->next = p_del->next;

    return (SUCCESS); 
}

status_t remove_data(dcll_t* p_list, data_t r_data)
{
    node_t* p_del = NULL; 

    p_del = search_node(p_list, r_data); 
    if(p_del == NULL)
        return (LIST_DATA_NOT_FOUND); 
    
    p_del->next->prev = p_del->prev;
    p_del->prev->next = p_del->next;
    
    return (SUCCESS); 
}

status_t get_start(dcll_t* p_list, data_t* p_start_data)
{
    if(is_list_empty(p_list))
        return (LIST_EMPTY); 
    *p_start_data = p_list->next->data; 
    return (SUCCESS); 
}

status_t get_end(dcll_t* p_list, data_t* p_end_data)
{
    if(is_list_empty(p_list))
        return (LIST_EMPTY); 
    *p_end_data = p_list->prev->data; 
    return (SUCCESS); 
}

status_t pop_start(dcll_t* p_list, data_t* p_start_data)
{
    node_t* p_del;

    if(is_list_empty(p_list))
        return (LIST_EMPTY); 
    *p_start_data = p_list->next->data;

    p_del = p_list->next;

    p_del->next->prev = p_del->prev;
    p_del->prev->next = p_del->next;

    return (SUCCESS); 
}

status_t pop_end(dcll_t* p_list, data_t* p_end_data)
{
    node_t* p_del;

    if(is_list_empty(p_list))
        return (LIST_EMPTY); 
    *p_end_data = p_list->prev->data; 
    
    p_del = p_list->prev;
    
    p_del->next->prev = p_del->prev;
    p_del->prev->next = p_del->next;
    
    return (SUCCESS); 
}

status_t clear_list(dcll_t* p_list)
{
    node_t* run = NULL; 
    node_t* run_next = NULL; 

    run = p_list->next; 
    while(run != p_list)
    {
        run_next = run->next; 
        free(run); 
        run = run_next; 
    }

    p_list->prev = p_list; 
    p_list->next = p_list; 

    return (SUCCESS); 
}

status_t is_list_empty(dcll_t* p_list)
{
    return (p_list->prev == p_list && p_list->next == p_list); 
}

status_t find(dcll_t* p_list, data_t f_data)
{
    node_t* f_node = NULL; 

    f_node = search_node(p_list, f_data); 
    return (f_node != NULL); 
}

len_t get_list_length(dcll_t* p_list)
{
    node_t* run = NULL; 
    len_t L = 0; 

    for(run = p_list->next; run != p_list; run = run->next)
        ++L; 
    return (L); 
}

void show_list(dcll_t* p_list, const char* msg)
{
    node_t* run = NULL; 

    if(msg)
        puts(msg); 

    printf("[START]<->"); 
    for(run = p_list->next; run != p_list; run = run->next)
        printf("[%d]<->", run->data); 
    puts("[END]"); 
}

status_t destroy_list(dcll_t** pp_list)
{
    clear_list(*pp_list); 
    free(*pp_list); 
    *pp_list = NULL; 
    return (SUCCESS); 
}

dcll_t* get_concatenated_list(
            dcll_t* p_list_1, 
            dcll_t* p_list_2
        )
{
    dcll_t* p_cat_list = NULL; 
    node_t* run = NULL; 

    p_cat_list = create_list(); 
    for(
        run = p_list_1->next; 
        run != p_list_1; 
        run = run->next
    )
        assert(
            insert_end(p_cat_list, run->data) 
            == SUCCESS
        ); 
    
    for(
        run = p_list_2->next; 
        run != p_list_2; 
        run = run->next
    )
        assert(
                insert_end(p_cat_list, run->data) 
                == SUCCESS
        ); 

    return (p_cat_list); 
}

status_t concat_lists(
        dcll_t* p_list_1, 
        dcll_t* p_list_2
    )
{
    if(is_list_empty(p_list_2) == TRUE)
    {
        free(p_list_2); 
        p_list_2 = NULL; 
        return (SUCCESS); 
    }

    p_list_2->prev->next = p_list_1; 
    p_list_2->next->prev = p_list_1->prev; 
    p_list_1->prev->next = p_list_2->next; 
    p_list_1->prev = p_list_2->prev; 

    free(p_list_2); 
    p_list_2 = NULL; 

    return (SUCCESS); 
}

dcll_t* merge_lists(
        dcll_t* p_list_1, 
        dcll_t* p_list_2
    )
{
    dcll_t* p_merged_list = NULL; 
    node_t* run1 = NULL; 
    node_t* run2 = NULL; 

    p_merged_list = create_list(); 
    run1 = p_list_1->next; 
    run2 = p_list_2->next; 

    while(TRUE)
    {
        if(run1 == p_list_1)
        {
            while(run2 != p_list_2)
            {
                assert(
                        insert_end(
                            p_merged_list, 
                            run2->data
                        ) == SUCCESS 
                    ); 
                run2 = run2->next; 
            }
            break; 
        }

        if(run2 == p_list_2)
        {
            while(run1 != p_list_1)
            {
                assert(
                    insert_end( 
                        p_merged_list, 
                        run1->data 
                    ) == SUCCESS
                ); 
                run1 = run1->next; 
            }
            break; 
        }

        if(run1->data <= run2->data)
        {
            assert(
                    insert_end( 
                        p_merged_list, 
                        run1->data 
                    ) == SUCCESS
                ); 
            run1 = run1->next; 
        }
        else 
        {
            assert(
                    insert_end(
                        p_merged_list, 
                        run2->data
                    ) == SUCCESS 
                ); 
            run2 = run2->next; 
        }
    }

    return (p_merged_list); 
} 

data_t* to_array(
            dcll_t* p_list, 
            int* pN
        )
{
    node_t* run = NULL; 
    data_t* p_array = NULL; 
    len_t N = 0; 
    int i; 

    N = get_list_length(p_list); 
    if(N == 0)
        return (p_array); 

    p_array = (data_t*)xmalloc(N * sizeof(data_t)); 
    
    i = 0; 
    run = p_list->next; 
    while(run != p_list)
    {
        p_array[i] = run->data;
        run = run->next; 
        i = i + 1;  
    }

    *pN = N; 
    return (p_array); 
}

dcll_t* to_list(
            data_t* p_array, 
            int N
        )
{
    dcll_t* p_list = NULL;  
    int i; 

    p_list = create_list(); 
    for(i = 0; i < N; ++i)
        assert(
            insert_end(
                p_list, 
                p_array[i]
            ) == SUCCESS
        ); 

    return (p_list); 
}

dcll_t* get_reversed_list(
        dcll_t* p_list
    )
{
    dcll_t* p_reversed_list = NULL; 
    node_t* run = NULL; 

    p_reversed_list = create_list(); 
    for(
        run = p_list->next; 
        run != p_list; 
        run = run->next
    )
        assert(
            insert_start(
                p_reversed_list, 
                run->data
            ) == SUCCESS
        ); 

    return (p_reversed_list); 
}

status_t reverse_list(
        dcll_t* p_list
    )
{
    node_t* original_first = NULL; 
    node_t* current_first = NULL; 
    node_t* run = NULL; 
    node_t* run_next = NULL; 

    if(p_list->next == p_list)
        return (SUCCESS); 

    if(p_list->next->next == p_list)
        return (SUCCESS); 

    original_first = p_list->next; 
    current_first = p_list->next; 

    for(
        run = p_list->next->next; 
        run != p_list; 
        run = run_next
    )
    {
        run_next = run->next; 

        run->next = current_first; 
        run->prev = p_list; 
        p_list->next = run; 
        current_first->prev = run; 

        current_first = run; 
    }

    p_list->prev = original_first; 
    original_first->next = p_list; 
    
    return (SUCCESS); 
} 

status_t reverse_list_swp(
        dcll_t* p_list
    )
{
    node_t* run = NULL; 
    node_t* run_next = NULL; 
    node_t* tmp = NULL; 

    for(
        run = p_list->next; 
        run != p_list; 
        run = run_next
    )
    {
        run_next = run->next; 
        tmp = run->prev; 
        run->prev = run->next; 
        run->next = tmp; 
    }

    tmp = p_list->prev; 
    p_list->prev = p_list->next; 
    p_list->next = tmp; 

    return (SUCCESS); 
}

// HELPER FUNCTIONS 
static node_t* search_node(dcll_t* p_list, data_t s_data)
{
    node_t* run = NULL; 

    for(run = p_list->next; run != p_list; run = run->next)
        if(run->data == s_data)
            return (run); 

    return (NULL); 
}

static node_t* get_node(data_t new_data)
{
    node_t* new_node = NULL; 

    new_node = (node_t*)xmalloc(sizeof(node_t)); 
    new_node->data = new_data; 
    new_node->prev = NULL; 
    new_node->next = NULL; 
   
    return (new_node); 
}

static void* xmalloc(size_t size_in_bytes)
{
    void* p = NULL; 

    p = malloc(size_in_bytes); 
    if(p == NULL)
    {
        fprintf(stderr, "fatal:out of virtual memory.Exiting the app\n"); 
        exit(EXIT_FAILURE); 
    }

    return (p); 
}

