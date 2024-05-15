#ifndef _STACK_H 
#define _STACK_H 

#include "dcll.h"

#define STACK_EMPTY LIST_EMPTY 

typedef dcll_t stack_t; 

stack_t* create_stack(void); 

status_t push(stack_t* stack, data_t new_element);
status_t pop(stack_t* stack, data_t* p_poped_data);
status_t top(stack_t* stack, data_t* p_top_data);   
status_t is_empty(stack_t* stack); 

status_t destroy_stack(stack_t** pp_stack); 

#endif /* _STACK_H */ 