#include <stdio.h> 
#include <stdlib.h> 
#include "bst.h"

bst_t* bst_create(void){
    bst_t* p_new_bst = NULL; 

    p_new_bst = (bst_t*)xmalloc(
                    sizeof(bst_t)
                );
    p_new_bst->root_node = NULL; 
    p_new_bst->number_of_elements = 0; 

    return (p_new_bst);  
}

status_t bst_insert(
    bst_t* p_bst,       /* Which bst? */
    data_t new_element  /* Which element? */
){
    bst_node_t* p_new_node = NULL; 
    bst_node_t* run = NULL; 

    p_new_node = get_bst_node(new_element); 
    if(p_bst->root_node == NULL){
        p_bst->root_node = p_new_node; 
        p_bst->number_of_elements += 1; 
        return (SUCCESS); 
    }

    run = p_bst->root_node; 
    while(run != NULL){
        if(new_element <= run->data){
            if(run->left == NULL){
                run->left = p_new_node; 
                p_new_node->parent = run; 
                break; 
            }else{
                run = run->left; 
                continue; 
            }
        }else{
            if(run->right == NULL){
                run->right = p_new_node; 
                p_new_node->parent = run; 
                break; 
            }else{
                run = run->right; 
                continue; 
            }
        }
    }

    p_bst->number_of_elements += 1; 
    return (SUCCESS); 
}

status_t bst_remove(
    bst_t* p_bst,       /* Which bst? */
    data_t r_data       /* Which element? */
){
    bst_node_t* z = NULL;   /*  z will maintain an address pf 
                                node to be removed */
    bst_node_t* y = NULL;   /*  y will store address of succesor of z 
                                in case z has non-empty left and right 
                                subtree*/

    z = search_nodelevel(
            p_bst->root_node, 
            r_data
        ); 
    if(z == NULL)
        return (BST_DATA_NOT_FOUND); 

    if(z->left == NULL){
        if(z->parent == NULL)
            p_bst->root_node = z->right; 
        else if(z == z->parent->left)
            z->parent->left = z->right; 
        else 
            z->parent->right = z->right; 
        
        if(z->right != NULL)
            z->right->parent = z->parent; 
    }else if(z->right == NULL){
        if(z->parent == NULL)
            p_bst->root_node = z->left; 
        else if(z == z->parent->left)
            z->parent->left = z->left; 
        else 
            z->parent->right = z->left; 

        z->left->parent = z->parent; 
    }else{
        y = inorder_successor_nodelevel(z); 
        if(y != z->right){
            y->parent->left = y->right; 
            if(y->right != NULL)
                y->right->parent = y->parent; 
            y->right = z->right; 
            y->right->parent = y; 
        }

        y->left = z->left; 
        y->left->parent = y; 
        if(z->parent == NULL)
            p_bst->root_node = y; 
        else if(z == z->parent->left)
            z->parent->left = y; 
        else 
            z->parent->right = y; 
        y->parent = z->parent; 
    }

    free(z); 
    z = NULL; 

    p_bst->number_of_elements = p_bst->number_of_elements - 1; 

    return (SUCCESS); 
}

status_t bst_remove_transplant_version( 
    bst_t* p_bst, 
    data_t r_data
){
    bst_node_t* z = NULL;   /*  z will maintain an address pf 
                                node to be removed */
    bst_node_t* y = NULL;   /*  y will store address of succesor of z 
                                in case z has non-empty left and right 
                                subtree*/

    z = search_nodelevel(
            p_bst->root_node, 
            r_data
        ); 
    if(z == NULL)
        return (BST_DATA_NOT_FOUND); 

    if(z->left == NULL){
        transplant(p_bst, z, z->right); 
    }else if(z->right == NULL){
        transplant(p_bst, z, z->left); 
    }else{
        y = inorder_successor_nodelevel(z); 
        if(y != z->right){
            transplant(p_bst, y, y->right); 
            y->right = z->right; 
            y->right->parent = y; 
        }

        y->left = z->left; 
        y->left->parent = y; 
        transplant(p_bst, z, y); 
    }

    free(z); 
    z = NULL; 

    p_bst->number_of_elements -= 1; 

    return (SUCCESS);   
}

status_t bst_search(
    bst_t* p_bst, 
    data_t search_data
){
    bst_node_t* node = NULL; 

    node = search_nodelevel(
                p_bst->root_node, 
                search_data   
            ); 

    return (node != NULL);
}

status_t bst_preorder(
    bst_t* p_bst
){
    printf("[START]->"); 
    preorder_nodelevel(p_bst->root_node); 
    puts("[END]"); 
    return (SUCCESS); 
}

status_t bst_inorder(
    bst_t* p_bst
){
    printf("[START]->"); 
    inorder_nodelevel(p_bst->root_node); 
    puts("[END]"); 
    return (SUCCESS); 
}

status_t bst_postorder(
    bst_t* p_bst
){
    printf("[START]->"); 
    postorder_nodelevel(p_bst->root_node); 
    puts("[END]");
    return (SUCCESS);  
}

status_t bst_maximum(
    bst_t* p_bst, 
    data_t* p_max_data
){
    bst_node_t* run = NULL; 

    run = p_bst->root_node;
    if(run == NULL) 
        return (BST_EMPTY); 

    while(run->right != NULL)
        run = run->right;

    *p_max_data = run->data; 
    return (SUCCESS);  
}

