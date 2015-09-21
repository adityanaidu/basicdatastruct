
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "basicdatastruct.h"

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

hashtable_t * create_hashtable(uint32_t num_buckets)  {
    
    hashtable_t * ht = NULL;
    ht = calloc(1, sizeof(hashtable_t));

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

int ht_insert(hashtable_t * ht, const void * key, 
               size_t keylength, const void * value, size_t valuelength) {
    
    if (ht == NULL)  { return -1; }

    int bucket = adler32(key, keylength) % (ht->numbuckets);
    printf("Bucket selected: %d\n", bucket);

    void * keycpy = calloc(1, keylength) ;
    if ( keycpy  == NULL )  { 
        printf("Unable to malloc keycpy\n");
        return -1 ;
    }
    
    if (memcpy(keycpy, key, keylength) == NULL)  {
        return -2 ;
    }

    hash_entry_t * ht_entry = calloc(1, sizeof(hash_entry_t )) ;

    if (ht_entry == NULL )  { 
        printf("Unable to malloc hash_entry_t\n"); 
        return -1 ;
    }
    
    ht_entry->value = value;
    ht_entry->next = NULL;
    ht_entry->keylength = keylength;
    ht_entry->key = keycpy;
    
    if (ht->table[bucket] == NULL)  {
        printf("bucket NULL. Init here\n");
        ht->table[bucket] = ht_entry;
    } 
        
    return 0;
}

const void * ht_retrieve(hashtable_t *ht, const void * key, size_t keylength ) {
    if (ht == NULL)  { return NULL; }
    
    int bucket = adler32(key, keylength) % (ht->numbuckets) ;
    printf("retrieve bucket: %d\n", bucket);

    if (ht->table[bucket] != NULL) {
        printf("keylength %d\n", (int) (ht->table[bucket])->keylength); 
        return (ht->table[bucket])->value; 
    } else {
        return NULL;
    }
}

int main(void)  {
    
    hashtable_t * ht = NULL;
    ht = create_hashtable(32);

    if (ht == NULL)  {
        return 1; 
    }

    int * int1 = malloc(sizeof(int));
    *int1 = 11;
    ht_insert(ht, int1, sizeof(int), int1, sizeof(int) );
    *int1 = 12;
    ht_insert(ht, int1, sizeof(int), int1, sizeof(int) );
    *int1 = 13;
    ht_insert(ht, int1, sizeof(int), int1, sizeof(int) );
    
    *int1 = 11;
    printf("Returned for 11: %d\n", * (int *) ht_retrieve(ht, int1, sizeof(int)));
    *int1 = 12;
    printf("Returned for 12: %d\n", * (int *) ht_retrieve(ht, int1, sizeof(int)));
    *int1 = 13;
    printf("Returned for 13: %d\n", * (int *) ht_retrieve(ht, int1, sizeof(int)));
    return 0;
}
