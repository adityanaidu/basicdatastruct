#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "basicdatastruct.h"

bds_stack_t * bds_stack_create() {
    bds_stack_t * bds_stack_handle = NULL ;
    bds_stack_handle = malloc( sizeof(bds_stack_t ) ); 

    if ( bds_stack_handle == NULL ) {
        printf("%s: create_handle unable to allocate memory\n", __FILE__);   
    }
    
    bds_stack_handle->top = NULL ;
    bds_stack_handle->size = 0;
    return bds_stack_handle ;
}

size_t bds_stack_size(bds_stack_t * bds_stack_handle)  {

    if ( bds_stack_handle == NULL )  { return 0; }   

    return bds_stack_handle->size;
}

int destroy_stack(bds_stack_t * bds_stack_handle) {

    a_node_t * element = bds_stack_handle->top;
    a_node_t * next_element = NULL ;
    while ( element != NULL  )  {
        next_element = element->next;
        free(element);
        element = next_element ;
    }

    free(bds_stack_handle);
    return 0;
}

int push(bds_stack_t * bds_stack_handle, const void * val) {
    
    if (bds_stack_handle == NULL) { return -1; }
    
    a_node_t * old_top = bds_stack_handle->top ;

    a_node_t * new_top = malloc(sizeof(a_node_t ) );
    if ( new_top == NULL ) { return -1 ;  }
    new_top->value = (void *) val ;
    bds_stack_handle->top = new_top ;
    
    new_top->next = old_top ;
    bds_stack_handle->size++ ;
    return 0;
}

int print_bds_stack_contents (bds_stack_t *bds_stack_handle) {
    
    printf("Print stack contents\n");
    int idx = 0;

    if (bds_stack_handle == NULL || bds_stack_handle->top == NULL)  {
        printf("Stack empty\n");
        return 0;
    }

    a_node_t * element = bds_stack_handle->top;
    
    const void * intp = NULL;
    while ( element != NULL ) {
        intp = element->value;
        int val = * (int *) intp ;
        printf("Element index: %d; %d \n", idx, val );
        element = element->next ;
        idx++ ;
    }
    return 0 ;
}

void *pop(bds_stack_t *stack) {
    
    if ( stack == NULL || stack->top == NULL ) {
        return NULL ;
    }
    
    const void * return_value = stack->top->value;

    a_node_t * element = stack->top->next;

    free(stack->top);
    stack->top = element ;
    stack->size-- ;
    return (void *) return_value;
}
