
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "basicdatastruct.h"

int node_insert(bds_bst_node_t * newnode, bds_bst_node_t *tree, size_t vallen); 

// leftright - which child of the searchrootnode is the delnode
//- if left then leftright is false ; else true
bds_bst_node_t * search_node(bds_bst_node_t *tree, void *value, size_t vallen,
                       bds_bst_node_t **searchrootnode, bool *leftRight);  

void destroy_node(bds_bst_node_t *rootnode); 

bds_bst_node_t * get_lowest_node(bds_bst_node_t * tree, bds_bst_node_t **slnode); 

bds_bst_t * bds_bst_create(size_t valuelength)  {
    bds_bst_t *bst = NULL;

    bst = malloc( sizeof(*bst));
    bst->valuelength= valuelength;
    bst->root = NULL;
    return bst;
}

int bds_bst_insert(bds_bst_t *bst, void * value)   {
    
    if (bst == NULL)  {
        return -1;
    } 

    bds_bst_node_t * node = bst->root ; 
    
    bds_bst_node_t *newnode = malloc( sizeof(*newnode) );
    newnode->value = value;
    newnode->left = NULL;
    newnode->right = NULL;

    if (node == NULL)   {
        bst->root = newnode;
        return 0;
    }

    int rc = node_insert(newnode, node, bst->valuelength);

    if (rc != 0)  {
        free(newnode);   
        return rc ;
    } 

     return 0;
}

int node_insert(bds_bst_node_t * newnode, bds_bst_node_t *tree, size_t vallen) {
    
    int cmp = memcmp(newnode->value, tree->value, vallen ) ; 
    
    if ( cmp == 0)  {
         return -1; // value already present    
    } else if ( cmp < 0 )  {
        if ( tree->left == NULL )  { 
            tree->left = newnode ;
            return 0;
        }  else {
            return node_insert(newnode, tree->left, vallen);
        }
    }  else {
        if (tree->right == NULL)  {
            tree->right = newnode;
            return 0;
        } else {
            return node_insert(newnode, tree->right, vallen);
        }
    }

    return 0;
}

void print_bst( bds_bst_t *bst )  {
    if (bst == NULL)  {
        return ;
    }





}

bool bds_bst_search(bds_bst_t * bst, void * value)  {
    if (! bst )  { return false;  }

    bds_bst_node_t *rootnode = bst->root;

    if (rootnode == NULL) { return false; }
    
    if ( memcmp(rootnode->value, value, bst->valuelength ) == 0 )  {
        return true;
    }

    bds_bst_node_t * dummy = NULL;
    bool leftright ;
    return (search_node(rootnode, value, bst->valuelength, &dummy, &leftright) 
                      != NULL) ? true: false; 
}

bds_bst_node_t * search_node(bds_bst_node_t *tree, 
                      void *value, 
                      size_t vallen,
                      bds_bst_node_t ** searchrootnode, 
                      bool *leftright)  // false = left; true = right
{
    
    if ( tree == NULL )  {  return NULL;  }
    
    int compare = memcmp(value, tree->value, vallen ) ;

    if ( compare == 0 )  {
        return tree;
    } else if ( compare < 0 )  {
        if ( ! tree->left )  {  return NULL;  }
        *searchrootnode = tree;
        *leftright = false;
        return search_node(tree->left, value, vallen, searchrootnode, 
                    leftright);
    } else {
        if ( ! tree->right )  {  return NULL; }
        *searchrootnode = tree;
        *leftright = true;
        return search_node(tree->right, value, vallen, searchrootnode,
                    leftright);
    }

}

int bds_bst_delete(bds_bst_t *bst, void * value)  {
    
    if (bst == NULL)  {
        return -1 ;
    } else if ( bst->root == NULL )  {
        return -2;
    }
    
    bds_bst_node_t *delnode = NULL;
    bds_bst_node_t *searchroot = NULL;
    bool leftright;
    if ( memcmp(value, bst->root , bst->valuelength) == 0 )  {
        free(bst->root);
        bst->root = NULL;
        return 0;
    }  else {
        delnode = search_node(bst->root, value, bst->valuelength, 
                     &searchroot, &leftright);
    }
    
    //didnt find the value to be deleted
    if (delnode == NULL)  { return -3;  }
    
    // node to be deleted is a leaf node
    if (delnode->right == NULL  &&  delnode->left == NULL)  {

        if (leftright == false)  {
            free((searchroot)->left);
            (searchroot)->left = NULL;
        } else  {
            free((searchroot)->right);
            (searchroot)->right = NULL;
        }
        return 0;
    } else if ( delnode->right == NULL )    { 
        // value to be deleted has only one subtree - left
        if ( leftright ) {
            (searchroot)->right = delnode->left ;   
        } else {
            (searchroot)->left = delnode->left ;   
        }
        return 0;
    } else if ( delnode->left == NULL )  { 
        // value to be deleted has one only subtree - right   
        if ( leftright ) {
            (searchroot)->right = delnode->right;
        } else {
            (searchroot)->left = delnode->right;
        }
        return 0;
    }
    
    // both subtrees present
    // now find the right-most leaf in the left tree
    bds_bst_node_t **secondlastnode = NULL;
    bds_bst_node_t *replacement = get_lowest_node(delnode->right, 
                                   secondlastnode);
    
    // replacement and secondlastnode will not be NULL since
    // the node to be deleted is an internal non-root node
    // with two subtrees
    replacement->left = delnode->left;
    (*secondlastnode)->left = replacement->right ;
    
    replacement->right = delnode->right ;
    
    return 0;
}

bds_bst_node_t * get_lowest_node(bds_bst_node_t * tree, bds_bst_node_t **secondlastnode)
{
    if ( ! tree )  {
        return NULL;
    }

    if ( ! tree->left )   {
        return tree;
    }

    secondlastnode = &tree ;
    return get_lowest_node(tree->left, secondlastnode);
}

void destroy_node(bds_bst_node_t *rootnode)   {
    
    if (rootnode->left)  {
        destroy_node(rootnode->left);
    }

    if (rootnode->right)  {
        destroy_node(rootnode->right);
    }

    free(rootnode);
}

void bds_bst_destroy(bds_bst_t * bst) {
    bds_bst_node_t * rootnode = bst->root ;

    destroy_node(rootnode);

    free(bst);    
}
