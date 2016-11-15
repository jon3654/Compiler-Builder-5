#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "tokens.h" // Functions in file know value of tokens
#include "parser.h"
#include "generator.h"
#include "symbol.h"

// Will get the next token
token_type get_token(FILE* ifp, tok_prop *properties){
    char current;
    char word[12];
    char temp;
    int found;
    int num;
    int i;
    // Check for end of file
    if(feof(ifp))
    {
        return nulsym;
    }
    current=fgetc(ifp);

    // Skip white space
    while(current == ' ' || current == '\n' || current == '\t')
    {
        current=fgetc(ifp);
        // Check for end of file
        if(feof(ifp))
        {
            return nulsym;
        }
    }

    // Check if the first character is a letter, if so it is either an identifier or reserved word
    if(isalpha(current))
    {
        i=0;
        while(current != EOF && isalnum(current))
        {
            word[i]=current;
            i++;
            current=fgetc(ifp);
        }
        // Add a null character to the end
        word[i]='\0';
        // Allow the extra character to be read later
        ungetc(current, ifp);
        if(i>12)
        {
            error(29);
        }
        // Check if the word is a reserved word
        if(strcmp(word, "begin") == 0)
        {
            return beginsym;
        }
        else if(strcmp(word, "call") == 0)
        {
            return callsym;
        }
        else if(strcmp(word, "const") == 0)
        {
            return constsym;
        }
        else if(strcmp(word, "do") == 0)
        {
            return dosym;
        }
        else if(strcmp(word, "end") == 0)
        {
            return endsym;
        }
        else if(strcmp(word, "if") == 0)
        {
            return ifsym;
        }
        else if(strcmp(word, "odd") == 0)
        {
            return oddsym;
        }
        else if(strcmp(word, "procedure") == 0)
        {
            return procsym;
        }
        else if(strcmp(word, "then") == 0)
        {
            return thensym;
        }
        else if(strcmp(word, "var") == 0)
        {
            return varsym;
        }
        else if(strcmp(word, "while") == 0)
        {
            return whilesym;
        }
        else if(strcmp(word, "write") == 0)
        {
            return writesym;
        }
        else if(strcmp(word, "read") == 0)
        {
            return readsym;
        }
        else if(strcmp(word, "else") == 0)
        {
            return elsesym;
        }
        // Otherwise save the word temporarily before returning
        strcpy(properties->id, word);
        return identsym;
    }

    // Check if the first character is a number, if so it must be a number or an error has occurred
    if(isdigit(current))
    {
        temp=current;
        current=fgetc(ifp);
        if(isalpha(current))
        {
            error(27);
        }
        // Unread the two characters and then read the entire number
        ungetc(current, ifp);
        ungetc(temp, ifp);
        fscanf(ifp, "%d", &num);
        if(num>65535)
        {
            error(25);
            return nulsym;
        }
        // Save the number before returning
        properties->val=num;
        return numbersym;
    }

    switch (current)
    {
    case '+':
        return plussym;
        break;
    case '-':
        return minussym;
        break;
    case '*':
        return multsym;
        break;
    case '/':
        // Check for comment
        current=fgetc(ifp);
        if(current == '*')
        {
            fgetc(ifp);
            // Indicate the end of the comment has not been reached
            found=0;
            while(found == 0)
            {
                current = fgetc(ifp);
                // possible end of comment
                if(current == '*')
                {
                    current = fgetc(ifp);
                    // if "/", end of comment found
                    if(current == '/')
                    found = 1;
                    return get_token(ifp, properties);
                }
            }
        }
        else
        {
            ungetc(current, ifp);
            return slashsym;
        }
        break;
    case '(':
        return lparentsym;
        break;
    case ')':
        return rparentsym;
        break;
    case ':':
        // Check for equal sign
        current=fgetc(ifp);
        if(current == '=')
        {
            return becomessym;
        }
        else
        {
            error(28);
        }
        break;
    case '=':
        return eqlsym;
        break;
    case '<':
        // Check for > or =
        current=fgetc(ifp);
        if(current == '>')
        {
            return neqsym;
        }
        else if(current == '=')
        {
            return leqsym;
        }
        else
        {
            // Allow the extra character to be read later
            ungetc(current, ifp);
            return lessym;
        }
        break;
    case '>':
        // Check for =
        current=fgetc(ifp);
        if(current == '=')
        {
            return geqsym;
        }
        else
        {
            // Allow the extra character to be read later
            ungetc(current, ifp);
            return gtrsym;
        }
        break;
    case ',':
        return commasym;
        break;
    case ';':
        return semicolonsym;
        break;
    case '.':
        return periodsym;
        break;
    default:
        error(26);
        break;
    }
    return nulsym;
}
