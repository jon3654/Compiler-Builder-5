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
    int i, j;
    for(j = 0; j < swap; j++){
        for(i = 1; i < gen; i++){
            if(code[i].op != JMP){
                temp = code[i];
                code[i] = code[i+1];
                code[i+1] = temp;
            }
        }
    }
}

// decrements modifier on JMP JPC and CAL if no procedures are in the program
void dec_m(){
    int i = 1;
    while(code[i].op != 0){
        if(code[i].op == JMP || code[i].op == CAL || code[i].op == JPC){
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
    dec_m();
}

void place_jmp()
{
    int k = 1;
    int d = 2;
    int i, j;
    for(i = 1; i < d; i++){
        if(code[i].op == INC){
            d++;
        }
        else if(code[i].op == JMP){
            pm0 temp = code[i];
            code[i] = code[k];
            code[k] = temp;
            
            for(j = k+1; j < code[k].m-1; j++){
                temp = code[j];
                code[j] = code[j+1];
                code[j+1] = temp;
            }
        k++;
        }
    }
}

void rm_jmp(int i){
    int j;
    for(j = i; j < cx; j++){
        code[j] = code[j+1];
    }
    cx--;
    dec_m();
}

void swap_jmp(int num){
    int num_found = 1;
    int i, index, index1;
    int swap_done = 0;
    i = 1;
    
    while(num_found < num){
        if(code[i].op == JMP) num_found++;
        i++;
    }
    
    i = 1;
    while(swap_done != 1){
        if(code[i].op == JMP) {swap_done = 1; index = i;}
        i++;
    }
    swap_done = 0;
    num_found = 2;
    while(swap_done != 1){
        if(code[i].op == JMP) {swap_done = 1; index1 = i;}
        i++;
    }
    
    pm0 tmp = code[index];
    code[index] = code[index1];
    code[index1] = tmp;

}











