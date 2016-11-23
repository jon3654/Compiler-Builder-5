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


// replaces INC instruction if no procedures are found in the program
void place_inc(){
    int i = 0;
    while(code[i].op == JMP || code[i].l > 0){
        i++;
    }
    printf("%d %d %d\n", code[i].op, code[i].l, code[i].m);
    int j;
    pm0 tmp = code[i];
    code[i] = code[0];
    code[0] = tmp;
    printf("%d %d %d\n", tmp.op, tmp.l, tmp.m);
    for(j = 1; j < i; j++){
        tmp = code[j];
        code[j] = code[j+1];
        code[j+1] = tmp;
    }
}

void dec_op(){
    int i = 1;
    while(code[i].op != 0){
        if(code[i].op == JMP || code[i].op == JPC || code[i].op == LOD || code[i].op == STO){
            code[i].m--;
        }
        i++;
    }
}

// removes JMP instruction if no procedures are found in the program
void no_proc(){
    int i;
    code[0] = code[1];
    for(i=1; i<cx; i++)
    {
        code[i] = code[i+1];
    }
    cx--;
    dec_op();
}



