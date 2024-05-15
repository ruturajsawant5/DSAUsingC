#include "stack.h"

stack_t* create_stack(void)
{
    return create_list(); 
}

status_t push(stack_t* stack, data_t new_element)
{
    return insert_end(stack, new_element); 
}

status_t pop(stack_t* stack, data_t* p_poped_data)
{
    return pop_end(stack, p_poped_data); 
}

status_t top(stack_t* stack, data_t* p_top_data)
{
    return get_end(stack, p_top_data); 
}   

status_t is_empty(stack_t* stack)
{
    return is_list_empty(stack); 
}

status_t destroy_stack(stack_t** pp_stack)
{
    return destroy_list(pp_stack); 
}