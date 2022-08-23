CC=gcc

compile:
	CC -o kjell kjell.c node.c source.c scanner.c parser.c executor.c prompt.c builtins/builtins.c builtins/dump.c symtable/symtab.c initsh.c
