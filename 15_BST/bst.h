#ifndef _BST_H 
#define _BST_H 

#include <stdio.h> 

#define SUCCESS 1 
#define TRUE 1 
#define FALSE 0 
#define BST_DATA_NOT_FOUND 2 
#define BST_EMPTY 3 
#define BST_NO_INORDER_SUCCESSOR 4 
#define BST_NO_INORDER_PREDECESSOR 5 

typedef int data_t; 
typedef int status_t; 
typedef long long ssize_t; 
typedef struct bst_node bst_node_t; 
typedef struct bst bst_t; 

struct bst_node 
{
    data_t data; 
    struct bst_node* left; 
    struct bst_node* right; 
    struct bst_node* parent; 
}; 

struct bst 
{
    bst_node_t* root_node; 
    ssize_t number_of_elements; 
}; 

/* BST Interface Routines */
bst_t* bst_create(void); 

status_t bst_insert(
    bst_t* p_bst,       /* Which bst? */
    data_t new_element  /* Which element? */
); 

status_t bst_remove(
    bst_t* p_bst,       /* Which bst? */
    data_t r_data       /* Which element? */
); 

status_t bst_remove_transplant_version( 
    bst_t* p_bst, 
    data_t r_data
); 

status_t bst_search(
    bst_t* p_bst, 
    data_t search_data
); 

status_t bst_preorder(
    bst_t* p_bst
); 

status_t bst_inorder(
    bst_t* p_bst
); 

status_t bst_postorder(
    bst_t* p_bst
); 

status_t bst_maximum(
    bst_t* p_bst, 
    data_t* p_max_data
); 

status_t bst_minimum(
    bst_t* p_bst, 
    data_t* p_min_data
); 

status_t bst_inorder_successor(
    bst_t* p_bst, 
    data_t ext_data, 
    data_t* p_succ_data
); 

status_t bst_inorder_predecessor(
    bst_t* p_bst, 
    data_t ext_data, 
    data_t* p_pred_data
); 

status_t bst_destroy(
    bst_t** pp_bst
); 

/* BST Auxillary routines */

static void preorder_nodelevel(
    bst_node_t* root_node
); 

static void inorder_nodelevel(
    bst_node_t* root_node
); 

static void postorder_nodelevel(
    bst_node_t* root_node
); 

static bst_node_t* inorder_successor_nodelevel(
    bst_node_t* node
);

static bst_node_t* inorder_predecessor_nodelevel(
    bst_node_t* node
); 

static bst_node_t* search_nodelevel(
    bst_node_t* root_node, 
    data_t data
); 

static void destroy_nodelevel(
    bst_node_t* root_node
); 

static void transplant(
    bst_t* p_bst,
    bst_node_t* u, 
    bst_node_t* v 
); 

static bst_node_t* get_bst_node(
    data_t new_data
); 

static void* xmalloc(
    size_t number_of_bytes
); 

#endif 