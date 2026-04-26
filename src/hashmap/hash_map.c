#include "../../include/hashmap/hash_map.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/utilities.h"

#define FULLNESS_FACTOR 0.75 /* If the capacity is too full, reallocate a bigger hashmap ahead of time. */

#define INSERT_EXISTING_VALUE 1
#define INSERT_NEW_VALUE 0

unsigned long calculate_hash(const char *key);
void expand_map_if_needed(HashMap *hash_map);
void initialize_map(HashMap *hash_map);

int set_value_no_expansion(HashMap *hash_map, char *key, char *value);

void set_value(HashMap *hash_map, char *key, char *value) {
    if (hash_map == NULL) {
        report_error("Null map!");
        return;
    }

    if (hash_map->array == NULL)
        initialize_map(hash_map);

    if (set_value_no_expansion(hash_map, key, value) == INSERT_NEW_VALUE)
        hash_map->node_count++;

    expand_map_if_needed(hash_map);
}

char *get_value(const HashMap *hash_map, const char *key) {
    if (hash_map == NULL || hash_map->array == NULL)
        return NULL;

    const unsigned long hash = calculate_hash(key);
    size_t index = hash % hash_map->capacity;

    if (hash_map->array[index].key == NULL) return NULL;

    if (strcmp(hash_map->array[index].key, key) == 0)
        return hash_map->array[index].value;

    /* We traverse linearly, so if we encountered a null, the key doesn't exist.*/
    while (hash_map->array[index].key != NULL && strcmp(hash_map->array[index].key, key) != 0) {
        index++;
        index %= hash_map->capacity;
    }

    if (hash_map->array[index].key == NULL)
        return NULL;

    return hash_map->array[index].value;
}

void initialize_map(HashMap *hash_map) {
    hash_map->node_count = 0;
    hash_map->capacity = DEFAULT_HASHMAP_CAPACITY;
    hash_map->array = calloc(hash_map->capacity, sizeof(HashMapNodes));

    if (hash_map->array == NULL)
        report_error("Ran out of memory.");
}

void expand_map_if_needed(HashMap *hash_map) {
    if (hash_map->capacity * FULLNESS_FACTOR > hash_map->node_count)
        return;

    HashMapNodes *old_array = hash_map->array;

    hash_map->capacity *= 2;
    hash_map->array = calloc(hash_map->capacity, sizeof(HashMapNodes));

    if (hash_map->array == NULL)
        report_error("Ran out of memory.");

    if (old_array == NULL)
        return;

    /* Rehash keys cuz we changed the size */
    for (size_t i = 0; i < hash_map->capacity / 2; ++i) {
        if (old_array[i].key == NULL)
            continue;

        set_value_no_expansion(hash_map, old_array[i].key, old_array[i].value);
    }

    free(old_array);
}

/*
 * Assumes valid hash_map and hash_map->array!
 */
int set_value_no_expansion(HashMap *hash_map, char *key, char *value) {
    const unsigned long hash = calculate_hash(key);
    size_t index = hash % hash_map->capacity;

    if (hash_map->array[index].key == NULL) {
        hash_map->array[index].key = key;
        hash_map->array[index].value = value;
        hash_map->array[index].hash = hash;
        return INSERT_NEW_VALUE;
    }

    while (hash_map->array[index].key != NULL && strcmp(hash_map->array[index].key, key) != 0) {
        index++;
        index %= hash_map->capacity;
    }

    const char *old_key = hash_map->array[index].key;
    if (old_key == NULL)
        return INSERT_NEW_VALUE;

    hash_map->array[index].key = key;
    hash_map->array[index].value = value;
    hash_map->array[index].hash = hash;

    return strcmp(old_key, key) == 0 ? INSERT_EXISTING_VALUE : INSERT_NEW_VALUE;
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
