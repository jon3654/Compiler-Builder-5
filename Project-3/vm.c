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
#include "vm.h"

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
void execute(int opcode, int level, int modifier, char *str, int *lcheck, int *mcheck, int *outcheck, int *out, int *inpcheck, 
int *in, int *hlt, int *pc, int *bp, int *sp);
int base(int level, int b);

int vm(char* file)
{
    // Declare variables
    int i, hlt=0, check=1, counter=0, sp=0, bp=1, pc=0, ir=0, lcheck, mcheck, outcheck=0, out, inpcheck=1, in, temp, tempmod, 
templev, end;
    char str[3];
    stack[1]=0;
    stack[2]=0;
    stack[3]=0;

	//Creates FILE pointer ifp, then opens it to the filename given by argv[1] (mcode.pm0 in our case) for reading only.
    int filecount = 0;
    int exists = 1;
    char name[11];
    strcpy(name, "stacktrace");
	FILE *ifp = fopen(file,"r");
    if(ifp == NULL) return 1;
    FILE *ofp;
    while (exists == 1){
        
        char str[filecount%10];
        sprintf(str,"%d",filecount);
        strcat(name, str);
        strcat(name, ".txt");
        ofp = fopen(name,"r");
        if(ofp == NULL){
            ofp = fopen(name,"w");
            exists = 0;
        }
        else{
            strcpy(name, "stacktrace");
            fclose(ofp);
            filecount++;
        }
    }
    // Allocate memory for the instructions
    instruction* all=(instruction*)malloc(sizeof(instruction));

    // Scan PL/0 code
    while(check)
    {
        // Reallocate memory based on the current number of instructions
        all=(instruction*)realloc(all,(counter+1)*sizeof(instruction));

        // Scan the current instruction
        fscanf(ifp,"%d %d %d", &all[counter].op, &all[counter].l, &all[counter].m);
        // Check for a halt command
        if(all[counter].op==9 && all[counter].l==0 && all[counter].m==2)
            check=0;

        // Check to see if the end of the file has been reached
        if(feof(ifp))
        {
            check=0;
            end=counter;
        }

        // Increment the counter
        counter++;
    }



    // Execute the instructions
    fprintf(ofp,"\nExecution:\n");
    fprintf(ofp,"                       pc   bp   sp   stack\n");
    fprintf(ofp,"                        0    1    0   \n");

    while(!hlt)
    {
        // Reset the lcheck
        lcheck=0;
        // Reset the mcheck
        mcheck=1;
        // Reset the outcheck
        outcheck=0;
        // Reset the inpcheck
        inpcheck=0;
        // Store a temporary value for part of the output
        temp=pc;
        // Store a temporary modifier
        tempmod=all[pc].m;
        // Store a temporary level
        templev=all[pc].l;
        execute(all[pc].op, all[pc].l, all[pc].m, str, &lcheck, &mcheck, &outcheck, &out, &inpcheck, &in, &hlt, &pc, &bp, 
&sp);
        // Check if the modifier should be displayed in the output
        if(!mcheck)
        {
            fprintf(ofp, "%3d  %s               %2d   %2d   %2d   ", temp, str, pc, bp, sp);
            for(i=1; i<=sp; i++)
			{
            	if(bp > 1 && i == bp)
		    		fprintf(ofp,"| ");

                fprintf(ofp,"%d ", stack[i]);
            }
            fprintf(ofp,"\n");

            if(outcheck==1)
                fprintf(ofp,"%d\n", out);
            else if(inpcheck==1)
                fprintf(ofp,"read %d from input\n", in);
        }
        // Check if the level should be displayed in the output
        else if(lcheck==0)
        {
            fprintf(ofp, "%3d  %s        %3d    %2d   %2d   %2d   ", temp, str, tempmod, pc, bp, sp);
            for(i=1; i<=sp; i++)
            {
	    		if(bp > 1 && i == bp)
			   		fprintf(ofp,"| ");

                fprintf(ofp,"%d ", stack[i]);
            }
            fprintf(ofp,"\n");

            if(outcheck==1)
                fprintf(ofp,"%d\n", out);
        }

        else if(lcheck==1)
        {
            fprintf(ofp, "%3d  %s    %d   %3d    %2d   %2d   %2d   ", temp, str, templev, tempmod, pc, bp, sp);
            for(i=1; i<=sp; i++)
            {
	        	if(bp > 1 && i == bp)
				    fprintf(ofp,"| ");

	        	fprintf(ofp,"%d ", stack[i]);
            }
            fprintf(ofp,"\n");

            if(outcheck==1)
                fprintf(ofp,"%d\n", out);
        }
        if(pc==end)
            hlt=1;
    }

	//Close the file from reading
	fclose(ifp);
    fclose(ofp);
    return 0;
}

