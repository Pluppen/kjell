#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "source.h"
#include "parser.h"
#include "executor.h"

#include "shell.h"

#define CMD_BUFFER_SIZE 1024
char* read_cmd() {
    char buffer[CMD_BUFFER_SIZE];
    char *ptr = NULL;
    char ptrlen = 0;

    while(fgets(buffer, CMD_BUFFER_SIZE, stdin)) {
        int buflen = strlen(buffer);

        if(!ptr) {
            ptr = malloc(buflen +1);
        } else {
            char *ptr2 = realloc(ptr, ptrlen+buflen+1);

            if(ptr2) {
                ptr = ptr2;
            } else {
                free(ptr);
                ptr = NULL;
            }
        }

        if(!ptr) {
            print_error("kjell: allocation error\n");
            return NULL;
        }

        strcpy(ptr+ptrlen, buffer);

        if(buffer[buflen-1] == '\n'){
            if(buflen == 1 || buffer[buflen-2] != '\\') {
                return ptr;
            }

            ptr[ptrlen+buflen-2] = '\0';
            buflen -= 2;
            print_prompt2();
        }

        ptrlen += buflen;
    }

    return ptr;
}

int parse_and_execute(struct source_s *src) {
    skip_white_spaces(src);

    struct token_s *tok = tokenize(src);

    if(tok == &eof_token) {
        return 0;
    }

    while(tok && tok != &eof_token) {
        struct node_s *cmd = parse_simple_command(tok);

        if(!cmd) {
            break;
        }

        do_simple_command(cmd);
        free_node_tree(cmd);
        tok = tokenize(src);
    }

    return 1;
}

void kjell_loop() {
    char *cmd;

    do {
        print_prompt1();

        cmd = read_cmd();

        if(!cmd) {
            exit(EXIT_FAILURE);
        }

        if(cmd[0] == '\0' || strcmp(cmd, "\n") == 0) {
            free(cmd);
            continue;
        }

        if(strcmp(cmd, "exit\n") == 0) {
            free(cmd);
            break;
        }

        struct source_s src;
        src.buffer = cmd;
        src.bufsize = strlen(cmd);
        src.curpos = INIT_SRC_POS;
        parse_and_execute(&src);

        free(cmd);
    } while(1);
}

int main() {

    initsh();

    kjell_loop();

    return EXIT_SUCCESS;
}
