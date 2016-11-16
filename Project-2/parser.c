#include <stdlib.h>
#include <stdio.h>
#include "tokens.h" // Functions in file know value of tokens and can use get_token()
#include "parser.h"
#include "generator.h"
#include "symbol.h"
#include <string.h>

// main parser functions
void program(FILE* ifp, tok_prop *properties){
    token_type token = get_token(ifp, properties);
    block(ifp, properties, &token);
    if(token != periodsym) error(9);
    else {
        emit(SIO, 0, 2);
        printf("\nNo errors, program is syntactically correct\n");
    }
}

void block(FILE* ifp, tok_prop *properties, token_type *token){
    if(*token == constsym){
       do{
            *token = get_token(ifp, properties);
            if(*token != identsym) error(4);

            *token = get_token(ifp, properties);
            if(*token != eqlsym)
            {
                if(*token == becomessym) error(1);
                else error(3);
            }

            *token = get_token(ifp, properties);
            if(*token != numbersym) error(2);

            put_symbol(1, properties->id, properties->val, 0, 0);

            *token = get_token(ifp, properties);
        } while(*token == commasym);
        if(*token != semicolonsym) error(5);
            *token = get_token(ifp, properties);
    }
    int numvars = 0;
    if(*token == varsym){
        do{
            *token = get_token(ifp, properties);
            if(*token != identsym) error(4);

            numvars++;
            put_symbol(2, properties->id, 0, 0, 3 + numvars);

            *token = get_token(ifp, properties);
        }while(*token == commasym);

        if(*token != semicolonsym) error(5);

        *token = get_token(ifp, properties);

    }
    emit(INC, 0, 4+numvars);
    // we don't need procedures for tiny PL/0
    while(*token == procsym){
        *token = get_token(ifp, properties);
        if(*token != identsym) error(4);

        *token = get_token(ifp, properties);
        if(*token != semicolonsym) error(5);

        *token = get_token(ifp, properties);
        block(ifp, properties, token);

        if(*token != semicolonsym) error(5);
        *token = get_token(ifp, properties);
    }
    statement(ifp, properties, token);
}

void statement(FILE* ifp, tok_prop *properties, token_type *token){
    int ctemp; // Temporary counter for if
    int cx1; // First temporary counter for while
    int cx2; // Second temporary counter for while
    int index = 0; // keeps track of where in the symbol_table array a symbol is

    if(*token == identsym){
        *token = get_token(ifp, properties);
        index = getsymbol(properties->id);

        if(symbol_table[index].kind != 2) error(12); // Assignment to constant or procedure is not allowed

        if (*token != becomessym) error(13); // Assignment operator expected

        *token = get_token(ifp, properties);
        expression(ifp, properties, token);

        emit(STO, 0, symbol_table[index].modifier);
    }
    // no calls in Tiny PL/0
    else if(*token == callsym){
        *token = get_token(ifp, properties);
        if(*token != identsym) error(14);

        *token = get_token(ifp, properties);
    }

    else if(*token == beginsym){
        *token = get_token(ifp, properties);
        statement(ifp, properties, token);
        while(*token == semicolonsym)
        {
            *token = get_token(ifp, properties);
            statement(ifp, properties, token);
        }
        if(*token == identsym || *token == callsym || *token == beginsym || *token == ifsym || *token == whilesym) error(10); // Missing semicolon between statements
        if (*token != endsym) error(17); // Semicolon or } expected

        *token = get_token(ifp, properties);
    }

    else if(*token == ifsym){
        *token = get_token(ifp, properties);
        condition(ifp, properties, token);

        if(*token != thensym) error(16); // Then expected
        *token = get_token(ifp, properties);
        ctemp=cx; // Temporarily saves the code index
        emit(JPC, 0, 0);
        statement(ifp, properties, token);
        code[ctemp].m=cx; // Change JPC 0 0 to JPC 0 cx
    }

    else if(*token == whilesym){
        cx1=cx; // Temporarily saves first code index

        *token = get_token(ifp, properties);
        condition(ifp, properties, token);

        cx2=cx; // Temporarily saves second code index
        emit(JPC, 0, 0);
        if(*token != dosym) error(18); // Do expected
        *token = get_token(ifp, properties);

        statement(ifp, properties, token);
        emit(JMP, 0, cx1);
        code[cx2].m=cx; // JPC 0 0 to JPC 0 cx
    }

    else if(*token == readsym){
        emit(SIO, 0, 1);

        *token = get_token(ifp, properties);
        if(*token != identsym) error(4);

        emit(STO, 0, symbol_table[getsymbol(properties->id)].modifier);

        *token = get_token(ifp, properties);
    }

    else if(*token == writesym){
        *token = get_token(ifp, properties);

        if(*token != identsym) error(4);

        if(symbol_table[getsymbol(properties->id)].kind == 2)
            emit(LOD, 0, symbol_table[getsymbol(properties->id)].modifier);

        if(symbol_table[getsymbol(properties->id)].kind == 1)
            emit(LIT, 0, symbol_table[getsymbol(properties->id)].num);

        emit(SIO, 0, 0);
        *token = get_token(ifp, properties);
    }

	 else if(*token == elsesym){

        *token = get_token(ifp, properties);
        ctemp=cx; // Temporarily saves the code index
        emit(JPC, 0, 0);
        statement(ifp, properties, token);
        code[ctemp].m=cx; // Change JPC 0 0 to JPC 0 cx
    }
}

