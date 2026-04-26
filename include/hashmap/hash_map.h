//
// Created by Wihy on 4/26/26.
//

#ifndef OWN_ASSEMBLER_HASHMAP_H
#define OWN_ASSEMBLER_HASHMAP_H

/* HashMap for the macro expander. Retrieval by char (input) and returns the text to replace with (output) */
/* Standard Hashmap implementation as an ARRAY. */

#define DEFAULT_HASHMAP_CAPACITY 8
#include <stddef.h>

typedef struct HashMapNodes HashMapNodes;
typedef struct HashMap HashMap;

struct HashMapNodes {
    unsigned long hash;
    char *key;
    char *value;
};

struct HashMap {
    size_t capacity;
    size_t node_count;
    HashMapNodes* array; /*Dynamically allocated*/
};

void set_value(HashMap* hash_map, char *key, char *value);
char *get_value(const HashMap* hash_map, const char *key);

#endif //OWN_ASSEMBLER_HASHMAP_H
