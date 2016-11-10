#ifndef SYMBOL_H_INCLUDED
#define SYMBOL_H_INCLUDED

#define MAX_SYMBOL_TABLE_SIZE 100

typedef struct symbol{
    int kind;
    char name[13];
    int num;
    int level;
    int modifier;
} symbol_type;

int numsym; // keeps tracks of how many symbols are in the symbol table
struct symbol symbol_table[MAX_SYMBOL_TABLE_SIZE];

symbol_type *getsymbol(char* name);
void put_symbol(int kind, char* name, int num, int level, int modifier);

#endif
