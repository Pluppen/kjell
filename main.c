#include <stdio.h>

#include "hashtable.c"

void print_options() {
    printf("1. Add\n2. Delete\n3. Search\n4. Quit\n");
}

void add(ht_hash_table* ht) {
    char key[256];
    char value[256];

    printf("Specify key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;

    printf("Specify value: ");
    fgets(value, sizeof(value), stdin);
    value[strcspn(value, "\n")] = 0;

    ht_insert(ht, key, value);
    printf("Added key '%s' with value '%s' into hashtable.\n", key, value);
}

void delete(ht_hash_table* ht) {
    char key[256];

    printf("Specify key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;

    ht_delete(ht, key);
    printf("Deleted key '%s'.\n", key);
}

void search(ht_hash_table* ht) {
    char key[256];

    printf("Specify key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;

    char* value = ht_search(ht, key);
    printf("The value for key '%s' is '%s'\n", key, value);
}

int main(void) {
    ht_hash_table* ht = ht_new();

    char line[256];
    
    print_options();
    printf("Select option: ");
    while(fgets(line, sizeof(line), stdin)) {
        if(*line == '1') {
            printf("Add this shit\n");
            add(ht);
        } else if(*line == '2') {
            printf("Remove this shit\n");
            delete(ht);
        } else if(*line == '3') {
            printf("Search this shit\n");
            search(ht);
        }  else if(*line == '4') {
            printf("Quitting\n");
            exit(0);
        } else {
            printf("Invalid input!\n");
            print_options();
        }

        print_options();
        printf("Select option: ");
    }

    ht_del_hash_table(ht);
}
