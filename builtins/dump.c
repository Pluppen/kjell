#include "../shell.h"
#include "../symtable/symtab.h"

int dump(int argc, char **argv) {
    dump_local_symtab();
    return 0;
}
