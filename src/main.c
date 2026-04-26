#include <stdio.h>
#include <stdlib.h>

#include "../include/utilities.h"
#include "../include/pass/traverse_file.h"
#include "../include/firstpass/macro_expander.h"


#define tr

int main(int argc, char** argv) { //TODO: Should be able to run on INFINITELY many files.
    const FILE* assembly_source = fopen(argv[1], "r");

    if (argc < 2) {
        report_error("Usage: ./assembler <filename>.s");
    }

    if (assembly_source == NULL) {
        report_error("The file you provided is null!");
    }

    printf("Hello, World!\n");

    /* handle file */

    int count = 0;
    char** my_lines = process_file(argv[1], &count);

    for (int i = 0; i < count; i++) {
        printf("line %d: %s\n", i+1, my_lines[i]);
        free(my_lines[i]);
    }
    free(my_lines);

    /* end of handling a file */

    return 0;
}
