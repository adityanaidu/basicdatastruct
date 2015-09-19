
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
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
    ht = malloc( sizeof(hashtable_t));

    if (ht == NULL)  {
        printf("Unable to malloc\n");
        return NULL;
    }
    
    ht->numbuckets = num_buckets;
    const void ** table = NULL;
    table = malloc( num_buckets * sizeof(void *));
    
    if (table == NULL)  {
        printf("Unable to allocate table\n");
        return NULL ;
    }

    ht->table = table;
    return ht ;
}

int ht_insert(hashtable_t * ht, const void * key, 
               size_t keylength, const void * value) {
    
    if (ht == NULL)  { return -1; }

    int bucket = adler32(key, keylength) % (ht->numbuckets);
    
    ht->table[bucket] = value;
    return 0;
}

const void * ht_retrieve(hashtable_t *ht, const void * key, size_t keylength ) {
    if (ht == NULL)  { return NULL; }

    int bucket = adler32(key, keylength) % (ht->numbuckets) ;
    return ht->table[bucket];
}

int main(void)  {
    
    hashtable_t * ht = NULL;
    ht = create_hashtable(15);

    if (ht == NULL)  {
        return 1; 
    }

    int * int1 = malloc(sizeof(int));
    *int1 = 11;
    ht_insert(ht, int1, sizeof(int), int1 );
    *int1 = 12;
    ht_insert(ht, int1, sizeof(int), int1 );
    *int1 = 13;
    ht_insert(ht, int1, sizeof(int), int1 );
    
    *int1 = 11;
    printf("Returned for 11: %d\n", * (int *) ht_retrieve(ht, int1, sizeof(int)));
    *int1 = 12;
    printf("Returned for 12: %d\n", * (int *) ht_retrieve(ht, int1, sizeof(int)));
    *int1 = 13;
    printf("Returned for 13: %d\n", * (int *) ht_retrieve(ht, int1, sizeof(int)));
    return 0;
}
