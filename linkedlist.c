
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "basicdatastruct.h"

linkedlist_t * create_linkedlist()  {
    
    linkedlist_t * ll = calloc(1, sizeof(linkedlist_t));

    if (ll == NULL)  {
        printf("Unable to malloc for linkedlist\n");
        return NULL;
    } else {
        ll->next = NULL;
        ll->size = 0;
        return ll;
    }

}

uint32_t linkedlist_size(linkedlist_t * ll)  {
        
    if (ll == NULL) { return 0; }

    return ll->size;
}

int destroy_linkedlist( linkedlist_t *ll) {
    
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

int ll_insert(linkedlist_t * ll, const void * value, size_t valuelength)  {
    
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

    return 0 ;
}

int ll_delete(linkedlist_t * ll, const void * value, size_t valuelength) {
    
    if (ll == NULL || ll->next == NULL )  { 
        printf("Either ll is NULL or its empty\n");
        return -1;  
    }

    a_node_t * current = ll->next;
    a_node_t * prev = (a_node_t *) ll ; // ugly hack 

    while ( current != NULL )  {
        
        if ( memcmp(current->value, value, valuelength) == 0 ) {
            // delete this element
            prev->next = current->next;
            free(current);
            ll->size-- ;
            return 0;
        }

        prev = current ;
        current = current->next ;   
    }
    
    printf("Didn't find the element\n");
    return -1 ;
}

bool ll_ispresent(linkedlist_t * ll, const void * value, size_t valuelength)   {
    
    if (ll == NULL)  { return -1; }

    a_node_t * node = ll->next;

    while(node != NULL)  {
        
        if ( memcmp(node->value, value, valuelength) == 0 )  {
            return true;
        }

        node = node->next ;

    }
    
    return false;
}
