// Team name: Compiler Builder 5
// Jonathan Brownlee
// Jeremy Hofmann
// Christian Acosta
// Cody Boyer
// Devin Barron

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3

// Global variables
int stack[MAX_STACK_HEIGHT];

typedef struct instr {
    int op;
    int l;
    int m;
    } instruction;

// Function prototypes
void print_AC(int opcode, int level, int modifier, int line);
void execute(int opcode, int level, int modifier, char *str, int *lcheck, int *mcheck, int *outcheck, int *out, int *hlt, int *pc, int *bp, int *sp);
int base(int level, int b);

int main(void)
{
    // Declare variables
    int i, hlt=0, check=1, counter=0, sp=0, bp=1, pc=0, ir=0, lcheck, mcheck, outcheck=0, out, temp, tempmod, templev;
    char str[3];
    stack[1]=0;
    stack[2]=0;
    stack[3]=0;

    // Allocate memory for the instructions
    instruction* all=(instruction*)malloc(sizeof(instruction));

    // Scan PL/0 code
    while(check==1)
    {
        // Reallocate memory based on the current number of instructions
        all=(instruction*)realloc(all,(counter+1)*sizeof(instruction));

        // Scan the current instruction
        scanf("%d %d %d", &all[counter].op, &all[counter].l, &all[counter].m);

        // Check for a halt command
        if(all[counter].op==9 && all[counter].l==0 && all[counter].m==2)
        {
            check=0;
        }

        // Increment the counter
        counter++;
    }

    // Print the assembler version of the code
    printf("PL/0 code:\n\n");
    for(i=0; i<counter; i++)
    {
        print_AC(all[i].op, all[i].l, all[i].m, i);
    }

    // Execute the instructions
    printf("\nExecution:\n");
    printf("\t\t\t\tpc\tbp\tsp\tstack\n");
    printf("\t\t\t\t0\t1\t0\n");
    while(hlt==0)
    {
        // Reset the lcheck
        lcheck=0;
        // Reset the mcheck
        mcheck=1;
        // Reset the outcheck
        outcheck=0;
        // Store a temporary value for part of the output
        temp=pc;
        // Store a temporary modifier
        tempmod=all[pc].m;
        // Store a temporary level
        templev=all[pc].l;
        execute(all[pc].op, all[pc].l, all[pc].m, str, &lcheck, &mcheck, &outcheck, &out, &hlt, &pc, &bp, &sp);
        // Check if the modifier should be displayed in the output
        if(mcheck==0)
        {
            printf("%3d\t%s\t\t\t%d\t%d\t%d\t", temp, str, pc, bp, sp);
            for(i=1; i<=sp; i++)
            {
            	if(bp > 1 && i == bp)
	        {
		    printf("| ");
	        }
	        
                printf("%d ", stack[i]);
            }
            printf("\n");
            if(outcheck==1)
            {
                printf("%d\n", out);
            }
        }
        // Check if the level should be displayed in the output
        else if(lcheck==0)
        {
            printf("%3d\t%s\t\t%d\t%d\t%d\t%d\t", temp, str, tempmod, pc, bp, sp);
            for(i=1; i<=sp; i++)
            {
	    	if(bp > 1 && i == bp)
	        {
		    printf("| ");
	        }

                printf("%d ", stack[i]);
		
            }
            printf("\n");
            if(outcheck==1)
            {
                printf("%d\n", out);
            }
        }
        else if(lcheck==1)
        {
            printf("%3d\t%s\t%d\t%d\t%d\t%d\t%d\t", temp, str, templev, tempmod, pc, bp, sp);
            for(i=1; i<=sp; i++)
            {
	        if(bp > 1 && i == bp)
	        {
		    printf("| ");
	        }

	        printf("%d ", stack[i]);
            }
            printf("\n");
            if(outcheck==1)
            {
                printf("%d\n", out);
            }
        }
    }

    return 0;
}

