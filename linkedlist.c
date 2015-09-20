
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "basicdatastruct.h"

linkedlist_t * create_linkedlist()  {
    
    linkedlist_t * ll = malloc( sizeof(linkedlist_t));

    if (ll == NULL)  {
        printf("Unable to malloc for linkedlist\n");
        return NULL;
    } else {
        ll->next = NULL;
        return ll;
    }

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

    return 0;
}

int ll_insert(linkedlist_t * ll, const void * value, size_t valuelength)  {
    
   if (value == NULL)  {
       printf("Unable to insert NULL value\n");
       return -1 ;
   }

   if (ll == NULL)  { return -1 ; }

    a_node_t * node = malloc(sizeof(a_node_t));

    if (node == NULL)   { return -1;}

    node->next = NULL;
    node->value = value;
    node->valuelength = valuelength;
    
    if (ll->next == NULL )  {
        ll->next = node ;
        return EXIT_SUCCESS ;
    }

    a_node_t * current = ll->next; 

    while ( true )  {
       if ( current->next == NULL ) {
           current->next = node ;
           return EXIT_SUCCESS;
       }
       current = current->next ;
    }

    return EXIT_SUCCESS ;
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
            return EXIT_SUCCESS;
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

/*
int main(void)  {
  
  linkedlist_t * ll = create_linkedlist();
  
  int * i = malloc(sizeof(int));
  *i = 15 ;
  if (ll_insert(ll, i, sizeof(int) ) != 0)  {
      printf("Issue with insert\n");
  }

  if (ll_ispresent(ll, i, sizeof(int) ) )  {
      printf("value found\n");
  } else {
      printf("value NOT found\n");
  }

  int * testint = malloc(sizeof(int));
  *testint = 50 ;
  if (ll_ispresent(ll, testint, sizeof(int) ) )  {
      printf("value found\n");
  } else {
      printf("value NOT found\n");
  }

  if (ll_delete(ll, i, sizeof(int) ) != 0)  {
      printf("Issue with first delete\n");
  }

  if (ll_delete(ll, i, sizeof(int) ) != 0)  {
      printf("Issue with second delete\n");
  }

  return 0;
}

*/
