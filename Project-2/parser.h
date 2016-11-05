#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

void parser(FILE* ifp);
void enter();
void lookup();
void error(int token);

// main parser function prototypes
void program();
void block();
void const_decl();
void var_dec();
void statement();
void condition();
int rel_op(int token);
void expression();
void term();
void factor();
void number();
void ident();
void digit();
void letter();


#endif // PARSER_H_INCLUDED