status_t bst_minimum(
    bst_t* p_bst, 
    data_t* p_min_data
){
    bst_node_t* run = NULL; 

    run = p_bst->root_node; 
    if(run == NULL)
        return (BST_EMPTY); 

    while(run->left != NULL)
        run = run->left; 

    *p_min_data = run->data; 
    return (SUCCESS); 
} 

status_t bst_inorder_successor(
    bst_t* p_bst, 
    data_t ext_data, 
    data_t* p_succ_data
){
    bst_node_t* p_ext_node = NULL; 
    bst_node_t* p_succ_node = NULL; 

    p_ext_node = search_nodelevel(
                    p_bst->root_node, 
                    ext_data
                    ); 
    if(p_ext_node == NULL)
        return (BST_DATA_NOT_FOUND); 

    p_succ_node = inorder_successor_nodelevel(p_ext_node); 
    if(p_succ_node == NULL)
        return (BST_NO_INORDER_SUCCESSOR); 

    *p_succ_data = p_succ_node->data; 
    return (SUCCESS); 
}

status_t bst_inorder_predecessor(
    bst_t* p_bst, 
    data_t ext_data, 
    data_t* p_pred_data
){
    bst_node_t* p_ext_node = NULL; 
    bst_node_t* p_pred_node = NULL; 

    p_ext_node = search_nodelevel(
                    p_bst->root_node, 
                    ext_data
                ); 
    if(p_ext_node == NULL)
        return (BST_DATA_NOT_FOUND); 

    p_pred_node = inorder_predecessor_nodelevel(p_ext_node); 
    if(p_pred_node == NULL)
        return (BST_NO_INORDER_PREDECESSOR); 

    *p_pred_data = p_pred_node->data; 
    return (SUCCESS); 
}

status_t bst_destroy(
    bst_t** pp_bst
){
    destroy_nodelevel((*pp_bst)->root_node); 
    *pp_bst = NULL; 
    return (SUCCESS); 
}

/* BST Auxillary routines */

static void preorder_nodelevel(
    bst_node_t* root_node
){
    if(root_node != NULL){
        printf("[%d]->", root_node->data); 
        preorder_nodelevel(root_node->left); 
        preorder_nodelevel(root_node->right);
    }
}

static void inorder_nodelevel(
    bst_node_t* root_node
){
    if(root_node != NULL){
        inorder_nodelevel(root_node->left); 
        printf("[%d]->", root_node->data); 
        inorder_nodelevel(root_node->right); 
    }
}

static void postorder_nodelevel(
    bst_node_t* root_node
){
    if(root_node != NULL){
        postorder_nodelevel(root_node->left); 
        postorder_nodelevel(root_node->right); 
        printf("[%d]->", root_node->data); 
    }
}

static bst_node_t* inorder_successor_nodelevel(
    bst_node_t* node
){
    bst_node_t* run = NULL; 
    bst_node_t* x = NULL; 
    bst_node_t* y = NULL; 

    run = node->right; 
    if(run != NULL){
        while(run->left != NULL)
            run = run->left; 
        return (run); 
    }

    x = node; 
    y = x->parent; 
    while(y != NULL && y->right == x){
        x = y; 
        y = x->parent; 
    }

    return (y); 
}

static bst_node_t* inorder_predecessor_nodelevel(
    bst_node_t* node
){
    bst_node_t* run = NULL; 
    bst_node_t* x = NULL; 
    bst_node_t* y = NULL; 

    run = node->left; 
    if(run != NULL){
        while(run->right != NULL)
            run = run->right; 
        return (run); 
    }

    x = node; 
    y = x->parent; 
    while(y != NULL && y->left == x){
        x = y; 
        y = x->parent; 
    }

    return (y); 
}

static bst_node_t* search_nodelevel(
    bst_node_t* root_node, 
    data_t data
){
    bst_node_t* run = NULL; 

    run = root_node; 
    while(run != NULL){
        if(run->data == data)
            break; 
        else if(data < run->data)
            run = run->left; 
        else 
            run = run->right; 
    }

    return (run); 
}

static void transplant(
    bst_t* p_bst,
    bst_node_t* u, 
    bst_node_t* v 
){
    if(u->parent == NULL)
        p_bst->root_node = v; 
    else if(u == u->parent->left)
        u->parent->left = v; 
    else 
        u->parent->right = v; 

    if(v != NULL)
        v->parent = u->parent; 
}

static bst_node_t* get_bst_node(
    data_t new_data
){
    bst_node_t* p_bst_node = NULL; 

    p_bst_node = (bst_node_t*)xmalloc(
                    sizeof(bst_node_t)
                );
    
    p_bst_node->data = new_data; 
    p_bst_node->left = NULL; 
    p_bst_node->right = NULL; 
    p_bst_node->parent = NULL; 

    return (p_bst_node); 
}

static void destroy_nodelevel(
    bst_node_t* root_node
){
    if(root_node != NULL){
        destroy_nodelevel(root_node->left); 
        destroy_nodelevel(root_node->right); 
        free(root_node); 
    }
}

static void* xmalloc(
    size_t number_of_bytes    
){
    void* p = NULL; 

    p = malloc(
            number_of_bytes
        ); 

    if(NULL == p){
        fprintf(stderr, "fatal:out of virtual memory\n"); 
        exit(EXIT_FAILURE); 
    }

    return (p); 
}