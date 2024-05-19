#define _CRT_RAND_S 
#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include "bst.h"

typedef long long ssize_t; 

void test_bst_normal(void); 
void test_bst_extreme(void); 

int main(void){
    test_bst_normal(); 
    #ifdef BST_TEST_EXTREME
    test_bst_extreme(); 
    #endif 
    return (EXIT_SUCCESS); 
}

void test_bst_normal(void){
    data_t bst_data[] = {   
                            100, 50, 150, 25, 175, 30, 125, 65, 
                            130, 400, 20, 15, 40, 205, 128
                        }; 
    
    data_t min_data, max_data, data_inorder_succ, data_inorder_pred; 
    size_t i;
    status_t status; 

    bst_t* p_bst = NULL; 
     
    p_bst = bst_create(); 
    for(
        i = 0; 
        i < sizeof(bst_data)/sizeof(bst_data[0]); 
        ++i
    ){
        status = bst_insert(p_bst, bst_data[i]); 
        assert(status == SUCCESS); 
    }

    puts("Inorder traversal:"); 
    bst_inorder(p_bst); 

    puts("Preorder traversal:"); 
    bst_preorder(p_bst); 

    puts("Postorder traversal:"); 
    bst_postorder(p_bst); 

    puts("Testing search:"); 
    assert(bst_search(p_bst, 175) == TRUE); 
    assert(bst_search(p_bst, 15) == TRUE); 
    assert(bst_search(p_bst, 130) == TRUE); 
    assert(bst_search(p_bst, 400) == TRUE); 
    assert(bst_search(p_bst, -545) == FALSE);
    assert(bst_search(p_bst, 1000) == FALSE);  
    assert(bst_search(p_bst, 199) == FALSE);
    puts("175, 15, 130, 400->PRESENT"); 
    puts("-545, 1000, 199 -> ABSENT"); 

    status = bst_minimum(p_bst, &min_data); 
    assert(status); 
    printf("min_data=%d\n", min_data); 

    status = bst_maximum(p_bst, &max_data); 
    assert(status); 
    printf("max_data=%d\n", max_data); 

    status = bst_inorder_successor(p_bst, 175, &data_inorder_succ); 
    assert(status); 
    printf("SUCC(175)=%d\n", data_inorder_succ); 

    status = bst_inorder_predecessor(p_bst, 175, &data_inorder_pred); 
    assert(status); 
    printf("PRED(175)=%d\n", data_inorder_pred); 

    assert(
        bst_inorder_predecessor(
            p_bst, 
            min_data, 
            &data_inorder_pred
        ) == BST_NO_INORDER_PREDECESSOR
    ); 

    assert(
        bst_inorder_successor(
            p_bst, 
            max_data, 
            &data_inorder_succ
        ) == BST_NO_INORDER_SUCCESSOR
    ); 

    puts("Testing remove:"); 
    puts("CURR DATA:"); 
    bst_inorder(p_bst); 

    status = bst_remove(p_bst, min_data); 
    assert(status); 
    printf("Remove:%d\n", min_data); 
    bst_inorder(p_bst); 

    status = bst_remove(p_bst, 30); 
    assert(status); 
    printf("Remove:%d\n", 30); 
    bst_inorder(p_bst); 

    status = bst_remove(p_bst, 175); 
    assert(status); 
    printf("Remove:%d\n", 175); 
    bst_inorder(p_bst); 

    status = bst_remove(p_bst, 100); 
    assert(status); 
    printf("Remove:%d\n", 100); 
    bst_inorder(p_bst); 

    status = bst_remove(p_bst, -500); 
    assert(status == BST_DATA_NOT_FOUND); 

    status = bst_destroy(&p_bst); 
    assert(status && !p_bst); 
}

void test_bst_extreme(void){
    bst_t* p_bst = NULL;
    data_t* arr = NULL;  
    ssize_t N = 10000;
    ssize_t i; 
    status_t status; 
    unsigned int num; 

    p_bst = bst_create(); 

    arr = (data_t*)malloc(N * sizeof(int)); 
    for(i = 0; i < N; ++i){
        rand_s(&num); 
        arr[i] = num; 
        status = bst_insert(p_bst, num); 
        assert(status == SUCCESS); 
    }

    bst_inorder(p_bst);     /* 
                                all nodes in sorted order 
                                implies correctness of insertion algorithm
                            */

    for(i = 0; i < N; ++i){
        printf("removing:%d\n", arr[i]); 
        status = bst_remove(p_bst, arr[i]); 
        printf("remaining nodes:%lld\n", p_bst->number_of_elements); 
    }

    status = bst_destroy(&p_bst); 
    assert(status == SUCCESS && p_bst == NULL); 

    puts("BST extreme testing successful"); 
}