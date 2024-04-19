#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include "sll.h"

sll_t* create_list(void)
{
    return (get_node(0)); 
}

status_t insert_start(sll_t* p_list, data_t new_data)
{
    node_t* new_node = NULL; 

    new_node = get_node(new_data); 
    new_node->next = p_list->next; 
    p_list->next = new_node; 

    return (SUCCESS); 
}

status_t insert_end(sll_t* p_list, data_t new_data)
{
    node_t* run = NULL; 

    run = p_list; 
    while(run->next != NULL)
        run = run->next; 

    run->next = get_node(new_data); 
    return (SUCCESS); 
}

status_t insert_after(sll_t* p_list, data_t e_data, data_t new_data)
{
    node_t* e_node = NULL; 
    node_t* new_node = NULL; 
    
    e_node = p_list->next; 
    while(e_node != NULL)
    {
        if(e_node->data == e_data)
        {
            new_node = get_node(new_data); 
            new_node->next = e_node->next; 
            e_node->next = new_node; 
            return (SUCCESS); 
        }
        e_node = e_node->next; 
    }

    return (LIST_DATA_NOT_FOUND); 
}

status_t insert_before(sll_t* p_list, data_t e_data, data_t new_data)
{
    node_t* new_node = NULL; 
    node_t* e_node = NULL; 
    node_t* e_node_back = NULL; 

    e_node = p_list->next; 
    e_node_back = p_list; 

    while(e_node != NULL)
    {
        if(e_node->data == e_data)
        {
            new_node = get_node(new_data); 
            e_node_back->next = new_node; 
            new_node->next = e_node; 
            return (SUCCESS); 
        }

        e_node_back = e_node; 
        e_node = e_node->next; 
    }

    return (LIST_DATA_NOT_FOUND); 
}

status_t remove_start(sll_t* p_list)
{
    node_t* p_next_node = NULL; 

    if(p_list->next == NULL)
        return (LIST_EMPTY); 
    
    p_next_node = p_list->next; 
    p_list->next = p_list->next->next; 

    free(p_next_node); 
    p_next_node = NULL; 

    return (SUCCESS); 
}

status_t remove_end(sll_t* p_list)
{
    node_t* run_prev = NULL; 
    node_t* run = NULL; 

    if(p_list->next == NULL)
        return (LIST_EMPTY); 

    run_prev = p_list; 
    run = p_list->next; 

    while(run->next != NULL)
    {
        run_prev = run; 
        run = run->next; 
    }

    free(run); 
    run = NULL; 

    run_prev->next = NULL; 

    return (SUCCESS); 
    
}

status_t remove_data(sll_t* p_list, data_t r_data)
{
    node_t* run_prev = NULL; 
    node_t* run = NULL; 

    run_prev = p_list; 
    run = p_list->next; 

    while(run != NULL)
    {
        if(run->data == r_data)
        {
            run_prev->next = run->next; 
            free(run); 
            run = NULL; 
            return (SUCCESS); 
        }
        run_prev = run; 
        run = run->next; 
    }

    return (LIST_DATA_NOT_FOUND); 
} 

status_t get_start(sll_t* p_list, data_t* p_start_data)
{
    if(p_list->next == NULL)
        return (LIST_EMPTY); 

    *p_start_data = p_list->next->data; 
    return (SUCCESS); 
} 

status_t get_end(sll_t* p_list, data_t* p_end_data)
{
    node_t* run = NULL; 
    
    if(p_list->next == NULL)
        return (LIST_EMPTY);

    run = p_list->next; 
    while(run->next != NULL)
        run = run->next; 

    *p_end_data = run->data;
    return (SUCCESS); 
}

status_t pop_start(sll_t* p_list, data_t* p_start_data)
{
    node_t* p_node_next = NULL; 
    
    if(p_list->next == NULL)
        return (LIST_EMPTY); 
    
    *p_start_data = p_list->next->data; 
    p_node_next = p_list->next; 
    p_list->next = p_list->next->next; 
    free(p_node_next); 
    p_node_next = NULL; 

    return (SUCCESS); 
}

