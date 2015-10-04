
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "basicdatastruct.h"

int main(void)  {

    bds_stack_t * stack = bds_stack_create();
    assert(stack != NULL);  
    
    size_t intsize = sizeof(int);

    int * int1 = malloc(intsize);
    *int1 = 10 ;
    assert ( bds_stack_push(stack, int1) == 0 );  

    int * int2 = malloc(intsize);
    *int2 = 20 ;
    assert ( bds_stack_push(stack, int2) == 0 );  

    int * int3 = malloc(intsize);
    *int3 = 30 ;
    assert( bds_stack_push(stack, int3) == 0 );

    print_bds_stack_contents(stack);

    void *intVal = bds_stack_pop(stack);
    assert(intVal != NULL);  

    destroy_stack(stack);
    
    free(int1); free(int2); free(int3) ;

    bds_linkedlist_t * ll = create_linkedlist();
    assert (ll != NULL);

    int * i = malloc(intsize);
    *i = 15 ;
    assert(bds_linkedlist_insert(ll, i, intsize ) == 0);
    assert (bds_linkedlist_ispresent(ll, i, intsize ) == true );

    int * testint = malloc(intsize);
    *testint = 50 ;
    assert(bds_linkedlist_ispresent(ll, testint, intsize ) == false );

    assert(bds_linkedlist_delete(ll, i, intsize ) == 0);  

    assert(bds_linkedlist_delete(ll, i, intsize ) != 0);  
    
    bds_linkedlist_destroy(ll);
    free(i); free(testint) ;


    bds_queue_t * queue = bds_queue_create();
    assert( queue != NULL); 

    int1 = malloc(intsize);
    *int1 = 10 ;
    assert (bds_enqueue(queue, int1) == 0 ); 

    print_bds_queue_contents(queue);

    int2 = malloc(intsize);
    *int2 = 20 ;
    assert (bds_enqueue(queue, int2) == 0 );

    print_bds_queue_contents(queue);

    int3 = malloc(intsize);
    *int3 = 30 ;
    assert (bds_enqueue(queue, int3) == 0 );
    
    bds_dequeue(queue);
    print_bds_queue_contents(queue);

    printf("Dequeue and print\n");
    bds_dequeue(queue);
    print_bds_queue_contents(queue);
    bds_queue_destroy(queue);
    free(int1); free(int2); free(int3); 
    

    bds_hashtable_t * ht = NULL;
    ht = create_hashtable(32);
    assert (ht != NULL);
    
    int1 = malloc(intsize);
    *int1 = 11;
    assert(bds_hashtable_insert(ht, int1, intsize, int1) == 0);
    
    assert(bds_hashtable_insert(ht, int1, intsize, int1) == 0);

    assert(bds_hashtable_insert(ht, int1, intsize, int1) == 0);
    
    int2 = malloc(intsize);
    *int2 = 12;
    assert(bds_hashtable_insert(ht, int2, intsize, int2) == 0);
    
    int3 = malloc(intsize);
    *int3 = 13;
    assert(bds_hashtable_insert(ht, int3, intsize, int3) == 0);
    
    int retVal =  * (int *) bds_hashtable_retrieve(ht, int1, intsize);
    assert(retVal == 11);

    retVal =  * (int *) bds_hashtable_retrieve(ht, int2, intsize);
    assert(retVal == 12);

    retVal =  * (int *) bds_hashtable_retrieve(ht, int3, intsize);
    assert(retVal == 13);

    bds_hashtable_destroy(ht);
    free(int1); free(int2); free(int3); 


    bds_pqueue_t * pq =  bds_pqueue_create(10, sizeof(char) ); 
    char * pri1 = malloc( sizeof(char ));
    * pri1 = 'E' ;
    int rc = bds_pqueue_insert(pq, pri1, pri1) ; 
    assert (rc == 0 );

    char * pri2 = malloc( sizeof(char ));
    * pri2 = 'B' ;
    rc = bds_pqueue_insert(pq, pri2, pri2) ; 
    assert (rc == 0 );

    int * pri3 = malloc( sizeof(char ));
    * pri3 = 'C' ;
    rc = bds_pqueue_insert(pq, pri3, pri3) ; 
    assert (rc == 0 );
    
    bds_pqueue_print(pq);
    char rv ; 
    
    rv = * (char *) bds_pqueue_remove(pq) ; 
    assert ( rv == 'B' );
    bds_pqueue_print(pq);
    
    rv = * (char *) bds_pqueue_remove(pq) ; 
    assert (rv == 'C' );
    bds_pqueue_print(pq);
    
    rv = * (char *) bds_pqueue_remove(pq) ; 
    assert (rv == 'E' );
    bds_pqueue_print(pq);

    bds_pqueue_destroy(pq);
    free(pri1); free(pri2); free(pri3);
    return 0;
}
