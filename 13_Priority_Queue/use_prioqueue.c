#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include "prioqueue.h"

int main(void)
{
    prio_queue_t* p_prio_queue = NULL; 
    data_t data, min_data, max_data; 
    status_t status; 
    int i; 

    p_prio_queue = create_prio_queue(); 

    assert(
        is_prio_queue_empty(p_prio_queue) 
        == TRUE
    ); 

    assert(
        prio_max_dequeue(
            p_prio_queue, 
            &max_data
        ) == PRIO_QUEUE_EMPTY
    ); 

    assert(
        prio_min_dequeue(
            p_prio_queue, 
            &min_data
        ) == PRIO_QUEUE_EMPTY
    ); 

    for(i = 0; i < 10; ++i)
    {
        data = rand(); 
        status = prio_enqueue(
            p_prio_queue, 
            data
        ); 
        assert(status == SUCCESS); 
        printf(
            "Added %d to the priority queue\n", 
            data
        ); 
    }

    assert(
        is_prio_queue_empty(
            p_prio_queue
        ) == FALSE
    ); 

    status = prio_max_dequeue(
        p_prio_queue, 
        &max_data
    ); 
    assert(status == SUCCESS); 
    printf("Max Data = %d\n", max_data); 

    status = prio_min_dequeue(
        p_prio_queue, 
        &min_data
    ); 
    assert(status == SUCCESS); 
    printf("Min Data = %d\n", min_data); 

    while(
        is_prio_queue_empty(
            p_prio_queue
        ) != TRUE
    )
    {
        status = prio_max_dequeue(
            p_prio_queue, 
            &max_data
        ); 
        assert(status == SUCCESS); 
        printf(
            "Next Max Data = %d\n", 
            max_data
        ); 
    }

    status = destroy_prio_queue(&p_prio_queue); 
    assert(
        status == SUCCESS && 
        p_prio_queue == NULL
    ); 

    exit(EXIT_SUCCESS); 
}