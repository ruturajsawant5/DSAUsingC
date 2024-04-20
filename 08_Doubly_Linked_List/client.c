#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include "dll.h" 

int main(void)
{
    dll_t* p_list = NULL; 
    data_t data; 
    status_t status; 

    p_list = create_list();
    show_list(p_list, "After creation:"); 
    puts("assert start"); 
    assert(get_start(p_list, &data) == LIST_EMPTY); 
    assert(get_end(p_list, &data) == LIST_EMPTY); 
    assert(pop_start(p_list, &data) == LIST_EMPTY); 
    assert(pop_end(p_list, &data) == LIST_EMPTY); 
    assert(remove_start(p_list) == LIST_EMPTY); 
    assert(remove_end(p_list) == LIST_EMPTY); 
    assert(get_list_length(p_list) == 0); 
    puts("assert end"); 

    status = insert_start(p_list, 10); 
    assert(status == SUCCESS); 
    show_list(p_list, "insert_start:"); 

    status = insert_end(p_list, 20); 
    assert(status == SUCCESS); 
    show_list(p_list, "insert_end:"); 

    status = insert_after(p_list, 0, 100); 
    puts("assert start"); 
    assert(status == LIST_DATA_NOT_FOUND); 
    puts("assert end"); 

    status = insert_after(p_list, 10, 100); 
    assert(status == SUCCESS); 
    show_list(p_list, "insert_after:"); 

    status = insert_before(p_list, 0, 200); 
    puts("assert start"); 
    assert(status == LIST_DATA_NOT_FOUND); 
    puts("assert end"); 

    status = insert_before(p_list, 100, 200); 
    assert(status == SUCCESS); 
    show_list(p_list, "insert_before:"); 

    status = clear_list(p_list); 
    assert(status == SUCCESS); 

    puts("assert start");  
    assert(get_list_length(p_list) == 0); 
    puts("assert end"); 

    for(data = 0; data <= 50; data += 10)
        assert(insert_end(p_list, data) == SUCCESS);
    show_list(p_list, "insert_end():");

    for(data = 60; data <= 100; data += 10)
        assert(insert_start(p_list, data) == SUCCESS);  
    show_list(p_list, "insert_start()"); 

    assert(get_start(p_list, &data) == SUCCESS); 
    printf("start_data=%d\n", data);
    show_list(p_list, "after get_start():"); 

    assert(get_end(p_list, &data) == SUCCESS);
    printf("end_data = %d\n", data); 
    show_list(p_list, "after get_end()"); 

    assert(pop_start(p_list, &data) == SUCCESS);
    printf("start_data = %d\n", data); 
    show_list(p_list, "after pop_start():"); 

    assert(pop_end(p_list, &data) == SUCCESS);
    printf("end_data = %d\n", data); 
    show_list(p_list, "after pop_end():"); 

    assert(remove_start(p_list) == SUCCESS); 
    show_list(p_list, "after remove_start():"); 

    assert(remove_end(p_list) == SUCCESS);
    show_list(p_list, "after remove_end():");      

    assert(remove_data(p_list, 0) == SUCCESS); 
    show_list(p_list, "after remove_data():"); 

    puts("assert start"); 
    assert(remove_data(p_list, -100) == LIST_DATA_NOT_FOUND); 
    puts("assert end"); 

    printf("length=%d\n", get_list_length(p_list)); 

    show_list(p_list, "Before in-place reversal:"); 
    reverse_list(p_list); 
    show_list(p_list, "After in-place reversal:"); 
    reverse_list(p_list);
    show_list(p_list, "After restoring to original:"); 

    status = destroy_list(&p_list); 
    assert(status == SUCCESS && p_list == NULL);

    puts("end of front end"); 

    return (EXIT_SUCCESS); 
}

