
#ifndef BASICDATASTRUCT_H

#define  BASICDATASTRUCT_H

#include <stdint.h>
#include <stdbool.h>

typedef struct a_node_t {
    struct a_node_t * next ;
    const void * value ;
    size_t valuelength;
} a_node_t ;

typedef struct queue_t {
    a_node_t * next ;
    a_node_t * last ;
    uint32_t size;
} queue_t ;

typedef struct stack_t {
    a_node_t * top ;
    uint32_t size;
} stack_t ;

typedef struct linkedlist_t {
    a_node_t * next ;
    a_node_t * last ;
    uint32_t size;
} linkedlist_t ;

typedef struct hash_entry_t {
    struct hash_entry_t * next ;
    void * key;
    size_t keylength;
    const void * value;
} hash_entry_t;

typedef struct hashtable_t {
    int numbuckets ;    
    hash_entry_t ** table;
} hashtable_t;


const void * ht_retrieve(hashtable_t *, const void *, size_t );

int ht_insert(hashtable_t * , const void * , size_t, const void * , size_t ); 

hashtable_t * create_hashtable(uint32_t ); 

linkedlist_t * create_linkedlist(void) ; 

int destroy_linkedlist( linkedlist_t *);  

int ll_insert(linkedlist_t *, const void * , size_t ); 

int ll_delete(linkedlist_t *, const void * , size_t ) ;

bool ll_ispresent(linkedlist_t *, const void *, size_t ) ; 

stack_t * create_stack(); 

uint32_t stack_size(stack_t * stack_handle) ;

int destroy_stack(stack_t * stack_handle) ;

int push(stack_t * stack_handle, const void * val);

void *pop(stack_t *stack) ; 

queue_t * create_queue() ;
#endif  // BASICDATASTRUCT_H 
