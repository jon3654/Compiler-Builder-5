#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED
#include <stdio.h>

#define CODE_SIZE 5000

enum opcode {LIT = 1, OPR, LOD, STO, CAL, INC, JMP, JPC, SIO};

enum ar_log_operation {RET = 0, NEG, ADD, SUB, MUL, DIV, ODD, MOD, EQL, NEQ, LSS, LEQ, GTR, GEQ};

// Function prototypes
void emit(int op, int level, int modifier);
void generate(FILE* ofp);
void no_proc();
void place_inc(int swap, int gen);
void place_jmp();

typedef struct code_pm0 {
    int op;
    int l;
    int m;
} pm0;

pm0 code[CODE_SIZE];

int cx; // Global counter


#endif // GENERATOR_H_INCLUDED
