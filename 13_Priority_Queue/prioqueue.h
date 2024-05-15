#ifndef _PRIO_QUEUE_H 
#define _PRIO_QUEUE_H 

#include "dcll.h"

#define PRIO_QUEUE_EMPTY LIST_EMPTY 

typedef dcll_t prio_queue_t; 

prio_queue_t* create_prio_queue(void); 
status_t prio_enqueue(
    prio_queue_t* p_prio_queue, 
    data_t new_data
); 
status_t prio_min_dequeue(
    prio_queue_t* p_prio_queue, 
    data_t* p_min_data
); 
status_t prio_max_dequeue(
    prio_queue_t* p_prio_queue, 
    data_t* p_max_data
); 
status_t is_prio_queue_empty(
    prio_queue_t* p_prio_queue
); 
status_t destroy_prio_queue(
    prio_queue_t** pp_prio_queue
); 

#endif /* _PRIO_QUEUE_H */