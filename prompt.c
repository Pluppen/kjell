#include <stdio.h>
#include "shell.h"
#include "symtable/symtab.h"

void reset_text() {
    printf("\x1b[0m");
}

void print_error(char* error) {
    fprintf(stderr, "\x1b[31m%s\n", error);
    reset_text();
}

void print_prompt1() {
    struct symtab_entry_s *entry = get_symtab_entry("PS1");

    if(entry && entry->val) {
        fprintf(stderr, "%s", entry->val);
    } else {
        fprintf(stderr, "$ ");
    }
}

void print_prompt2() {
     struct symtab_entry_s *entry = get_symtab_entry("PS2");

    if(entry && entry->val) {
        fprintf(stderr, "%s", entry->val);
    } else {
        fprintf(stderr, "> ");
    }
}
