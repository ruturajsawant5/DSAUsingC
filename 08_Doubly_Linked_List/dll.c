#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include "dll.h"

dll_t* create_list(void)
{
    return (get_node(0)); 
}

status_t insert_start(dll_t* p_list, data_t new_data)
{
    node_t* new_node = NULL; 

    new_node = get_node(new_data); 
    new_node->next = p_list->next; 
    new_node->prev = p_list; 
    if(p_list->next != NULL)
        p_list->next->prev = new_node; 
    p_list->next = new_node; 
    return (SUCCESS); 
}

status_t insert_end(dll_t* p_list, data_t new_data)
{
    node_t* new_node = NULL; 
    node_t* run = NULL; 

    new_node = get_node(new_data); 
    for(run = p_list; run->next != NULL; run = run->next)
        ; 
    
    new_node->prev = run; 
    run->next = new_node; 

    return (SUCCESS); 
}

status_t insert_after(dll_t* p_list, data_t e_data, data_t new_data)
{
    node_t* run = NULL;
    node_t* new_node = NULL; 

    for(run = p_list->next; run != NULL; run = run->next)
    {
        if(run->data == e_data)
        {
            new_node = get_node(new_data); 
            new_node->prev = run; 
            new_node->next = run->next; 
            if(run->next != NULL)
                run->next->prev = new_node; 
            run->next = new_node; 
            return (SUCCESS); 
        }
    }

    return (LIST_DATA_NOT_FOUND); 
}

status_t insert_before(dll_t* p_list, data_t e_data, data_t new_data)
{
    node_t* run = NULL; 
    node_t* new_node = NULL; 

    for(run = p_list->next; run != NULL; run = run->next)
    {
        if(run->data == e_data)
        {
            new_node = get_node(new_data); 
            new_node->prev = run->prev; 
            new_node->next = run; 
            run->prev->next = new_node; 
            run->prev = new_node; 
            return (SUCCESS); 
        }
    }

    return (LIST_DATA_NOT_FOUND); 
}

status_t remove_start(dll_t* p_list)
{
    node_t* p_first_node = NULL; 

    if(p_list->prev == NULL && p_list->next == NULL)
        return (LIST_EMPTY); 
    
    p_first_node = p_list->next; 
    if(p_first_node->next != NULL)
        p_first_node->next->prev = p_list; 
    p_list->next = p_first_node->next; 
    free(p_first_node); 
    p_first_node = NULL; 

    return (SUCCESS); 
}

status_t remove_end(dll_t* p_list)
{
    node_t* run = NULL; 

    if(p_list->prev == NULL && p_list->next == NULL)
        return (LIST_EMPTY); 

    for(run = p_list; run->next != NULL; run = run->next)
        ; 
    run->prev->next = NULL; 
    free(run); 
    run = NULL; 

    return (SUCCESS); 
}

status_t remove_data(dll_t* p_list, data_t r_data)
{
    node_t* run = NULL; 

    for(run = p_list->next; run != NULL; run = run->next)
    {
        if(run->data == r_data) 
        {
            run->prev->next = run->next; 
            if(run->next != NULL)
                run->next->prev = run->prev; 
            free(run); 
            run = NULL; 
            return (SUCCESS); 
        }
    }

    return (LIST_DATA_NOT_FOUND); 
}

status_t get_start(dll_t* p_list, data_t* p_start_data)
{
    if(is_list_empty(p_list) == TRUE)
        return (LIST_EMPTY); 
    *p_start_data = p_list->next->data; 
    return (SUCCESS); 
}

status_t get_end(dll_t* p_list, data_t* p_end_data)
{
    node_t* run = NULL; 

    if(is_list_empty(p_list) == TRUE)
        return (LIST_EMPTY);
    
    for(run = p_list; run->next != NULL; run = run->next)
        ; 
    *p_end_data = run->data; 
    return (SUCCESS); 
}

status_t pop_start(dll_t* p_list, data_t* p_start_data)
{
    node_t* p_first_node = NULL; 

    if(is_list_empty(p_list) == TRUE)
        return (LIST_EMPTY); 

    p_first_node = p_list->next; 
    *p_start_data = p_first_node->data;
    
    if(p_first_node->next != NULL)
        p_first_node->next->prev = p_list; 
    p_list->next = p_first_node->next; 
    
    free(p_first_node); 
    p_first_node = NULL;  

    return (SUCCESS); 
}

status_t pop_end(dll_t* p_list, data_t* p_end_data)
{
    node_t* run = NULL; 

    if(is_list_empty(p_list) == TRUE)
        return (LIST_EMPTY); 

    for(run = p_list; run->next != NULL; run = run->next)
        ; 
    
    *p_end_data = run->data; 
    run->prev->next = NULL; 
    free(run); 
    run = NULL; 

    return (SUCCESS); 
}

