#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "basicdatastruct.h"

queue_t * create_queue() {
    queue_t * queue_handle = NULL ;
    queue_handle = malloc( sizeof(queue_t ) ); 

    if ( queue_handle == NULL ) {
        printf("%s: create_handle unable to allocate memory\n", __FILE__);   
    }
    
    queue_handle->next = NULL ;
    queue_handle->size = 0;
    return queue_handle ;
}

uint32_t queue_size(queue_t * queue_handle)  {
    if ( queue_handle == NULL ) {
        printf("%s: create_handle unable to allocate memory\n", __FILE__);   
        return 0;
    }
    return queue_handle->size;
}

int destroy_queue(queue_t * queue_handle) {
    a_node_t * element = queue_handle->next;
    a_node_t * next_element = NULL ;
    while ( element != NULL  )  {
        next_element = element->next;
        free(element);
        element = next_element ;
    }

    free(queue_handle);
    return EXIT_SUCCESS;
}

int enqueue(queue_t * queue_handle, const void * val) {
    
    if (queue_handle == NULL) { return -1; }
    
    a_node_t * new_element = malloc(sizeof(a_node_t ) );
    if ( new_element == NULL ) { return -1 ;  }
    new_element->value = val ;
    new_element->next = NULL ;
    
    if (queue_handle->next == NULL)  {
        queue_handle->next = new_element;
        queue_handle->size++ ;
        return EXIT_SUCCESS;
    }

    a_node_t * element = queue_handle->next ;

    while (true) {
        if ( element->next == NULL )  {
               element->next = new_element ;
               queue_handle->size++ ;
               return EXIT_SUCCESS;
        }
        element = element->next ;
    }
    return EXIT_SUCCESS;
}

int print_queue_contents (queue_t *queue_handle) {
    
    printf("Print queue contents\n");
    int idx = 0;

    if (queue_handle == NULL || queue_handle->next == NULL)  {
        printf("Stack empty\n");
        return EXIT_SUCCESS;
    }

    a_node_t * element = queue_handle->next;

    while ( element != NULL ) {
        const void * intp = element->value;
        int val = * (int *) intp ;
        printf("Element index: %d; %d \n", idx, val );
        element = element->next ;
        idx++ ;
    }
    return EXIT_SUCCESS ;
}

const void *dequeue(queue_t *queue) {
    
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

int main(void)  {
    
    queue_t * queue = create_queue();
    assert( queue != NULL); 

    int * int1 = malloc(sizeof(int));
    *int1 = 10 ;

    assert (enqueue(queue, int1) == 0 ); 

    print_queue_contents(queue);

    int1 = malloc(sizeof(int));
    *int1 = 20 ;
    assert (enqueue(queue, int1) == 0 );
    
    print_queue_contents(queue);
    
    int1 = malloc(sizeof(int));
    *int1 = 30 ;
    assert (enqueue(queue, int1) == 0 );
    print_queue_contents(queue);
    
    printf("Dequeue and print\n");
    dequeue(queue);
    print_queue_contents(queue);

    printf("Dequeue and print\n");
    dequeue(queue);
    print_queue_contents(queue);
    
    destroy_queue(queue);
    return EXIT_SUCCESS;
}
