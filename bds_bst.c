
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "basicdatastruct.h"


int node_insert(bds_bst_node_t * newnode, bds_bst_node_t *tree, size_t vallen); 

bool search_node(bds_bst_node_t *tree, void *value, size_t vallen);  

bds_bst_t * bds_bst_create(size_t valuelength)  {
    bds_bst_t *bst = NULL;

    bst = malloc( sizeof(bds_bst_t));
    bst->valuelength= valuelength;
    bst->root = NULL;
    return bst;
}

int bds_bst_insert(bds_bst_t *bst, void * value)   {
    
    if (bst == NULL)  {
        return -1;
    } 

    bds_bst_node_t * node = bst->root ; 
    
    bds_bst_node_t *newnode = malloc( sizeof(bds_bst_node_t) );
    newnode->value = value;
    newnode->left = NULL;
    newnode->right = NULL;

    if (node == NULL)   {
        bst->root = newnode;
        return 0;
    }

    node_insert(newnode, node, bst->valuelength);

    return 0;
}

int node_insert(bds_bst_node_t * newnode, bds_bst_node_t *tree, size_t vallen) {
    
    if ( memcmp(newnode->value, tree->value, vallen )  <= 0 )  {
        if ( tree->left == NULL )  { 
            tree->left = newnode ;
            return 0;
        }  else {
            node_insert(newnode, tree->left, vallen);
        }
    }  else {
        if (tree->right == NULL)  {
            tree->right = newnode;
            return 0;
        } else {
            node_insert(newnode, tree->right, vallen);
        }
    }

    return 0;

}

bool bds_bst_search(bds_bst_t * bst, void * value)  {
    if (! bst )  { return NULL;  }

    bds_bst_node_t *rootnode = bst->root;

    if (rootnode == NULL) { return false;  }
    
    if ( memcmp(rootnode->value, value, bst->valuelength ) == 0 )  {
        return true;
    } 
    
    return search_node(rootnode, value, bst->valuelength);
}

bool search_node(bds_bst_node_t *tree, void *value, size_t vallen)  {
    
    if ( tree == NULL  )  {  return false;  }

    if ( memcmp(value, tree->value, vallen ) == 0 )  {
        return true;
    } else if (memcmp(value, tree->value, vallen ) < 0 )  {
        return search_node( tree->left, value, vallen);
    } else {
        return search_node( tree->right, value, vallen);
    }

    return false;
}

void bds_bst_destroy(bds_bst_t * bst) {

    
}
