#include "prioqueue.h"

prio_queue_t* create_prio_queue(void)
{
    return create_list(); 
}

status_t prio_enqueue(
    prio_queue_t* p_prio_queue, 
    data_t new_data
)
{
    return insert_end(
                p_prio_queue, 
                new_data
            ); 
}

status_t prio_min_dequeue(
    prio_queue_t* p_prio_queue, 
    data_t* p_min_data
)
{
    return pop_min(
        p_prio_queue, 
        p_min_data
    ); 
}

status_t prio_max_dequeue(
    prio_queue_t* p_prio_queue, 
    data_t* p_max_data
)
{
    return pop_max(
        p_prio_queue, 
        p_max_data
    ); 
}

status_t is_prio_queue_empty(
    prio_queue_t* p_prio_queue
)
{
    return is_list_empty(p_prio_queue); 
}

status_t destroy_prio_queue(
    prio_queue_t** pp_prio_queue
)
{
    return destroy_list(
                pp_prio_queue
            ); 
}