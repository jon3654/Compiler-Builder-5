#include <stdlib.h>
#include "tokens.h" // Functions in file know value of tokens and can use get_token()
#include "parser.h"

void parser(FILE* ifp){

}


// Inserts into the symbol table
void enter(){

}

// Looks up previously entered symbol
int lookup(){

}

// main parser functions
void program(FILE* ifp, tok_prop *properties){
    token_type token = get_token(ifp, properties);
    block(ifp, properties, &token);
    if(token != periodsym) error(9);
    else printf("\nNo errors, program is syntactically correct");
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

            *token = get_token(ifp, properties);
        } while(*token == commasym);
        if(*token != semicolonsym) error(5);
            *token = get_token(ifp, properties);
    }

    if(*token == varsym){
        do{
            *token = get_token(ifp, properties);
            if(*token != identsym) error(4);

            *token = get_token(ifp, properties);
        }while(*token == commasym);
        if(*token != semicolonsym) error(5);
            *token = get_token(ifp, properties);
    }

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
    if(*token == identsym){
        *token = get_token(ifp, properties);
        if (*token != becomessym) error(13);

        *token = get_token(ifp, properties);
        expression(ifp, properties, token);
    }
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
        if(*token != thensym) error(16);
        *token = get_token(ifp, properties);
        statement(ifp, properties, token);
    }
    else if(*token == whilesym){
        *token = get_token(ifp, properties);
        condition(ifp, properties, token);
        if(*token != dosym) error(18);
        *token = get_token(ifp, properties);
        statement(ifp, properties, token);
    }
    else if(*token == readsym){
        *token = get_token(ifp, properties);
        if(*token != identsym) error(4);
        *token = get_token(ifp, properties);
    }
    else if(*token == writesym){
        *token = get_token(ifp, properties);
        if(*token != identsym) error(4);
        *token = get_token(ifp, properties);
    }
}

void condition(FILE* ifp, tok_prop *properties, token_type *token){
    if(*token == oddsym){
        *token = get_token(ifp, properties);
        expression(ifp, properties, token);
    }
    else{
        expression(ifp, properties, token);
        if(rel_op(*token) == 0) error(20);
        *token = get_token(ifp, properties);
        expression(ifp, properties, token);
    }
}

void expression(FILE* ifp, tok_prop *properties, token_type *token){
    if(*token == plussym || *token == minussym)
        *token = get_token(ifp, properties);
    term(ifp, properties, token);
    while(*token == plussym || *token == minussym){
        *token = get_token(ifp, properties);
        term(ifp, properties, token);
    }
}

void term(FILE* ifp, tok_prop *properties, token_type *token){
    factor(ifp, properties, token);
    while(*token == multsym || *token == slashsym)
    {
        *token = get_token(ifp, properties);
        factor(ifp, properties, token);
    }
}

void factor(FILE* ifp, tok_prop *properties, token_type *token){
    if(*token == identsym)
        *token = get_token(ifp, properties);
    else if(*token == numbersym)
        *token = get_token(ifp, properties);
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
    if(token == eqlsym || token == neqsym || token == lessym || token == leqsym || token == gtrsym || token == geqsym)
        return 1;
    else return 0;
}


void error(int num){
    switch (num)
    {
    case 1:
        printf("\nError number 1, use = instead of :=");
        break;
    case 2:
        printf("\nError number 2, = must be followed by a number");
        break;
    case 3:
        printf("\nError number 3, identifier must be followed by =");
        break;
    case 4:
        printf("\nError number 4, const, var, procedure must be followed by identifier");
        break;
    case 5:
        printf("\nError number 5, semicolon or comma missing");
        break;
    case 6:
        printf("\nError number 6, incorrect symbol after procedure declaration");
        break;
    case 7:
        printf("\nError number 7, statement expected");
        break;
    case 8:
        printf("\nError number 8, incorrect symbol after statement part in block");
        break;
    case 9:
        printf("\nError number 9, period expected");
        break;
    case 10:
        printf("\nError number 10, semicolon between statements missing");
        break;
    case 11:
        printf("\nError number 11, undeclared identifier");
        break;
    case 12:
        printf("\nError number 12, assignment to constant or procedure is not allowed");
        break;
    case 13:
        printf("\nError number 13, assignment operator expected");
        break;
    case 14:
        printf("\nError number 14, call must be followed by an identifier");
        break;
    case 15:
        printf("\nError number 15, call of a constant or variable is meaningless");
        break;
    case 16:
        printf("\nError number 16, then expected");
        break;
    case 17:
        printf("\nError number 17, semicolon or } expected");
        break;
    case 18:
        printf("\nError number 18, do expected");
        break;
    case 19:
        printf("\nError number 19, incorrect symbol following statement");
        break;
    case 20:
        printf("\nError number 20, relational operator expected");
        break;
    case 21:
        printf("\nError number 21, expression must not contain a procedure identifier");
        break;
    case 22:
        printf("\nError number 22, right parenthesis missing");
        break;
    case 23:
        printf("\nError number 23, the preceding factor cannot begin with this symbol");
        break;
    case 24:
        printf("\nError number 24, an expression cannot begin with this symbol");
        break;
    case 25:
        printf("\nError number 25, this number is too large");
        break;
    case 26:
        printf("\nError number 26, lexing error: unidentified token");
        break;
    case 27:
        printf("\nError number 27, lexing error: invalid alphanumeric combination");
        break;
    case 28:
        printf("\nError number 28, lexing error: colon must be followed by =");
        break;
    case 29:
        printf("\nError number 29, lexing error: identifier longer than 12 characters detected");
        break;
    }
    exit(num);
}




