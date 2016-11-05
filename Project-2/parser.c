#include "tokens.h" // Functions in file know value of tokens and can use get_token()
#include "parser.h"

token_type token = malloc(sizeof(token));

void parser(FILE* ifp){

}


// Inserts into the symbol table
void enter(){

}

// Looks up previously entered symbol
int lookup(){

}

// main parser functions
void program(){
    token = get_token();
    block();
    if(token != periodsym) error(9);
}

void block(){
    if(token == constsym){
       do{
            token = get_token();
            if(token != identsym) error(4);

            token = get_token();
            if(token != eqsym)
            {
                if(token == becomessym) error(1);
                else error(3);
            }

            token = get_token();
            if(token != numbersym) error(numbersym);

            token = get_token();
        } while(token == commasym);
    }

    if(token != semicolonsym) error(semicolonsym);
    token = get_token();

    if(token == varsym){
        do{
            token = get_token();
            if(token != identsym) error(4);

            token = get_token();
        }while(token == commasym);
    }

    if(token != semicolonsym) error();
    token = get_token();

    while(token == procsym){
        token = get_token();
        if(token != identsym) error(4);

        token = get_token();
        if(token != semicolonsym) error(semicolonsym);

        token = get_token();
        block();

        if(token != semicolonsym) error(semicolonsym);
        token = get_token();
    }
    statement();
}

void statement(){
    if(token == identsym){
        token = get_token();
        if (token != identsym) error(identsym);

        token = get_token();
        expression();
    }
    else if(token == callsym){
        token = get_token();
        if(token != callsym) error(callsym);

        token = get_token();
    }
    else if(token == beginsym){
        token = get_token();
        statement();
        while(token == semicolonsym){
            token = get_token();
            statement();
        }
        if (token != endsym) error(endsym);

        token = get_token();
    }
    else if(token == ifsym){
        token = get_token();
        condition();
        if(token != thensym) error(thensym);
        token = get_token();
        statement();
    }
    else if(token == whilesym){
        token = get_token();
        condition();
        if(token != dosym) error(dosym);
        token = get_token();
        statement();
    }
}

void condition(){
    if(token == oddsym){
        token = get_token();
        expression();
    }
    else{
        expression();
        if(rel_op(token) == 0) error(34);
        token = get_token();
        expression();
    }
}

void expression(){
    if(token == plussym || token == minussym)
        token = get_token();
    term();
    while(token == plussym || token == minussym){
        token = get_token();
        term();
    }
}

void term(){
    factor();
    while(token == plussym || token == slashsym){
        token = get_token();
        factor();
    }
}

void factor(){
    if(token == identsym)
        token = get_token();
    else if(token == numbersym)
        token = get_token();
    else if(token == lparentsym){
        token = get_token();
        expression();
        if(token != rparentsym) error(rparentsym);
        token = get_token();
    }
    else error();
}

// returns 1 if relationship operator, 0 otherwise
int rel_op(int token){
    if(token != eqlsym || token != neqsym || token != lessym || token != leqsym || token != gtrsym || token != geqsym)
        return 0;
    else return 1;
}


void error(int num){
    switch (token)
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
        pintf("\nError number 6, incorrect symbol after procedure declaration");
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
    }
}