void print_AC(int opcode, int level, int modifier, int line)
{
    // Declare variables
    char operation[3];

    if(opcode==1)
    {
        printf("%3d\tLIT\t\t%d\n", line, modifier);
    }
    if(opcode==2)
    {
        if(modifier==0)
        {
            // RET
            printf("%3d\tRET\n", line);
        }
        else if(modifier==1)
        {
            // NEG
            printf("%3d\tNEG\n", line);
        }
        else if(modifier==2)
        {
            // ADD
            printf("%3d\tADD\n", line);
        }
        else if(modifier==3)
        {
            // SUB
            printf("%3d\tSUB\n", line);
        }
        else if(modifier==4)
        {
            // MUL
            printf("%3d\tMUL\n", line);
        }
        else if(modifier==5)
        {
            // DIV
            printf("%3d\tDIV\n", line);
        }
        else if(modifier==6)
        {
            // ODD
            printf("%3d\tODD\n", line);
        }
        else if(modifier==7)
        {
            // MOD
            printf("%3d\tMOD\n", line);
        }
        else if(modifier==8)
        {
            // EQL
            printf("%3d\tEQL\n", line);
        }
        else if(modifier==9)
        {
            // NEQ
            printf("%3d\tNEQ\n", line);
        }
        else if(modifier==10)
        {
            // LSS
            printf("%3d\tLSS\n", line);
        }
        else if(modifier==11)
        {
            // LEQ
            printf("%3d\tLEQ\n", line);
        }
        else if(modifier==12)
        {
            // GTR
            printf("%3d\tGTR\n", line);
        }
        else if(modifier==13)
        {
            // GEQ
            printf("%3d\tGEQ\n", line);
        }
    }
    if(opcode==3)
    {
        printf("%3d\tLOD\t%d\t%d\n", line, level, modifier);
    }
    if(opcode==4)
    {
        printf("%3d\tSTO\t%d\t%d\n", line, level, modifier);
    }
    if(opcode==5)
    {
        printf("%3d\tCAL\t%d\t%d\n", line, level, modifier);
    }
    if(opcode==6)
    {
        printf("%3d\tINC\t\t%d\n", line, modifier);
    }
    if(opcode==7)
    {
        printf("%3d\tJMP\t\t%d\n", line, modifier);
    }
    if(opcode==8)
    {
        printf("%3d\tJPC\t\t%d\n", line, modifier);
    }
    if(opcode==9)
    {
        if(modifier==0)
        {
            printf("%3d\tINP\n", line);
        }
        else if(modifier==1)
        {
            printf("%3d\tOUT\n", line);
        }
        else if(modifier==2)
        {
            printf("%3d\tHLT\n", line);
        }
    }
}

