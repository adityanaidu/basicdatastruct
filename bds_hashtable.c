
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
uint32_t adler32(const void *buf, size_t buflength)  {
    const uint8_t * buffer = (const uint8_t *) buf ;
    uint32_t s1 = 1;
    uint32_t s2 = 1;
    
    size_t n = 0;
    for (; n< buflength; n++)  {
        s1 = (s1 + buffer[n]) % 65521 ;
        s2 = (s2 + s1) % 65521 ;
    }

    return (( s2 << 16 ) | s1) ;
}

bds_hashtable_t * create_hashtable(size_t num_buckets)  {
    
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
               size_t keylength, const void * value, size_t valuelength) {
    
    if (ht == NULL)  { return -1; }

    int bucket = adler32(key, keylength) % (ht->numbuckets);

    void * keycpy = calloc(1, keylength) ;
    if ( keycpy  == NULL )  { 
        printf("Unable to malloc keycpy\n");
        return -1 ;
    }
    
    if (memcpy(keycpy, key, keylength) == NULL)  {
        free(keycpy);
        return -2 ;
    }

    hash_entry_t * bds_hashtable_entry = malloc( sizeof(hash_entry_t ) );

    if (bds_hashtable_entry == NULL )  { 
        printf("Unable to malloc hash_entry_t\n"); 
        free(keycpy);
        return -1 ;
    }
    
    bds_hashtable_entry->value = value;
    bds_hashtable_entry->next = NULL;
    bds_hashtable_entry->keylength = keylength;
    bds_hashtable_entry->key = keycpy;
    
    if (ht->table[bucket] == NULL)  {
        ht->table[bucket] = bds_hashtable_entry;
    } else {
        
        hash_entry_t * he = ht->table[bucket] ; 
        
        while ( he->next != NULL)  {
            he = he->next;
        }

        he->next = bds_hashtable_entry;
    }

    return 0;
}

const void * bds_hashtable_retrieve(bds_hashtable_t *ht, const void * key, size_t keylength ) {
    if (ht == NULL)  { return NULL; }
    
    int bucket = adler32(key, keylength) % (ht->numbuckets) ;

    return lookup_list(ht->table[bucket], key, keylength); 
}

void destroy_list(hash_entry_t *he ) {
    
    hash_entry_t * curr = he ;
    hash_entry_t * next = NULL ;
    while (curr) {
        next = curr->next;
        free(curr->key);
        free(curr);
        curr = next;
    }
}

const void * lookup_list(hash_entry_t *he, const void * key, size_t keylength) {
    
    hash_entry_t * curr = he ;
    while (curr) {
        if (memcmp(curr->key, key, keylength) == 0)  {
           return curr->value ;
        }
        curr = curr->next;
    }
    
    return NULL ;
}

void bds_hashtable_destroy(bds_hashtable_t *ht)   {
    
    if (ht == NULL)  { return ; }

    hash_entry_t * table = ht->table[0];

    uint32_t numbuckets = ht->numbuckets;
    
    uint32_t idx = 0;

    for ( ; idx <  numbuckets ; idx++ )  {
        if ( ! table  )  {
            destroy_list(table);
        }
        table++ ;
    }
    free(ht->table);
    free(ht);
}
