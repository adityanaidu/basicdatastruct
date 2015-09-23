#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "basicdatastruct.h"

stack_t * create_stack() {
    stack_t * stack_handle = NULL ;
    stack_handle = malloc( sizeof(stack_t ) ); 

    if ( stack_handle == NULL ) {
        printf("%s: create_handle unable to allocate memory\n", __FILE__);   
    }
    
    stack_handle->top = NULL ;
    stack_handle->size = 0;
    return stack_handle ;
}

uint32_t stack_size(stack_t * stack_handle)  {

    if ( stack_handle == NULL )  { return 0; }   

    return stack_handle->size;
}

int destroy_stack(stack_t * stack_handle) {

    a_node_t * element = stack_handle->top;
    a_node_t * next_element = NULL ;
    while ( element != NULL  )  {
        next_element = element->next;
        free(element);
        element = next_element ;
    }

    free(stack_handle);
    return EXIT_SUCCESS;
}

int push(stack_t * stack_handle, const void * val) {
    
    if (stack_handle == NULL) { return -1; }
    
    a_node_t * old_top = stack_handle->top ;

    a_node_t * new_top = malloc(sizeof(a_node_t ) );
    if ( new_top == NULL ) { return -1 ;  }
    new_top->value = (void *) val ;
    stack_handle->top = new_top ;
    
    new_top->next = old_top ;
    stack_handle->size++ ;
    return EXIT_SUCCESS;
}

int print_stack_contents (stack_t *stack_handle) {
    
    printf("Print stack contents\n");
    int idx = 0;

    if (stack_handle == NULL || stack_handle->top == NULL)  {
        printf("Stack empty\n");
        return EXIT_SUCCESS;
    }

    a_node_t * element = stack_handle->top;
    
    const void * intp = NULL;
    while ( element != NULL ) {
        intp = element->value;
        int val = * (int *) intp ;
        printf("Element index: %d; %d \n", idx, val );
        element = element->next ;
        idx++ ;
    }
    return EXIT_SUCCESS ;
}

void *pop(stack_t *stack) {
    
    if ( stack == NULL || stack->top == NULL ) {
        return NULL ;
    }
    
    const void * return_value = stack->top->value;

    free(stack->top);
    stack->top = stack->top->next ;
    stack->size-- ;
    return (void *) return_value;
}

/*
int main(void)  {
    
    stack_t * stack = create_stack();
    if (stack == NULL) { 
        fprintf(stdout, "Unable to create stack\n");
        return -1; 
    } 

    int * int1 = malloc(sizeof(int));
    *int1 = 10 ;

    if (push(stack, int1) != 0 ) { 
        printf("Issue pushing: %s\n", __FILE__);   
    }
    
    int1 = malloc(sizeof(int));
    *int1 = 20 ;
    if (push(stack, int1) != 0 ) { 
        printf("Issue pushing: %s\n", __FILE__);   
    }
    
    int1 = malloc(sizeof(int));
    *int1 = 30 ;
    if (push(stack, int1) != 0 ) { 
        printf("Issue pushing: %s\n", __FILE__);   
    }
    
    print_stack_contents(stack);

    void *intVal = pop(stack);
    if (intVal == NULL)  {
        printf("Nothing poped. stack empty\n");
    } else {
        printf("poped Value: %d\n", * (int*) intVal);
    }
    print_stack_contents(stack);
    
    destroy_stack(stack);
    return EXIT_SUCCESS;
}
*/
