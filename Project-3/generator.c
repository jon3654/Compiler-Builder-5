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
        code[cx].op = op;
        code[cx].l = level;
        code[cx].m = modifier;
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


// places INC instruction at end of procedure code if procedures are found in the program
void place_inc(int swap, int gen){
    pm0 temp;
    for(int j = 0; j < swap; j++){
        for(int i = 1; i < gen-1; i++){
            temp = code[i];
            code[i] = code[i+1];
            code[i+1] = temp;
        }
    }
}

// decrements OP code of modifier on JMP JPC and CAL if no procedures are in the program
void dec_op(){
    int i = 1;
    while(code[i].op != 0){
        if(code[i].op == JMP || code[i].op == JPC || code[i].op == CAL){
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