void execute(int opcode, int level, int modifier, char *str, int *lcheck, int *mcheck, int *outcheck, int *out, int *hlt, int *pc, int *bp, int *sp)
{
  
    // Increment the program counter
    *pc=*pc+1;
    // LIT
    if(opcode==1)
    {
        *sp=*sp+1;
        stack[*sp]=modifier;
        strcpy(str, "LIT");
    }
    // OPR
    if(opcode==2)
    {
      
        // The modifier will not be shown in the output
        *mcheck=0;
        // RET
        if(modifier==0)
        {
            *sp=*bp-1;
            *pc=stack[*sp+4];
            *bp=stack[*sp+3];
            strcpy(str, "RET");
        }
        // NEG
        if(modifier==1)
        {
            stack[*sp]=-stack[*sp];
            strcpy(str, "NEG");
        }
        // ADD
        if(modifier==2)
        {
            *sp=*sp-1;
            stack[*sp]=stack[*sp]+stack[*sp+1];
            strcpy(str, "ADD");
        }
        // SUB
        if(modifier==3)
        {
            *sp=*sp-1;
            stack[*sp]=stack[*sp]-stack[*sp+1];
            strcpy(str, "SUB");
        }
        // MUL
        if(modifier==4)
        {
            *sp=*sp-1;
            stack[*sp]=stack[*sp]*stack[*sp+1];
            strcpy(str, "MUL");
        }
        // DIV
        if(modifier==5)
        {
            *sp=*sp-1;
            stack[*sp]=stack[*sp]/stack[*sp+1];
            strcpy(str, "DIV");
        }
        // ODD
        if(modifier==6)
        {
            stack[*sp]=stack[*sp]%2;
            strcpy(str, "ODD");
        }
        // MOD
        if(modifier==7)
        {
            *sp=*sp-1;
            stack[*sp]=stack[*sp]%stack[*sp+1];
            strcpy(str, "MOD");
        }
        // EQL
        if(modifier==8)
        {
            *sp=*sp-1;
            stack[*sp]=stack[*sp]==stack[*sp+1];
            strcpy(str, "EQL");
        }
        // NEQ
        if(modifier==9)
        {
            *sp=*sp-1;
            stack[*sp]=stack[*sp]!=stack[*sp+1];
            strcpy(str, "NEQ");
        }
        // LSS
        if(modifier==10)
        {
            *sp=*sp-1;
            stack[*sp]=stack[*sp]<stack[*sp+1];
            strcpy(str, "LSS");
        }
        // LEQ
        if(modifier==11)
        {
            *sp=*sp-1;
            stack[*sp]=stack[*sp]<=stack[*sp+1];
            strcpy(str, "LEQ");
        }
        // GTR
        if(modifier==12)
        {
            *sp=*sp-1;
            stack[*sp]=stack[*sp]>stack[*sp+1];
            strcpy(str, "GTR");
        }
        // GEQ
        if(modifier==13)
        {
            *sp=*sp-1;
            stack[*sp]=stack[*sp]>=stack[*sp+1];
            strcpy(str, "GEQ");
        }
    }
    // LOD
    if(opcode==3)
    {
        *sp=*sp+1;
        stack[*sp]=stack[base(level, *bp)+modifier];
        // The level will be displayed in the output
        *lcheck=1;
        strcpy(str, "LOD");
    }
    // STO
    if(opcode==4)
    {
        stack[base(level,*bp)+modifier]=stack[*sp];
        *sp=*sp-1;
        // The level will be displayed in the output
        *lcheck=1;
        strcpy(str, "STO");
    }
    // CAL
    if(opcode==5)
    {
        stack[*sp+1]=0;
        stack[*sp+2]=base(level,*bp);
        stack[*sp+3]=*bp;
        stack[*sp+4]=*pc;
        *bp=*sp+1;
        *pc=modifier;
        // The level will be displayed in the output
        *lcheck=1;
        strcpy(str, "CAL");
    }
    // INC
    if(opcode==6)
    {
        *sp=*sp+modifier;
        strcpy(str, "INC");
    }
    // JMP
    if(opcode==7)
    {
        *pc=modifier;
        strcpy(str, "JMP");
    }
    // JPC
    if(opcode==8)
    {
        if(stack[*sp]==0)
        {
            *pc=modifier;
        }
        *sp=*sp-1;
        strcpy(str, "JPC");
    }
    // SIO
    if(opcode==9)
    {
        // The modifier will not be displayed in the output
        *mcheck=0;
        // OUT
        if(modifier==0)
        {
            // A value will be printed
            *outcheck==1;
            *out=stack[*sp];
            *sp=*sp-1;
            strcpy(str, "OUT");
        }
        // INP
        if(modifier==1)
        {
            *sp=*sp+1;
            scanf("%d", &stack[*sp]);
            strcpy(str, "INP");
        }
        // HLT
        if(modifier==2)
        {
            *hlt=1;
            strcpy(str, "HLT");
        }
    }
}

int base(int level, int b)
{
    while(level>0)
    {
        b=stack[b+1];
        level--;
    }
    return b;
}
