#include "queue.h"

queue_t* create_queue(void)
{
    return create_list(); 
}

status_t enqueue(queue_t* queue, data_t new_element)
{
    return insert_end(queue, new_element); 
}

status_t dequeue(queue_t* queue, data_t* p_dequeued_data)
{
    return pop_start(queue, p_dequeued_data); 
}

status_t peek(queue_t* queue, data_t* p_peek_data)
{
    return get_start(queue, p_peek_data); 
}

status_t is_queue_empty(queue_t* queue)
{
    return is_list_empty(queue); 
}

status_t destroy_queue(queue_t** pp_queue)
{
    return destroy_list(pp_queue); 
} 
