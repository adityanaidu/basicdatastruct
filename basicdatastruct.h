
#ifndef BASICDATASTRUCT_H

#define  BASICDATASTRUCT_H

#include <stdint.h>
#include <stdbool.h>

/**
@file 
*/

typedef struct a_node_t {
    struct a_node_t * next ;
    const void * value ;
    size_t valuelength;
} a_node_t ;

typedef struct bds_queue_t {
    a_node_t * next ;
    a_node_t * last ;
    uint32_t size;
} bds_queue_t ;

typedef struct bds_stack_t {
    a_node_t * top ;
    uint32_t size;
} bds_stack_t ;

typedef struct bds_linkedlist_t {
    a_node_t * next ;
    a_node_t * last ;
    uint32_t size;
} bds_linkedlist_t ;

typedef struct hash_entry_t {
    struct hash_entry_t * next ;
    void * key;
    size_t keylength;
    const void * value;
} hash_entry_t;

typedef struct bds_hashtable_t {
    int numbuckets ;    
    hash_entry_t ** table;
} bds_hashtable_t;


const void * bds_hashtable_retrieve(bds_hashtable_t *, const void *, size_t );

int bds_hashtable_insert(bds_hashtable_t * , const void * , size_t, const void * , size_t ); 

bds_hashtable_t * create_hashtable(uint32_t ); 

void bds_hashtable_destroy(bds_hashtable_t *ht); 

void destroy_list(hash_entry_t *he ) ;


bds_linkedlist_t * create_linkedlist(void) ; 

int bds_linkedlist_destroy( bds_linkedlist_t *);  

int bds_linkedlist_insert(bds_linkedlist_t *, const void * , size_t ); 

int bds_linkedlist_delete(bds_linkedlist_t *, const void * , size_t ) ;

bool bds_linkedlist_ispresent(bds_linkedlist_t *, const void *, size_t ) ; 


bds_stack_t * bds_stack_create(); 

uint32_t bds_stack_size(bds_stack_t * bds_stack_handle) ;

int destroy_stack(bds_stack_t * bds_stack_handle) ;

int push(bds_stack_t * bds_stack_handle, const void * val);

void *pop(bds_stack_t *stack) ; 

uint32_t bds_stack_size(bds_stack_t * bds_stack_handle);

/**

queue as the name suggest and is experienced in everyday life is a 
collection of items where when an item is removed its the item which has been in the queue the longest - see #bds_dequeue. Any item which is inserted in the queue is enqueued at the tail of the queue - see #bds_enqueue

Note that none of the functions in the whole of basicdatastruct library are thread safe
*/
bds_queue_t * bds_queue_create() ;

/**
@brief Add an item to the queue

Memory for value has to be managed by the caller
*/
int bds_enqueue(bds_queue_t * bds_queue_handle, const void * value);  

/**
Remove the first item from the queue and return a pointer to it.
*/
const void * bds_dequeue(bds_queue_t *queue) ; 

/**
@brief Returns the number of items in the queue
*/
uint32_t bds_queue_size(bds_queue_t * bds_queue_handle);

#endif  // BASICDATASTRUCT_H 
