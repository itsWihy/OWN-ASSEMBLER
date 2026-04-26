#include "../../include/pass/traverse_file.h"
#include "../../include/utilities.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 80

void skip_spaces(char *str) {
    char *i = str, *j = str;
    while (*i != '\0') {
        if (!isspace(*i)) {
            *j = *i;
            *j++;
        }
        i++;
    }
    *j = '\0';
}

char** process_file(const char *filename, int *out_count) {
    printf("\n\nstarting working on the file\n");

    FILE* file = fopen(filename, "r");

    if (!file)
        report_error("can't open the file ):");

    char** lines = NULL;
    char line[82];

    int line_num = 0;
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        line_num++;

        if (strlen(line) > MAX_LINE_LEN && line[MAX_LINE_LEN] != '\n' && line[MAX_LINE_LEN] != '\0') {
            report_error("line too long");

            int c;
            while (( c = fgetc(file)) != '\n' && c!= EOF)
                continue;
        }

        line[strcspn(line, "\r\n")] = '\0';

        skip_spaces(line);

        if (line[0] == '\0' || line[0] == ';')
            continue;

        char** temp = realloc(lines, (count + 1) * sizeof(char*));
        lines = temp;
        lines[count] = malloc(strlen(line) + 1);
        if (!temp) {
            report_error("realloc failed");
            break;
        }
        lines = temp;

        lines[count] = malloc(strlen(line) + 1);
        if (lines[count]) {
            strcpy(lines[count], line);
            count++;
        }
    }
    fclose(file);
    *out_count = count;
    return lines;
}
//todo cleanup code