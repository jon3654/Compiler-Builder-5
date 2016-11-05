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
    if(token.val != periodsym) error(periodsym);
}

void block(){
    if(token.val == constsym){
        while(token == commasym){
            token = get_token();
            if(token.val != identsym) error(identsym);
        
            token = get_token();
            if(token.val != eqsym) error(eqsym);
        
            token = get_token();
            if(token.val != numbersym) error(numbersym);
        
            token = get_token();
        }
    }
    
    if(token.val != semicolonsym) error(semicolonsym);
    token = get_token();
    
    if(token.val == varsym){
        while(token.val == commasym){
            token = get_token();
            if(token.val != identsym) error(identsym);
            
            token = get_token();
        }
    }
    
    if(token.val != semicolonsym) error();
    token = get_token();
    
    while(token.val == procsym){
        token = get_token();
        if(token != identsym) error(identsym);
        
        token = get_token();
        if(token.val != semicolonsym) error(semicolonsym);
        
        token = get_token();
        block();
        
        if(token.val != semicolonsym) error(semicolonsym);
        token = get_token();
    }
    statement();
}

void statement(){
    if(token.val == identsym){
        token = get_token();
        if (token.val != identsym) error(identsym);
        
        token = get_token();
        expression();
    }
    else if(token.val == callsym){
        token = get_token();
        if(token.val != callsym) error(callsym);
        
        token = get_token();
    }
    else if(token == beginsym){
        token = get_token();
        statement();
        while(token.val == semicolonsym){
            token = get_token();
            statement();
        }
        if (token.val != endsym) error(endsym);
        
        token = get_token();
    }
    else if(token.val == ifsym){
        token = get_token();
        condition();
        if(token.val != thensym) error(thensym);
        token = get_token();
        statement();
    }
    else if(token.val == whilesym){
        token = get_token();
        condition();
        if(token.val != dosym) error(dosym);
        token = get_token();
        statement();
    }
}

void condition(){
    if(token.val == oddsym){
        token = get_token();
        expression();
    }
    else{
        expression();
        if(rel_op(token.val) == 0) error(34);
        token = get_token();
        expression();
    }
}

void expression(){
    if(token.val == plussym || token.val == minussym)
        token = get_token();
    term();
    while(token.val == plussym || token.val == minussym){
        token = get_token();
        term();
    }
}

void term(){
    factor();
    while(token.val == plussym || token.val == slashsym){
        token = get_token();
        factor();
    }
}

void factor(){
    if(token.val == identsym)
        token = get_token();
    else if(token.val == numbersym)
        token = get_token();
    else if(token.val == lparentsym){
        token = get_token();
        expression();
        if(token.val != rparentsym) error(rparentsym);
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









