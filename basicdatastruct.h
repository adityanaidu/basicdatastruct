
#ifndef BASICDATASTRUCT_H

#define  BASICDATASTRUCT_H

#include <stdint.h>
#include <stdbool.h>

/**
@file 

This file contains all the public API of this library
*/

typedef struct a_node_t {
    struct a_node_t * next ;
    const void * value ;
    size_t valuelength;
} a_node_t ;

typedef struct bds_queue_t {
    a_node_t * next ;
    a_node_t * last ;
    size_t size;
} bds_queue_t ;

typedef struct bds_stack_t {
    a_node_t * top ;
    size_t size;
} bds_stack_t ;

typedef struct bds_linkedlist_t {
    a_node_t * next ;
    a_node_t * last ;
    size_t size;
} bds_linkedlist_t ;

typedef struct hash_entry_t {
    struct hash_entry_t * next ;
    void * key;
    size_t keylength;
    const void * value;
} hash_entry_t;

typedef struct bds_hashtable_t {
    size_t numbuckets ;    
    hash_entry_t ** table;
} bds_hashtable_t;

typedef struct bds_pqueue_node_t {
    void * priority;
    size_t prioritylen; ///< Currently not used.
    void * value;
} bds_pqueue_node_t ;

typedef struct bds_pqueue_t {
    bds_pqueue_node_t ** array;
    size_t prioritylength; 
    size_t capacity ;
    size_t curr_size ;
} bds_pqueue_t ; 

const void * bds_hashtable_retrieve(bds_hashtable_t *, const void *, size_t );

/**

Delete \p key with length \p keylen from the hashtable
*/
int bds_hashtable_delete(bds_hashtable_t * ht, const void *key, size_t keylen);

/**

\brief Insert \p key \p value pair into \p ht

Memory for \p value has to be managed by caller. A copy of the \p key will be made and managed internally though.

\return 0 if successfull, negative if otherwise
*/
int bds_hashtable_insert(bds_hashtable_t * ht , const void *key , 
         size_t keylength, const void * value); 

bds_hashtable_t * bds_hashtable_create(size_t ); 

/**

free memory allocated for the hashtable infrastructure. Memory allocated by caller to store values is not freed. 
*/
void bds_hashtable_destroy(bds_hashtable_t *ht); 

/**

\brief Creates a singly linked list

*/
bds_linkedlist_t * create_linkedlist(void) ; 

/**

free memory allocated for the linkedlist infrastructure. Memory allocated by caller to store values is not freed. 
*/
int bds_linkedlist_destroy( bds_linkedlist_t *);  

/**

insert \p value into \p ll. size of \p valuesize is the size of \p value. Takes O(n) time

*/
int bds_linkedlist_insert(bds_linkedlist_t *ll, const void *value, 
          size_t valuesize); 

/**

delete \p value of size \p valuesize.Takes O(n) time
*/
int bds_linkedlist_delete(bds_linkedlist_t *, const void * value,
            size_t valuesize) ;

/**
Takes O(n) time.
*/

bool bds_linkedlist_ispresent(bds_linkedlist_t *, const void *, size_t ) ; 


bds_stack_t * bds_stack_create(void); 

/**

\return Number of items in the stack. Takes O(1) time
*/
size_t bds_stack_size(bds_stack_t * bds_stack_handle) ;

/**

free memory allocated for the stack infrastructure. Memory allocated by caller to store values is not freed. 
*/
int destroy_stack(bds_stack_t * bds_stack_handle) ;

/**

\brief Memory for \p value has to be managed by caller. Takes O(1) time

*/
int bds_stack_push(bds_stack_t * bds_stack_handle, const void * value);

/**
Takes O(1) time
*/
void *bds_stack_pop(bds_stack_t *stack) ; 

/**

\return Number of items in the stack. Takes O(1) time
*/
size_t bds_stack_size(bds_stack_t * bds_stack_handle);

/**

queue as the name suggest and is experienced in everyday life is a 
collection of items where when an item is removed its the item which has been in the queue the longest - see #bds_dequeue. Any item which is inserted in the queue is enqueued at the tail of the queue - see #bds_enqueue

Note that none of the functions in the whole of basicdatastruct library are thread safe
*/
bds_queue_t * bds_queue_create(void) ;

/**
@brief Add an item to the queue

Memory for value has to be managed by the caller. Takes O(n) time
*/
int bds_enqueue(bds_queue_t * bds_queue_handle, const void * value);  

/**
@brief Remove the first item from the queue and return a pointer to it.

Takes O(1) time

*/
const void * bds_dequeue(bds_queue_t * ) ; 

/**

free memory allocated for the queue infrastructure. Memory allocated by caller to store values is not freed. 
*/

int bds_queue_destroy(bds_queue_t * ); 

/**
@brief Returns the number of items in the queue. Takes O(1) time
*/
size_t bds_queue_size(bds_queue_t * );

/**

@brief Creates a priority queue which can contain at most \p capacity items
*/
bds_pqueue_t * bds_pqueue_create(size_t capacity, size_t prioritylength) ; 

/**
@brief Inserts \p item in \p pqueue. User needs to allocate memory for \p item.

*/
int bds_pqueue_insert(bds_pqueue_t *pqueue, void * priority, void * item);  

/**

@brief Remove (possibly one of ) the lowest priority item
*/
void * bds_pqueue_remove(bds_pqueue_t *pqueue) ;

/**
@brief free up all memory allocated by the library. 

*/
void bds_pqueue_destroy(bds_pqueue_t * pqueue);

/**
@brief Returns the number of items currently in \p pqueue. Takes O(1) time
*/
size_t bds_pqueue_size(bds_pqueue_t * pqueue);

/**
@brief Returns the capacity of \p pqueue
*/
size_t bds_pqueue_capacity(bds_pqueue_t * pqueue);


#endif  // BASICDATASTRUCT_H 