void execute(int opcode, int level, int modifier, char *str, int *lcheck, int *mcheck, int *outcheck, int *out, int *inpcheck, 
int *in, int *hlt, int *pc, int *bp, int *sp)
{

    // Increment the program counter
    *pc=*pc+1;
    switch(opcode){
	    case 1: //LIT
	        *sp=*sp+1;
	        stack[*sp]=modifier;
	        strcpy(str, "LIT");
	        break;

	    case 2: //OPR

	        // The modifier will not be shown in the output
	        *mcheck=0;

	        switch(modifier){
		        case 0: //RET
		            *sp=*bp-1;
		            *pc=stack[*sp+4];
		            *bp=stack[*sp+3];
		            strcpy(str, "RET");
		        	break;

		        case 1: //NEG
		            stack[*sp]=-stack[*sp];
		            strcpy(str, "NEG");
		        	break;

		        case 2: //ADD
		            *sp=*sp-1;
		            stack[*sp]=stack[*sp]+stack[*sp+1];
		            strcpy(str, "ADD");
			        break;

		        case 3: //SUB
		            *sp=*sp-1;
		            stack[*sp]=stack[*sp]-stack[*sp+1];
		            strcpy(str, "SUB");
		        	break;

		        case 4: //MUL
		            *sp=*sp-1;
		            stack[*sp]=stack[*sp]*stack[*sp+1];
		            strcpy(str, "MUL");
		        	break;

		        case 5: //DIV
		            *sp=*sp-1;
		            stack[*sp]=stack[*sp]/stack[*sp+1];
		            strcpy(str, "DIV");
		        	break;

		        case 6: //ODD
		            stack[*sp]=stack[*sp]%2;
		            strcpy(str, "ODD");
		        	break;

		        case 7: //MOD
		            *sp=*sp-1;
		            stack[*sp]=stack[*sp]%stack[*sp+1];
		            strcpy(str, "MOD");
		         	break;

		        case 8: //EQL
		            *sp=*sp-1;
		            stack[*sp]=stack[*sp]==stack[*sp+1];
		            strcpy(str, "EQL");
		        	break;
		        case 9: //NEQ
		            *sp=*sp-1;
		            stack[*sp]=stack[*sp]!=stack[*sp+1];
		            strcpy(str, "NEQ");
		        	break;

		        case 10: //LSS
		            *sp=*sp-1;
		            stack[*sp]=stack[*sp]<stack[*sp+1];
		            strcpy(str, "LSS");
		        	break;

		        case 11: //LEQ
		            *sp=*sp-1;
		            stack[*sp]=stack[*sp]<=stack[*sp+1];
		            strcpy(str, "LEQ");
		        	break;

		        case 12: //GTR
		            *sp=*sp-1;
		            stack[*sp]=stack[*sp]>stack[*sp+1];
		            strcpy(str, "GTR");
		        	break;

		        case 13: //GEQ
		            *sp=*sp-1;
		            stack[*sp]=stack[*sp]>=stack[*sp+1];
		            strcpy(str, "GEQ");
		        	break;

		        default: //Error
		        	printf("\n\nERR: Unknown modifier %d\n\n",modifier);
			}
			break;

	    case 3: //LOD
	        *sp=*sp+1;
	        stack[*sp]=stack[base(level, *bp)+modifier];
	        // The level will be displayed in the output
	        *lcheck=1;
	        strcpy(str, "LOD");
			break;

	    case 4: //STO
	        stack[base(level,*bp)+modifier]=stack[*sp];
	        *sp=*sp-1;
	        // The level will be displayed in the output
	        *lcheck=1;
	        strcpy(str, "STO");
	    	break;

	    case 5: //CAL
	        stack[*sp+1]=0;
	        stack[*sp+2]=base(level,*bp);
	        stack[*sp+3]=*bp;
	        stack[*sp+4]=*pc;
	        *bp=*sp+1;
	        *pc=modifier;
	        // The level will be displayed in the output
	        *lcheck=1;
	        strcpy(str, "CAL");
	    	break;

	    case 6: //INC
	        *sp=*sp+modifier;
	        strcpy(str, "INC");
	    	break;

	    case 7: //JMP
	        *pc=modifier;
	        strcpy(str, "JMP");
	    	break;

	    case 8: //JPC
	        if(stack[*sp]==0)
	            *pc=modifier;
	        *sp=*sp-1;
	        strcpy(str, "JPC");
	    	break;

	    case 9: //SIO
	        // The modifier will not be displayed in the output
	        *mcheck=0;

	        switch(modifier){
		        case 0: //OUT
		            // A value will be printed
		            *outcheck=1;
		            *out=stack[*sp];
		            *sp=*sp-1;
		            strcpy(str, "OUT");
		        	break;

		        case 1: //INP
		            *sp=*sp+1;
		            scanf("%d", &stack[*sp]);
		            *inpcheck=1;
		            *in=stack[*sp];
		            strcpy(str, "INP");
		        	break;

		        case 2: //HLT
		            *hlt=1;
		            strcpy(str, "HLT");
		        	break;
		        default: //Error
		        	printf("\n\nERR: Unknown modifier %d\n\n",modifier);
	    	}
	        break;

	    default: //Error
	    	printf("\n\nERR: Unknown opcode %d\n\n",opcode);
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
