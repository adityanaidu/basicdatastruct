#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "basicdatastruct.h"

bds_queue_t * bds_queue_create() {
    bds_queue_t * bds_queue_handle = NULL ;
    bds_queue_handle = malloc( sizeof( *bds_queue_handle ) ); 

    if ( bds_queue_handle == NULL ) {
        printf("%s: create_handle unable to allocate memory\n", __FILE__);   
    }
    
    bds_queue_handle->next = NULL ;
    bds_queue_handle->last = NULL ;
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

int bds_enqueue(bds_queue_t * queue, const void * val) {
    
    if (queue == NULL) { return -1; }
    
    a_node_t * new_element = malloc(sizeof( *new_element ) );
    if ( new_element == NULL ) { return -1 ;  }
    new_element->value = val ;
    new_element->next = NULL ;
    
    if (queue->next == NULL)  {
        queue->next = new_element;
        queue->last = new_element;
        queue->size++ ;
        return 0;
    }  else  {
        queue->last->next = new_element ;
        queue->last = new_element ;
        queue->size++ ;
        return 0;
    }

}

int print_bds_queue_contents (bds_queue_t *queue) {
    
    printf("Print queue contents\n");
    int idx = 0;

    if (queue == NULL || queue->next == NULL)  {
        printf("Stack empty\n");
        return 0;
    }

    a_node_t * element = queue->next;

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

