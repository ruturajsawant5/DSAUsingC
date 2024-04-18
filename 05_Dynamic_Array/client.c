#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include "dynamic_array.h"

int main(void)
{
    array_t* pA = NULL; 
    index_t index; 
    data_t data; 
    status_t status; 
    ssize_t N = 8; 

    pA = create_array(N); 
    assert(pA != NULL); 

    assert(create_array(0) == NULL); 
    assert(create_array(-5) == NULL); 

    for(index = 0; index < size(pA); ++index)
    {
        status = set(pA, index, (index+1)*100); 
        assert(status == SUCCESS); 
    }

    assert(set(pA, -8, 100) == INDEX_OUT_OF_RANGE); 
    assert(set(pA, N, 200) == INDEX_OUT_OF_RANGE); 
    assert(set(pA, N + 10, 100) == INDEX_OUT_OF_RANGE); 

    show(pA, "After setting:"); 

    status = get(pA, 4, &data); 
    assert(status == SUCCESS); 
    printf("pA[4]=%d\n", data); 

    status = get(pA, -1, &data); 
    assert(status == INDEX_OUT_OF_RANGE); 
    
    status = get(pA, N, &data); 
    assert(status == INDEX_OUT_OF_RANGE); 

    status = get(pA, 0, &data); 
    assert(status == SUCCESS); 
    printf("pA[0] = %d\n", data); 

    status = get(pA, N-1, &data); 
    assert(status == SUCCESS); 
    printf("pA[%lld-1] = %d\n", N, data); 

    for(index = 0; index < size(pA); ++index)
        assert(set(pA, index, rand()) == SUCCESS); 

    show(pA, "Before Sort:"); 
    sort(pA); 
    show(pA, "After Sort:"); 

    status = get(pA, rand() % size(pA), &data); 
    assert(status == SUCCESS); 
    index = search(pA, data); 
    printf("%d is found at index %lld\n", data, index); 

    assert(search(pA, rand()) == -1); 

    status = destroy_array(&pA); 
    assert(pA == NULL && status == SUCCESS); 

    return (EXIT_SUCCESS); 
}