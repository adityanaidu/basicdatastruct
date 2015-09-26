#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "basicdatastruct.h"

bds_queue_t * bds_queue_create() {
    bds_queue_t * bds_queue_handle = NULL ;
    bds_queue_handle = malloc( sizeof(bds_queue_t ) ); 

    if ( bds_queue_handle == NULL ) {
        printf("%s: create_handle unable to allocate memory\n", __FILE__);   
    }
    
    bds_queue_handle->next = NULL ;
    bds_queue_handle->size = 0;
    return bds_queue_handle ;
}

size_t bds_queue_size(bds_queue_t * bds_queue_handle)  {
    if ( bds_queue_handle == NULL ) {
        printf("%s: create_handle unable to allocate memory\n", __FILE__);   
        return 0;
    }
    return bds_queue_handle->size;
}

int bds_queue_destroy(bds_queue_t * bds_queue_handle) {
    a_node_t * element = bds_queue_handle->next;
    a_node_t * next_element = NULL ;
    while ( element != NULL  )  {
        next_element = element->next;
        free(element);
        element = next_element ;
    }

    free(bds_queue_handle);
    return 0;
}

int bds_enqueue(bds_queue_t * bds_queue_handle, const void * val) {
    
    if (bds_queue_handle == NULL) { return -1; }
    
    a_node_t * new_element = malloc(sizeof(a_node_t ) );
    if ( new_element == NULL ) { return -1 ;  }
    new_element->value = val ;
    new_element->next = NULL ;
    
    if (bds_queue_handle->next == NULL)  {
        bds_queue_handle->next = new_element;
        bds_queue_handle->size++ ;
        return 0;
    }

    a_node_t * element = bds_queue_handle->next ;

    while (true) {
        if ( element->next == NULL )  {
               element->next = new_element ;
               bds_queue_handle->size++ ;
               return 0;
        }
        element = element->next ;
    }
    return 0;
}

int print_bds_queue_contents (bds_queue_t *bds_queue_handle) {
    
    printf("Print queue contents\n");
    int idx = 0;

    if (bds_queue_handle == NULL || bds_queue_handle->next == NULL)  {
        printf("Stack empty\n");
        return 0;
    }

    a_node_t * element = bds_queue_handle->next;

    while ( element != NULL ) {
        const void * intp = element->value;
        int val = * (int *) intp ;
        printf("Element index: %d; %d \n", idx, val );
        element = element->next ;
        idx++ ;
    }
    return 0 ;
}

const void * bds_dequeue(bds_queue_t *queue) {
    
    if ( queue == NULL || queue->next == NULL ) {
        return NULL ;
    }
    
    const void * return_value = queue->next->value;

    a_node_t * new_next = queue->next->next ;

    free(queue->next);
    queue->next = new_next;

    queue->size-- ;
    return return_value;
}

