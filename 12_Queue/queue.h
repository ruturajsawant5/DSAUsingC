#ifndef _QUEUE_H 
#define _QUEUE_H 

#include "dcll.h"

#define QUEUE_EMPTY LIST_EMPTY

typedef dcll_t queue_t; 

queue_t* create_queue(void); 
status_t enqueue(queue_t* queue, data_t new_element); 
status_t dequeue(queue_t* queue, data_t* p_dequeued_data); 
status_t peek(queue_t* queue, data_t* p_peek_data);
status_t is_queue_empty(queue_t* queue); 
status_t destroy_queue(queue_t** pp_queue); 

#endif /* _QUEUE_H */