status_t pop_end(sll_t* p_list, data_t* p_end_data)
{
    node_t* run_prev = NULL; 
    node_t* run = NULL; 

    if(p_list->next == NULL)
        return (LIST_EMPTY); 

    run_prev = p_list; 
    run = p_list->next; 
    while(run->next != NULL)
    {
        run_prev = run; 
        run = run->next; 
    }

    *p_end_data = run->data; 
    run_prev->next = run->next; 
    
    free(run); 
    run = NULL; 

    return (SUCCESS); 
}

status_t is_list_empty(sll_t* p_list)
{
    return (p_list->next == NULL); 
}

status_t find(sll_t* p_list, data_t f_data)
{
    node_t* run = NULL; 

    for(run = p_list->next; run != NULL; run = run->next)
        if(run->data == f_data) 
            return (TRUE); 

    return (FALSE); 
}

len_t get_list_length(sll_t* p_list)
{
    node_t* run = NULL; 
    len_t len = 0; 

    for(run = p_list->next; run != NULL; run = run->next)
        ++len; 

    return (len); 
}

void show_list(sll_t* p_list, const char* msg)
{
    node_t* run = NULL; 

    if(msg)
        puts(msg); 

    printf("[START]->"); 
    run = p_list->next; 
    while(run != NULL)
    {
        printf("[%d]->", run->data); 
        run = run->next; 
    }
    puts("[END]"); 
}

status_t clear_list(sll_t* p_list)
{
    node_t* run = NULL; 
    node_t* run_next = NULL; 

    run = p_list->next;
    while(run != NULL)
    {
        run_next = run->next; 
        free(run); 
        run = run_next; 
    }

    p_list->next = NULL; 

    return (SUCCESS); 
}

status_t destroy_list(sll_t** pp_list)
{
    sll_t* p_list = NULL; 
    node_t* run = NULL; 
    node_t* run_next = NULL; 

    assert(pp_list != NULL); 

    p_list = *pp_list; 
    run = p_list->next; 
    while(run != NULL)
    {
        run_next = run->next; 
        free(run); 
        run = run_next; 
    }

    free(p_list); 
    p_list = NULL; 

    *pp_list = NULL; 

    return (SUCCESS); 
}

sll_t* get_concatenated_list(sll_t* p_list_1, sll_t* p_list_2)
{
    sll_t* p_cat_list = NULL; 
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

status_t concat_lists(sll_t* p_list_1, sll_t* p_list_2)
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
    free(p_list_2); 
    p_list_2 = NULL; 

    return (SUCCESS); 
}

sll_t* merge_lists(sll_t* p_list_1, sll_t* p_list_2)
{
    sll_t* p_merged_list = NULL; 
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

data_t* to_array(sll_t* p_list, int* pN)
{
    data_t* p_array = NULL; 
    int N = 0, i; 
    node_t* run = NULL; 

    p_list = create_list(); 
    N = get_list_length(p_list); 
    if(N == 0)
        return (p_array); 

    run = p_list->next; 
    i = 0; 
    while(run != NULL)
    {
        p_array[i] = run->data; 
        i = i + 1; 
        run = run->next; 
    }

    *pN = N; 
    return (p_array); 
}

sll_t* to_list(data_t* p_array, int N)
{
    sll_t* p_list = NULL; 
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

sll_t* get_reversed_list(sll_t* p_list)
{
    sll_t* p_reversed_list = NULL; 
    node_t* run = NULL; 

    p_reversed_list = create_list(); 
    run = p_list->next; 
    while(run != NULL)
    {
        assert(
            insert_start(
                p_reversed_list, 
                run->data
            ) == SUCCESS
        ); 
        run = run->next; 
    }

    return (p_reversed_list); 
}

status_t reverse_list(sll_t* p_list)
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
        p_list->next = run; 
        current_first = run; 
    }    

    original_first->next = NULL; 
    return (SUCCESS); 
}

static node_t* get_node(data_t new_data)
{
    node_t* new_node = NULL; 

    new_node = (node_t*)xmalloc(sizeof(node_t)); 
    new_node->data = new_data; 
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
