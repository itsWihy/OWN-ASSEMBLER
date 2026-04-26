#include "../../include/hashmap/hash_map.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/utilities.h"

unsigned long calculate_hash(const char *key);

void expand_map_if_needed(HashMap *hash_map);
void initialize_map(HashMap *hash_map);

void set_value(HashMap *hash_map, char *key, char *value) {
    if (hash_map == NULL || hash_map->array == NULL)
        initialize_map(hash_map);

    if (hash_map == NULL) {
        report_error("Couldn't initialize hashmap");
        return;
    }

    const unsigned long hash = calculate_hash(key);
    size_t index = hash % hash_map->capacity;

    expand_map_if_needed(hash_map);

    if (hash_map->array[index].key == NULL) {
        hash_map->array[index].key = key;
        hash_map->array[index].value = value;
        hash_map->array[index].hash = hash;
        return;
    }

    /* traverse indexes */
    while (hash_map->array[index].key != NULL && hash_map->array[index].key != key) {
        index++;
        index %= hash_map->capacity;
    }

    hash_map->array[index].key = key;
    hash_map->array[index].value = value;
    hash_map->array[index].hash = hash;

    expand_map_if_needed(hash_map);
}
//TODO: FIX HASH MAP NOT WORKING
char *get_value(const HashMap *hash_map, const char *key) {
    if (hash_map == NULL || hash_map->array == NULL)
        return NULL;

    const unsigned long hash = calculate_hash(key);
    size_t index = hash % hash_map->capacity;

    if (strcmp(hash_map->array[index].key, key) == 0)
        return hash_map->array[index].value;

    while (strcmp(hash_map->array[index].key, key) != 0) {
        if (hash_map->array[index].key == NULL)
            /* We traverse linearly, so if we encountered a null, the key doesn't exist.*/
            return NULL;

        index++;
        index %= hash_map->capacity;
    }

    return hash_map->array[index].value;
}

void initialize_map(HashMap *hash_map) {
    hash_map->capacity = DEFAULT_HASHMAP_CAPACITY;
    hash_map->array = malloc(hash_map->capacity * sizeof(HashMapNodes));

    if (hash_map->array == NULL)
        report_error("Ran out of memory.");
}

void expand_map_if_needed(HashMap *hash_map) {
    hash_map->node_count++;

    if (hash_map->capacity <= hash_map->node_count) {
        hash_map->capacity *= 2;
        hash_map->array = realloc(hash_map->array, hash_map->capacity * sizeof(HashMapNodes));

        if (hash_map->array == NULL)
            report_error("Ran out of memory.");

        for (int i = 0; i < hash_map->capacity; ++i) {
            //todo rehash
        }
    }
}

/* This hash function is inspired by djb2 algorithm. */
unsigned long calculate_hash(const char *key) {
    unsigned long hash = 5381;
    int c;

    /*Run until reach the end of the string*/
    while ((c = *key++))
        hash = (hash << 5) + hash + c; /* hash * 33 + c*/

    return hash;
}
