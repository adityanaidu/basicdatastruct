
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "basicdatastruct.h"

void testbst(void)  {
    printf("Testing bst\n");

    bds_bst_t * bst = bds_bst_create(sizeof(int));

    int * int1 = malloc(sizeof(int));
    *int1 = 32;
    bds_bst_insert(bst, int1);

    int * int2 = malloc(sizeof(int));
    *int2 = 33;
    bds_bst_insert(bst, int2);
    
    int * int3 = malloc(sizeof(int));
    *int3 = 30;
    bds_bst_insert(bst, int3);
    
    assert( bds_bst_search( bst, int3) ) ; 
    assert( bds_bst_delete(bst, int3) == 0);

    int * int4 = malloc(sizeof(int));
    *int4 = 40;
    assert( bds_bst_search( bst, int4) == false ) ; 
    assert( bds_bst_delete(bst, int4) == -3);

    bds_bst_destroy(bst);

    free(int1);free(int2);free(int3);free(int4);
}

void teststack(void)  {
    printf("Testing stack\n");

    bds_stack_t * stack = bds_stack_create();
    assert(stack != NULL);  
    
    size_t intsize = sizeof(int);

    int * int1 = malloc(intsize);
    *int1 = 10 ;
    assert ( bds_stack_push(stack, int1) == 0 );  
    assert(bds_stack_size(stack) == 1);

    int * int2 = malloc(intsize);
    *int2 = 20 ;
    assert ( bds_stack_push(stack, int2) == 0 );  

    int * int3 = malloc(intsize);
    *int3 = 30 ;
    assert( bds_stack_push(stack, int3) == 0 );
    
    assert(bds_stack_size(stack) == 3);
    //bds_stack_print(stack);

    int *intVal = (int *) bds_stack_pop(stack);
    assert( *intVal == 30 ); 

    assert(bds_stack_size(stack) == 2);

    destroy_stack(stack);
    
    free(int1); free(int2); free(int3) ;
}

void testlinkedlist(void)   {

    printf("Testing linkedlist\n");
    bds_linkedlist_t * ll = create_linkedlist();
    assert (ll != NULL);

    size_t intsize = sizeof(int);
    
    int * int1 = malloc(intsize);
    *int1 = 15 ;
    assert(bds_linkedlist_insert(ll, int1, intsize ) == 0);
    assert(bds_linkedlist_ispresent(ll, int1, intsize ) == true );
    
    assert(bds_linkedlist_insert(ll, int1, intsize ) == 0);

    int * testint1 = malloc(intsize);
    *testint1 = 50 ;
    assert(bds_linkedlist_insert(ll, testint1, intsize ) == 0);
    assert(bds_linkedlist_ispresent(ll, testint1, intsize ) == true );
    
    int * testint2 = malloc(sizeof(int)) ;
    *testint2 = 51 ;
    assert(bds_linkedlist_ispresent(ll, testint2, intsize) == false );

    assert(bds_linkedlist_delete(ll, int1, intsize ) == 0);  
    assert(bds_linkedlist_delete(ll, int1, intsize ) == 0);  
    assert(bds_linkedlist_ispresent(ll, int1, intsize ) == false);  
    
    int notpresent = 55 ;
    assert(bds_linkedlist_delete(ll, &notpresent, intsize ) == -2);  
    
    bds_linkedlist_destroy(ll);
    free(int1); free(testint1) ; free(testint2) ;
}

void testqueue(void)  {
    printf("Testing queue\n");
    bds_queue_t * queue = bds_queue_create();
    assert( queue != NULL); 
    
    int *int1, *int2, *int3 ;

    size_t intsize = sizeof(int);
    int1 = malloc(intsize);
    *int1 = 10 ;
    assert (bds_enqueue(queue, int1) == 0 ); 

    print_bds_queue_contents(queue);

    int2 = malloc(intsize);
    *int2 = 20 ;
    assert (bds_enqueue(queue, int2) == 0 );

    assert(bds_queue_size(queue) == 2);
    //print_bds_queue_contents(queue);

    int3 = malloc(intsize);
    *int3 = 30 ;
    assert (bds_enqueue(queue, int3) == 0 );
    
    assert(bds_queue_size(queue) == 3);

    bds_dequeue(queue);
    assert(bds_queue_size(queue) == 2);

    //print_bds_queue_contents(queue);

    //printf("Dequeue and print\n");
    bds_dequeue(queue);
    assert(bds_queue_size(queue) == 1);

    //print_bds_queue_contents(queue);
    bds_queue_destroy(queue);
    free(int1); free(int2); free(int3); 
}

void testhashtable(void)   {

    printf("Testing hashtable\n");
    bds_hashtable_t * ht = NULL;
    ht = bds_hashtable_create(16);
    assert (ht != NULL);
    
    int *int1, *int2, *int3 ;
    size_t intsize = sizeof(int);
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
    
    //bds_hashtable_print(ht);

    int retVal =  * (int *) bds_hashtable_retrieve(ht, int1, intsize);
    assert(retVal == 11);

    retVal =  * (int *) bds_hashtable_retrieve(ht, int2, intsize);
    assert(retVal == 12);

    assert( bds_hashtable_delete(ht, int3, intsize) == 0);
    
    assert( bds_hashtable_delete(ht, int3, intsize) == -1 );
    
    assert( bds_hashtable_delete(ht, int1, intsize) == 0 );
                  
    //bds_hashtable_print(ht);
    
    int notfound = 5;
    assert (bds_hashtable_retrieve(ht, &notfound, intsize) == NULL);

    bds_hashtable_destroy(ht);
    free(int1); free(int2); free(int3); 

}

void testpqueue(void)  {
    printf("Testing pqueue\n");

    bds_pqueue_t * pq =  bds_pqueue_create(10, sizeof(char) ); 
    char * pri1 = malloc( sizeof(char ));
    * pri1 = 'E' ;
    int rc = bds_pqueue_insert(pq, pri1, pri1) ; 
    assert (rc == 0 );
    assert(bds_pqueue_size(pq) == 1);
    assert(bds_pqueue_capacity(pq) == 10);
    
    char * pri2 = malloc( sizeof(char ));
    * pri2 = 'B' ;
    rc = bds_pqueue_insert(pq, pri2, pri2) ; 
    assert (rc == 0 );
    assert(bds_pqueue_capacity(pq) == 10);
    
    int * pri3 = malloc( sizeof(char ));
    * pri3 = 'C' ;
    rc = bds_pqueue_insert(pq, pri3, pri3) ; 
    assert(bds_pqueue_size(pq) == 3);
    assert (rc == 0 );
    
    //bds_pqueue_print(pq);
    char rv ; 
    
    rv = * (char *) bds_pqueue_remove(pq) ; 
    assert ( rv == 'B' );
    assert(bds_pqueue_size(pq) == 2);
    // bds_pqueue_print(pq);
    
    rv = * (char *) bds_pqueue_remove(pq) ; 
    assert (rv == 'C' );
    // bds_pqueue_print(pq);
    
    rv = * (char *) bds_pqueue_remove(pq) ; 
    assert (rv == 'E' );
    // bds_pqueue_print(pq);
    assert(bds_pqueue_size(pq) == 0);

    bds_pqueue_destroy(pq);
    free(pri1); free(pri2); free(pri3);
}

int main(void)  {
    
    testpqueue() ; 
    teststack();
    testqueue();

    testlinkedlist();
    testhashtable();
    testbst() ; 

    return 0;
}