void condition(FILE* ifp, tok_prop *properties, token_type *token){
    if(*token == oddsym){
        *token = get_token(ifp, properties);
        expression(ifp, properties, token);
    }
    else{
        expression(ifp, properties, token);
        int tmp = rel_op(*token);
        if(tmp == 0) error(20);
        *token = get_token(ifp, properties);
        expression(ifp, properties, token);
        emit(OPR, 0, tmp);
    }
}

void expression(FILE* ifp, tok_prop *properties, token_type *token){
    token_type addop;
    if(*token == plussym || *token == minussym)
    {
        addop = *token;
        *token = get_token(ifp, properties);
        term(ifp, properties, token);
        if(addop == minussym)
        {
            emit(OPR, 0, NEG);
        }
    }
    else
    {
        term(ifp, properties, token);
    }
    while(*token == plussym || *token == minussym){
        addop = *token;
        *token = get_token(ifp, properties);
        term(ifp, properties, token);
        if(addop == plussym)
        {
            emit(OPR, 0, ADD);
        }
        else
        {
            emit(OPR, 0, SUB);
        }
    }
}

void term(FILE* ifp, tok_prop *properties, token_type *token){
    int mulop;
    factor(ifp, properties, token);
    while(*token == multsym || *token == slashsym)
    {
        mulop = *token;
        *token = get_token(ifp, properties);
        factor(ifp, properties, token);
        if(mulop == multsym)
        {
            emit(OPR, 0, MUL);
        }
        else
        {
            emit(OPR, 0, DIV);
        }
    }
}

void factor(FILE* ifp, tok_prop *properties, token_type *token){
    if(*token == identsym){
        emit(LOD, 0, symbol_table[getsymbol(properties->id)].modifier);
        *token = get_token(ifp, properties);
    }
    else if(*token == numbersym){
        *token = get_token(ifp, properties);
        emit(LIT, 0, properties->val);
    }
    else if(*token == lparentsym){
        *token = get_token(ifp, properties);

        expression(ifp, properties, token);
        if(*token != rparentsym) error(22);

        *token = get_token(ifp, properties);
    }
    else error(23);
}

// returns 1 if relationship operator, 0 otherwise
int rel_op(token_type token){
    if(token == eqlsym)
        return EQL;
    if(token == neqsym)
        return NEQ;
    if(token == lessym)
        return LSS;
    if(token == leqsym)
        return LEQ;
    if( token == gtrsym)
        return GTR;
    if(token == geqsym)
        return GEQ;
    else return 0;
}


void error(int num){
    switch (num)
    {
    case 1:
        printf("\nError number 1, use = instead of :=\n");
        break;
    case 2:
        printf("\nError number 2, = must be followed by a number\n");
        break;
    case 3:
        printf("\nError number 3, identifier must be followed by =\n");
        break;
    case 4:
        printf("\nError number 4, const, var, procedure must be followed by identifier\n");
        break;
    case 5:
        printf("\nError number 5, semicolon or comma missing\n");
        break;
    case 6:
        printf("\nError number 6, incorrect symbol after procedure declaration\n");
        break;
    case 7:
        printf("\nError number 7, statement expected\n");
        break;
    case 8:
        printf("\nError number 8, incorrect symbol after statement part in block\n");
        break;
    case 9:
        printf("\nError number 9, period expected\n");
        break;
    case 10:
        printf("\nError number 10, semicolon between statements missing\n");
        break;
    case 11:
        printf("\nError number 11, undeclared identifier\n");
        break;
    case 12:
        printf("\nError number 12, assignment to constant or procedure is not allowed\n");
        break;
    case 13:
        printf("\nError number 13, assignment operator expected\n");
        break;
    case 14:
        printf("\nError number 14, call must be followed by an identifier\n");
        break;
    case 15:
        printf("\nError number 15, call of a constant or variable is meaningless\n");
        break;
    case 16:
        printf("\nError number 16, then expected\n");
        break;
    case 17:
        printf("\nError number 17, semicolon or } expected\n");
        break;
    case 18:
        printf("\nError number 18, do expected\n");
        break;
    case 19:
        printf("\nError number 19, incorrect symbol following statement\n");
        break;
    case 20:
        printf("\nError number 20, relational operator expected\n");
        break;
    case 21:
        printf("\nError number 21, expression must not contain a procedure identifier\n");
        break;
    case 22:
        printf("\nError number 22, right parenthesis missing\n");
        break;
    case 23:
        printf("\nError number 23, the preceding factor cannot begin with this symbol\n");
        break;
    case 24:
        printf("\nError number 24, an expression cannot begin with this symbol\n");
        break;
    case 25:
        printf("\nError number 25, this number is too large\n");
        break;
    case 26:
        printf("\nError number 26, lexing error: unidentified token\n");
        break;
    case 27:
        printf("\nError number 27, lexing error: invalid alphanumeric combination\n");
        break;
    case 28:
        printf("\nError number 28, lexing error: colon must be followed by =\n");
        break;
    case 29:
        printf("\nError number 29, lexing error: identifier longer than 12 characters detected\n");
        break;
    case 30:
        printf("\nError number 30, code too long\n");
        break;
    }
    exit(num);
}




