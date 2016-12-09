#include <string.h>
#include <stdio.h>
#include "symbol.h"

void init_array(){
    int i;
    for(i = 0; i < MAX_SYMBOL_TABLE_SIZE; i++){
        symbol_table[i].kind = 0;
        strcpy(symbol_table[i].name, "0");
        symbol_table[i].level = 0;
        symbol_table[i].modifier = 0;
    }
}

void put_symbol(int kind, char *name, int num, int level, int modifier){
    int found = 0;
    int i = 0;
    while(found == 0){
        if(strcmp(symbol_table[i].name, "0") == 0)
            found = 1;
        // error if identifier name and level are the same
        // need to add code in parser to stop program
        else if(strcmp(symbol_table[i].name, name) == 0 && symbol_table[i].level == level){
            printf("Error: Duplicate identifier %s\n", symbol_table[i].name);
            return;
        }
        else if(strcmp(symbol_table[i].name, name) == 0)
            found = 1;
        else
            i++;
    }

    symbol_table[i].kind = kind;
    strcpy(symbol_table[i].name, name);
    symbol_table[i].num = num;
    symbol_table[i].level = level;
    symbol_table[i].modifier = modifier;
    symcount++;
}

int getsymbol(char *name){
    int found = 0;
    int i = 0;

    while(found == 0){
        if(strcmp(symbol_table[i].name, name) == 0)
            found = 1;
        else if (strcmp(symbol_table[i].name, "0") == 0)
            return -1;
        else
            i++;
    }

    return i;
}

void print_array(){
    int found = 0;
    int i = 0;
    while(found == 0){
        if(strcmp(symbol_table[i].name, "0") == 0)
            found = 1;
        else
            printf("%d %s %d %d %d\n", symbol_table[i].kind, symbol_table[i].name, symbol_table[i].num, symbol_table[i].level, symbol_table[i].modifier);
        i++;
    }
}


void delete_vars(int level){
    int i;
    for(i = 0; i < MAX_SYMBOL_TABLE_SIZE; i++)
    {
        if(symbol_table[i].level == level && (symbol_table[i].kind == 1 || symbol_table[i].kind == 0)){
            strcpy(symbol_table[i].name, "0");
            symbol_table[i].kind = 0;
            symbol_table[i].level = 0;
        }
    }
}
