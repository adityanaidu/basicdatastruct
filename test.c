
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "basicdatastruct.h"

int main(void)  {

    stack_t * stack = create_stack();
    assert(stack != NULL);  

    int * int1 = malloc(sizeof(int));
    *int1 = 10 ;

    assert (push(stack, int1) == 0 );  

    int1 = malloc(sizeof(int));
    *int1 = 20 ;
    assert (push(stack, int1) == 0 );  

    int1 = malloc(sizeof(int));
    *int1 = 30 ;
    assert(push(stack, int1) == 0 );

    print_stack_contents(stack);

    void *intVal = pop(stack);
    assert(intVal != NULL);  
    //print_stack_contents(stack);

    destroy_stack(stack);

    linkedlist_t * ll = create_linkedlist();
    assert (ll != NULL);

    int * i = malloc(sizeof(int));
    *i = 15 ;
    assert(ll_insert(ll, i, sizeof(int) ) == 0);
    assert (ll_ispresent(ll, i, sizeof(int) ) == true );

    int * testint = malloc(sizeof(int));
    *testint = 50 ;
    assert(ll_ispresent(ll, testint, sizeof(int) ) == false );

    assert(ll_delete(ll, i, sizeof(int) ) == 0);  

    assert(ll_delete(ll, i, sizeof(int) ) != 0);  
    
    destroy_linkedlist(ll);

    queue_t * queue = create_queue();
    assert( queue != NULL); 

    int1 = malloc(sizeof(int));
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
    //print_queue_contents(queue);

    //printf("Dequeue and print\n");
    dequeue(queue);
    print_queue_contents(queue);

    printf("Dequeue and print\n");
    dequeue(queue);
    print_queue_contents(queue);
    destroy_queue(queue);



    hashtable_t * ht = NULL;
    ht = create_hashtable(32);
    assert (ht != NULL);

    *int1 = 11;
    assert(ht_insert(ht, int1, sizeof(int), int1, sizeof(int) ) == 0);

    assert(ht_insert(ht, int1, sizeof(int), int1, sizeof(int) ) == 0);

    assert(ht_insert(ht, int1, sizeof(int), int1, sizeof(int) ) == 0);

    *int1 = 12;
    assert(ht_insert(ht, int1, sizeof(int), int1, sizeof(int) ) == 0);

    *int1 = 13;
    assert(ht_insert(ht, int1, sizeof(int), int1, sizeof(int) ) == 0);

    *int1 = 11;
    int retVal =  * (int *) ht_retrieve(ht, int1, sizeof(int));
    assert(retVal == 11);

    *int1 = 12;
    retVal =  * (int *) ht_retrieve(ht, int1, sizeof(int));
    assert(retVal == 12);

    *int1 = 13;
    retVal =  * (int *) ht_retrieve(ht, int1, sizeof(int));
    assert(retVal == 13);

    destroy_hashtable(ht);

    return 0;
}