status_t clear_list(dll_t* p_list)
{
    node_t* run = NULL; 
    node_t* run_next = NULL; 

    for(run = p_list->next; run != NULL; run = run_next)
    {
        run_next = run->next; 
        free(run); 
    }

    p_list->next = NULL; 

    return (SUCCESS); 
}

status_t is_list_empty(dll_t* p_list)
{
    return (p_list->prev == NULL && p_list->next == NULL); 
}

status_t find(dll_t* p_list, data_t f_data)
{
    node_t* run = NULL; 

    for(run = p_list->next; run != NULL; run = run->next)
        if(run->data == f_data) 
            return (TRUE); 

    return (FALSE); 
}

len_t get_list_length(dll_t* p_list)
{
    node_t* run = NULL;
    len_t len = 0; 

    for(run = p_list->next; run != NULL; run = run->next)
        len += 1; 

    return (len); 
}

void show_list(dll_t* p_list, const char* msg)
{
    node_t* run = NULL; 

    if(msg)
        puts(msg); 

    printf("[START]<->"); 
    for(run = p_list->next; run != NULL; run = run->next)
        printf("[%d]<->", run->data); 
    puts("[END]"); 
}

status_t destroy_list(dll_t** pp_list)
{
    dll_t* p_list = NULL; 

    p_list = *pp_list; 
    assert(clear_list(p_list) == SUCCESS); 
    
    free(p_list); 
    p_list = NULL; 

    *pp_list = NULL; 

    return (SUCCESS); 
}

dll_t* get_concatenated_list(dll_t* p_list_1, dll_t* p_list_2)
{
    dll_t* p_cat_list = NULL; 
    node_t* run = NULL; 

    p_cat_list = create_list(); 

    for(
        run = p_list_1->next; 
        run != NULL; 
        run = run->next
    )
        assert(
            insert_end(
                p_cat_list, 
                run->data
            ) == SUCCESS
        ); 

    for(
        run = p_list_2->next; 
        run != NULL; 
        run = run->next
    )
        assert(
            insert_end(
                p_cat_list, 
                run->data
            ) == SUCCESS
        ); 

    return (p_cat_list); 
}

status_t concat_lists(dll_t* p_list_1, dll_t* p_list_2)
{
    node_t* run = NULL; 

    if(is_list_empty(p_list_2) == TRUE) 
    {
        free(p_list_2); 
        p_list_2 = NULL; 
        return (SUCCESS); 
    }

    for(
        run = p_list_1; 
        run->next != NULL; 
        run = run->next
    )
        ;

    run->next = p_list_2->next; 
    p_list_2->next->prev = run; 

    free(p_list_2); 
    p_list_2 = NULL; 

    return (SUCCESS);  
}

dll_t* get_merged_list(dll_t* p_list_1, dll_t* p_list_2)
{
    dll_t* p_merged_list = NULL; 
    node_t* run1 = NULL; 
    node_t* run2 = NULL; 

    p_merged_list = create_list(); 
    run1 = p_list_1->next; 
    run2 = p_list_2->next; 

    while(TRUE)
    {
        if(run1 == NULL)
        {
            while(run2 != NULL)
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

        if(run2 == NULL)
        {
            while(run1 != NULL)
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

data_t* to_array(dll_t* p_list, int* pN)
{
    data_t* p_array = NULL; 
    int N = 0, i; 
    node_t* run = NULL; 

    N = get_list_length(p_list); 
    if(N == 0)
        return (p_array); 

    p_array = (data_t*)xmalloc(N * sizeof(data_t)); 

    i = 0; 
    run = p_list->next; 
    while(run != NULL)
    {
        p_array[i] = run->data; 
        i = i + 1; 
        run = run->next; 
    }
    *pN = N; 
    return (p_array); 
}

dll_t* to_list(data_t* p_array, int N)
{
    dll_t* p_list = NULL; 
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

dll_t* get_reversed_list(dll_t* p_list)
{
    dll_t* p_reversed_list = NULL; 
    node_t* run = NULL; 

    p_reversed_list = create_list(); 
    for(
        run = p_list->next; 
        run != NULL; 
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

status_t reverse_list(dll_t* p_list)
{
    node_t* original_first = NULL; 
    node_t* current_first = NULL; 
    node_t* run = NULL; 
    node_t* run_next = NULL; 

    if(p_list->next == NULL)
        return (SUCCESS); 

    if(p_list->next->next == NULL)
        return (SUCCESS); 

    original_first = p_list->next; 
    current_first = p_list->next; 

    for(
        run = p_list->next->next; 
        run != NULL; 
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

    original_first->next = NULL; 
    return (SUCCESS); 
}


// HELPER FUNCTIONS 
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