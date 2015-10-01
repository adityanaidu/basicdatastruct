
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "basicdatastruct.h"

int main(void)  {

    bds_stack_t * stack = bds_stack_create();
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

    print_bds_stack_contents(stack);

    void *intVal = pop(stack);
    assert(intVal != NULL);  
    //print_bds_stack_contents(stack);

    destroy_stack(stack);

    bds_linkedlist_t * ll = create_linkedlist();
    assert (ll != NULL);

    int * i = malloc(sizeof(int));
    *i = 15 ;
    assert(bds_linkedlist_insert(ll, i, sizeof(int) ) == 0);
    assert (bds_linkedlist_ispresent(ll, i, sizeof(int) ) == true );

    int * testint = malloc(sizeof(int));
    *testint = 50 ;
    assert(bds_linkedlist_ispresent(ll, testint, sizeof(int) ) == false );

    assert(bds_linkedlist_delete(ll, i, sizeof(int) ) == 0);  

    assert(bds_linkedlist_delete(ll, i, sizeof(int) ) != 0);  
    
    bds_linkedlist_destroy(ll);

    bds_queue_t * queue = bds_queue_create();
    assert( queue != NULL); 

    int1 = malloc(sizeof(int));
    *int1 = 10 ;

    assert (bds_enqueue(queue, int1) == 0 ); 

    print_bds_queue_contents(queue);

    int1 = malloc(sizeof(int));
    *int1 = 20 ;
    assert (bds_enqueue(queue, int1) == 0 );

    print_bds_queue_contents(queue);

    int1 = malloc(sizeof(int));
    *int1 = 30 ;
    assert (bds_enqueue(queue, int1) == 0 );
    //print_bds_queue_contents(queue);

    //printf("Dequeue and print\n");
    bds_dequeue(queue);
    print_bds_queue_contents(queue);

    printf("Dequeue and print\n");
    bds_dequeue(queue);
    print_bds_queue_contents(queue);
    bds_queue_destroy(queue);


    bds_hashtable_t * ht = NULL;
    ht = create_hashtable(32);
    assert (ht != NULL);

    *int1 = 11;
    assert(bds_hashtable_insert(ht, int1, sizeof(int), int1, sizeof(int) ) == 0);

    assert(bds_hashtable_insert(ht, int1, sizeof(int), int1, sizeof(int) ) == 0);

    assert(bds_hashtable_insert(ht, int1, sizeof(int), int1, sizeof(int) ) == 0);

    *int1 = 12;
    assert(bds_hashtable_insert(ht, int1, sizeof(int), int1, sizeof(int) ) == 0);

    *int1 = 13;
    assert(bds_hashtable_insert(ht, int1, sizeof(int), int1, sizeof(int) ) == 0);

    *int1 = 11;
    int retVal =  * (int *) bds_hashtable_retrieve(ht, int1, sizeof(int));
    assert(retVal == 11);

    *int1 = 12;
    retVal =  * (int *) bds_hashtable_retrieve(ht, int1, sizeof(int));
    assert(retVal == 12);

    *int1 = 13;
    retVal =  * (int *) bds_hashtable_retrieve(ht, int1, sizeof(int));
    assert(retVal == 13);

    bds_hashtable_destroy(ht);



    bds_pqueue_t * pq =  bds_create_pqueue(10); 
    int * pri = malloc( sizeof(int));
    * pri = 10 ;
    int rc = bds_pqueue_insert(pq, pri, sizeof(int), pri) ; 
    printf ("Returned %d\n",  * (int*) bds_pqueue_remove(pq)) ; 
    
    bds_pqueue_destroy(pq);
    return 0;
}
