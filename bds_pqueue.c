
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "basicdatastruct.h"


// nodeindex parameter is 1 based. But the C array in 0 based
void percolateup(bds_pqueue_t *pqueue, size_t nodeindex)  {
    
    if (nodeindex == 1) { // reached top of tree
        return ;
    }

    size_t childarrayindex = nodeindex-1 ;
    size_t parentarrayindex = nodeindex/2 - 1 ;

    bds_pqueue_node_t * curr_node = pqueue->array[childarrayindex] ;
    bds_pqueue_node_t * parentnode = pqueue->array[parentarrayindex] ;

    if ( memcmp(parentnode->priority, curr_node->priority,
              curr_node->prioritylen) > 0 ) { // swap child and parent
        pqueue->array[childarrayindex] = pqueue->array[parentarrayindex];  
        pqueue->array[parentarrayindex] = curr_node ; 

        percolateup(pqueue, nodeindex/2);
    }
}

// nodeindex parameter is 1 based
int percolatedown(bds_pqueue_t * pqueue, size_t nodeindex) {
    
    size_t parentarrayindex = nodeindex - 1 ;
    size_t minchildarrayindex = 0 ;
    
    if ( pqueue->curr_size < nodeindex * 2 ) {
        return 0; //reached max depth. stop recurrsion
    } else if ( pqueue->curr_size == nodeindex * 2 ) {
        minchildarrayindex = nodeindex * 2 -1 ; // this is the only child
    } else {  // both children present

        // find the min of the two children
        bds_pqueue_node_t * child1 = pqueue->array[nodeindex * 2-1];
        bds_pqueue_node_t * child2 = pqueue->array[nodeindex * 2 ];

        if ( memcmp(child1->priority, child2->priority, child2->prioritylen)
                    > 0 )  {
            minchildarrayindex = nodeindex * 2 ;
        } else {
            minchildarrayindex = nodeindex * 2 - 1 ;
        }
    }
    
    if ( memcmp(pqueue->array[parentarrayindex]->priority,
                 pqueue->array[minchildarrayindex]->priority, 
                  pqueue->array[parentarrayindex]->prioritylen) > 0 ) {
        
        // swap parent and minchild
        bds_pqueue_node_t *tmp =  pqueue->array[parentarrayindex] ;
        pqueue->array[parentarrayindex] =  pqueue->array[minchildarrayindex];
        pqueue->array[minchildarrayindex] = tmp ;

        // try percolating furthur
        percolatedown(pqueue, minchildarrayindex+1) ;
    }

    return 0;
}

bds_pqueue_t * bds_create_pqueue(size_t capacity)  {
    
    bds_pqueue_t * pqueue = NULL;
    pqueue = malloc(sizeof(bds_pqueue_t));

    if (pqueue == NULL)  {
        printf("Unable to malloc\n");
        return NULL;
    }
    
    pqueue->capacity = capacity;
    pqueue->curr_size = 0 ;
    bds_pqueue_node_t ** pqueue_array = 
                                 calloc(capacity, sizeof(bds_pqueue_node_t *));
    
    if (pqueue_array == NULL)  {
        printf("Unable to allocate pqueue_array\n");
        return NULL ;
    }

    pqueue->array = pqueue_array ;
    return pqueue ;
}

void * bds_pqueue_remove(bds_pqueue_t *pqueue)  {
    
    if (pqueue == NULL || pqueue->curr_size == 0)  {
        printf("pqueue is NULL or is empty\n");
        return NULL;
    }
    
    void *returnval = pqueue->array[0]->value;
    (pqueue->curr_size) -- ;
    free(pqueue->array[0]);

    if ( pqueue->curr_size != 0 )  {
        pqueue->array[0] = pqueue->array[pqueue->curr_size ] ;
        percolatedown(pqueue, 1);
    }
    return returnval ;
}

void bds_pqueue_print(bds_pqueue_t * pqueue)  {
    if (pqueue ==  NULL)  {printf("pqueue is NULL\n"); }
    size_t idx = 0;
    printf("Printing pqueue:\n");
    for ( ; idx < pqueue->curr_size; idx++ )  {
        bds_pqueue_node_t * pnode = pqueue->array[idx];
        printf("idx: %zu; pri: %d; val: %d\n", idx, * (int *) (pnode->priority),
                    * (int *) (pnode->value));
    }
}

void bds_pqueue_destroy(bds_pqueue_t * pqueue)  {
    
    size_t idx = 0;
    for ( ; idx < pqueue->curr_size ; idx++ )  {
        free(pqueue->array[idx]);
    }
    
    free(pqueue->array);
    free(pqueue);
}

int bds_pqueue_insert(bds_pqueue_t *pqueue, void * priority, size_t prioritylen, void * value)  {
    
    if (pqueue->capacity == pqueue->curr_size)  {
        return -1 ;
    }

    bds_pqueue_node_t * pnode = malloc(sizeof(bds_pqueue_node_t));

    pnode->priority = priority;
    pnode->prioritylen = prioritylen;
    pnode->value = value;

    pqueue->array[pqueue->curr_size] = pnode ; 
    (pqueue->curr_size)++ ;

    percolateup(pqueue, pqueue->curr_size);

    return 0;
}
