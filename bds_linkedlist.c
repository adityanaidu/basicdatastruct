
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "basicdatastruct.h"

bds_linkedlist_t * create_linkedlist()  {
    
    bds_linkedlist_t * ll = calloc(1, sizeof(bds_linkedlist_t));

    if (ll == NULL)  {
        printf("Unable to malloc for linkedlist\n");
        return NULL;
    } else {
        ll->next = NULL;
        ll->size = 0;
        return ll;
    }

}

size_t bds_linkedlist_size(bds_linkedlist_t * ll)  {
        
    if (ll == NULL) { return 0; }

    return ll->size;
}

int bds_linkedlist_destroy( bds_linkedlist_t *ll) {
    
    if (ll == NULL) { return 0; }

    a_node_t * curr_node = ll->next;
    a_node_t * next_node = NULL;

    while (curr_node != NULL)  {
        next_node = curr_node->next;
        free(curr_node);
        curr_node = next_node; 
    }

    free(ll);

    return 0;
}

int bds_linkedlist_insert(bds_linkedlist_t * ll, const void * value,
            size_t valuelength)  {
    
   if (value == NULL)  {
       printf("Unable to insert NULL value\n");
       return -1 ;
   }

   if (ll == NULL)  { return -1 ; }

    a_node_t * node = calloc(1, sizeof(a_node_t));

    if (node == NULL)   { return -1;}

    node->next = NULL;
    node->value = value;
    node->valuelength = valuelength;
    
    if (ll->next == NULL )  {
        ll->next = node ;
        ll->size++ ;
        return 0 ;
    }

    a_node_t * current = ll->next; 

    while ( true )  {
       if ( current->next == NULL ) {
           current->next = node ;
           ll->size++ ;
           return 0;
       }
       current = current->next ;
    }

    return -1 ;
}

int bds_linkedlist_delete(bds_linkedlist_t * ll, const void * value,
      size_t valuelength) {
    
    if (ll == NULL || ll->next == NULL )  { 
        printf("Either ll is NULL or its empty\n");
        return -1;  
    }

    a_node_t * current = ll->next;
    a_node_t * prev = NULL ; 

    while ( current )  {
        
        if ( memcmp(current->value, value, valuelength) == 0 ) {
            // delete this element
            if (prev) { //not head link
                prev->next = current->next;
            } else {
                ll->next = current->next ;
            }
            free(current);
            current = NULL;
            ll->size-- ;
            return 0;
        }

        prev = current ;
        current = current->next ;   
    }
    
    return -2 ;
}

bool bds_linkedlist_ispresent(bds_linkedlist_t * ll, const void * value,
             size_t valuelength)   {
    
    if (ll == NULL || ll->next == NULL )  { return false; }

    a_node_t * node = ll->next;
    
    do {
        if ( memcmp(node->value, value, valuelength) == 0 )  {
            return true;
        }
        node = node->next ;
    } while ( node ) ;
    
    return false;
}
