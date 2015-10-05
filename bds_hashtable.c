
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "basicdatastruct.h"

void destroy_list(hash_entry_t * ) ;
const void * lookup_list(hash_entry_t *, const void * key, size_t keylength) ; 

// The hash function
size_t adler32(const void *buf, size_t buflength)  {
    const uint8_t * buffer = (const uint8_t *) buf ;
    uint32_t s1 = 1;
    uint32_t s2 = 1;
    
    size_t n = 0;
    for (; n< buflength; n++)  {
        s1 = (s1 + buffer[n]) % 65521 ;
        s2 = (s2 + s1) % 65521 ;
    }

    return (size_t) (( s2 << 16 ) | s1) ;
}

bds_hashtable_t * bds_hashtable_create(size_t num_buckets)  {
    
    bds_hashtable_t * ht = NULL;
    ht = calloc(1, sizeof(bds_hashtable_t));

    if (ht == NULL)  {
        printf("Unable to malloc\n");
        return NULL;
    }
    
    ht->numbuckets = num_buckets;
    hash_entry_t ** table =  (calloc( num_buckets, sizeof(hash_entry_t *)));
    
    if (table == NULL)  {
        printf("Unable to allocate table\n");
        return NULL ;
    }

    ht->table = table;
    return ht ;
}

int bds_hashtable_insert(bds_hashtable_t * ht, const void * key, 
               size_t keylength, const void * value) {
    
    if (ht == NULL)  { return -1; }
    if (key == NULL)  { return -2; }

    size_t bucket = adler32(key, keylength) % (ht->numbuckets);
   // printf("Inserting key %d; in bucket %zu\n", *(int *) key, bucket);
    void * keycpy = calloc(1, keylength) ;
    if ( keycpy  == NULL )  { 
        printf("Unable to malloc keycpy\n");
        return -1 ;
    }
    
    if ( memcpy(keycpy, key, keylength) == 0 )  {
        free(keycpy);
        return -2 ;
    }

    hash_entry_t * ht_entry = malloc( sizeof(hash_entry_t ) );

    if (ht_entry == NULL )  { 
        printf("Unable to malloc hash_entry_t\n"); 
        free(keycpy);
        return -1 ;
    }
    
    ht_entry->value = value;
    ht_entry->next = NULL;
    ht_entry->keylength = keylength;
    ht_entry->key = keycpy;
    
    if (ht->table[bucket] == NULL)  {
        ht->table[bucket] = ht_entry;
    } else {
        
        hash_entry_t * he = ht->table[bucket] ; 
        
        while ( he->next != NULL)  {
            he = he->next;
        }

        he->next = ht_entry;
    }

    return 0;
}

const void * bds_hashtable_retrieve(bds_hashtable_t *ht, const void * key,
                   size_t keylength ) {
    if (ht == NULL)  { return NULL; }
    
    size_t bucket = adler32(key, keylength) % (ht->numbuckets) ;

    return lookup_list(ht->table[bucket], key, keylength); 
}

void ll_print(hash_entry_t *ht)   {
   
   if (ht == NULL)  { return ; }
   
   do {
      printf("Value: %d\n", * (int *) ht->value);
      ht = ht->next;
   } while ( ht ) ;
}

void bds_hashtable_print(bds_hashtable_t *ht)    {
    
    if ( ht == NULL ) { printf("ht NULL\n"); return ; }

    hash_entry_t ** table = ht->table ;
    
    size_t idx = 0;
    while ( idx < ht->numbuckets )  {
        printf("--Printing table: %zu\n", idx) ;
        ll_print( *table);
        idx++ ; table++;
    }
   
}

void destroy_list(hash_entry_t * he ) {
    
    hash_entry_t * curr = he ;
    hash_entry_t * next = NULL ;
    while (curr) {
        next = curr->next;
        free(curr->key);
        free(curr);
        curr = next;
    }
}

const void * lookup_list(hash_entry_t *he, const void * key, size_t keylen) {
    
    hash_entry_t * curr = he ;
    while (curr) {
        if (memcmp(curr->key, key, keylen) == 0)  {
           return curr->value ;
        }
        curr = curr->next;
    }
    
    return NULL ;
}

int bds_hashtable_delete(bds_hashtable_t * ht, const void *key, size_t keylen) {
    
    if (ht == NULL)  {return -1 ;}

    size_t bucket = adler32(key, keylen) % (ht->numbuckets);

    hash_entry_t * curr = ht->table[bucket]; 
    hash_entry_t * prev = NULL;
    if ( ! curr )  {  return -1;  }
    
    do {
        if ( memcmp(curr->key, key, keylen) == 0 )  { //found item to delete

            if ( prev )  { // not head of list
                prev->next = curr->next;
                free(curr->key);
                free(curr);
            } else { //head of list 
                hash_entry_t * nexthe = ht->table[bucket]->next;
                free(ht->table[bucket]->key);
                free(ht->table[bucket]);
                ht->table[bucket] = nexthe ;
            }
            return 0;
        }

        prev = curr;
        curr = curr->next ;
    } while ( curr ) ;

    return -1;
}

void bds_hashtable_destroy(bds_hashtable_t *ht)   {
    
    if (ht == NULL)  { return ; }

    hash_entry_t ** table = ht->table ;

    size_t numbuckets = ht->numbuckets;
    size_t idx = 0;

    for ( ; idx <  numbuckets ; idx++ )  {
        if ( *table )  {
            destroy_list( *table);
        }
        table++ ;
    }

    free(ht->table);
    free(ht);
}
