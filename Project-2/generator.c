#include <stdio.h>
#include <stdlib.h>
#include "generator.h"
#include "symbol.h"
#include "parser.h"

void emit(int op, int level, int modifier){
    if(cx > CODE_SIZE)
        error(30);
    else
    {
        code[cx].op=op;
        code[cx].l=level;
        code[cx].m=modifier;
        cx++;
    }
}

void generate(FILE* ofp){
    int i;
    for(i=0; i<cx; i++)
    {
        fprintf(ofp, "%d %d %d\n", code[i].op, code[i].l, code[i].m);
    }
}
