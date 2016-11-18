#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include "tokens.h"

// main parser function prototypes
void program(FILE* ifp, tok_prop *properties);
void block(FILE* ifp, tok_prop *properties, token_type *token);
void const_decl(FILE* ifp, tok_prop *properties, token_type *token);
void var_dec(FILE* ifp, tok_prop *properties, token_type *token);
void statement(FILE* ifp, tok_prop *properties, token_type *token);
void condition(FILE* ifp, tok_prop *properties, token_type *token);
int rel_op(token_type token);
void expression(FILE* ifp, tok_prop *properties, token_type *token);
void term(FILE* ifp, tok_prop *properties, token_type *token);
void factor(FILE* ifp, tok_prop *properties, token_type *token);
void error(int num);
void number();
void ident();
void digit();
void letter();


#endif // PARSER_H_INCLUDED
