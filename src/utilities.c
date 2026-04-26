#include "../include/utilities.h"

#include <stdio.h>
#include <stdlib.h>

void report_error(char* error) {
    fprintf(stderr, "Received error: %s\n", error);
    exit(EXIT_FAILURE);
}
