#ifndef DANGDGEON_DIALOGUE_H
#define DANGDGEON_DIALOGUE_H

struct dialogue_info {
    char **lines;
    int line_count;
};

extern struct dialogue_info *dialogue;

struct dialogue_info * create_dialogue();
void add_line_to_dialogue(struct dialogue_info *d, const char *line);
void free_dialogue(struct dialogue_info *d);

#endif //DANGDGEON_DIALOGUE_H
