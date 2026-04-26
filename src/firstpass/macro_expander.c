#include "../../include/firstpass/macro_expander.h"

#include <stdio.h>

#include "../../include/hashmap/hash_map.h"


void expand_macros(char** lines) {
    HashMap map = {0, 0, NULL};

    set_value(&map, "nigga", "bigga");
    printf("yay %s", get_value(&map, "nigga"));

    //while line != starts with
    //MAP all macros to their texts.
}
