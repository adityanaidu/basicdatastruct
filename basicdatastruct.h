
#ifndef BASICDATASTRUCT_H

#define  BASICDATASTRUCT_H
typedef struct a_node_t {
    struct a_node_t * next ;
    const void * value ;
    size_t valuelength;
} a_node_t ;

typedef struct queue_t {
    a_node_t * next ;
} queue_t ;

typedef struct stack_t {
    a_node_t * top ;
} stack_t ;

typedef struct linkedlist_t {
    a_node_t * next ;
} linkedlist_t ;

typedef struct hashtable_t {
    int numbuckets ;    
    const void ** table;
} hashtable_t;


typedef struct hash_entry_t {
    struct hash_entry_t * next ;
    void * value;
    size_t keylength;
    void * key;
} hash_entry_t;

#endif  // BASICDATASTRUCT_H 
