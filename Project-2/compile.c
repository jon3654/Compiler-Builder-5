#include "parser.h"
#include "tokens.h"
#include "generator.h"

#define MAX_SYMBOL_TABLE_SIZE 100

typedef struct symbol {
 int kind;          // const = 1, var = 2, proc = 3
 char name[12];     // name up to 11 chars
 int val;           // number (ASCII value)
 int level;         // L level
 int addr;          // M address
} symbol;

symbol symbol_table[MAX_SYMBOL_TABLE_SIZE];


int main(int argc, char* argv[]){


    return 0;
}
