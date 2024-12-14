#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dialogue.h"

struct dialogue_info *dialogue;

struct dialogue_info * create_dialogue() {
    struct dialogue_info *temp_dialogue = (struct dialogue_info *)malloc(sizeof(struct dialogue_info));
    if (!temp_dialogue) {
        fprintf(stderr, "Error: create_dialogue falls. Malloc Error.\n");
        exit(EXIT_FAILURE);
    }
    temp_dialogue->lines = NULL;
    temp_dialogue->line_count = 0;
    return temp_dialogue;
}

void add_line_to_dialogue(struct dialogue_info *d, const char *line) {
    char **temp = (char **)realloc(d->lines, sizeof(char *) * (d->line_count + 1));
    if (!temp) {
        fprintf(stderr, "Error: add_line_to_dialogue falls. Re-allocating Error.\n");
        exit(EXIT_FAILURE);
    }
    d->lines = temp;
    d->lines[d->line_count] = strdup(line);
    d->line_count++;
}

void free_dialogue(struct dialogue_info *d) {
    for (int i = 0; i < d->line_count; ++i) {
        free(d->lines[i]);
    }
    free(d->lines);
    free(d);
}
