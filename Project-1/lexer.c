#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void PrintLines(int commentsIncluded, FILE *ifp);
void PrintTokens(FILE *ifp);

typedef enum token {nulsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5, multsym = 6, slashsym = 7, oddsym = 8,
    eqlsym = 9, neqsym = 10, lessym = 11, leqsym = 12,
    gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17, semicolonsym = 18, periodsym = 19,
    becomessym = 20, beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26, callsym = 27,
    constsym = 28, varsym = 29, procsym = 30, writesym = 31, readsym = 32, elsesym = 33} token_type;

int main(int argc, char* argv[]){
    FILE *ifp = fopen(argv[1],"r");
    int i;
    
    //Checks for --source or --clean command arguments for printing
    if(argv[2] != NULL){
        for(i = 2; i < argc; i++){
            if(strcmp(argv[i],"--source")==0)
            {
                // Print with comments
                PrintLines(1, ifp);
                rewind(ifp);
            }
            if(strcmp(argv[i],"--clean")==0)
            {
                // Print without comments
                PrintLines(0, ifp);
                rewind(ifp);
            }
        }
    }
    
    PrintTokens(ifp);
    // Close the file from reading
    fclose(ifp);
    
    return 0;
}


// Prints output if --source or --clean are given as command arguments
//if commentsIncluded = 1, print comments. If 0, don't.
void PrintLines(int commentsIncluded, FILE *ifp){
    // Declare variables
    char current;
    int halt;
    
    // Header for printing without comments
    if(commentsIncluded==0)
    {
        printf("\nsource code without comments:\n");
        printf("-----------------------------\n");
    }
    // Header for printing with comments
    else
    {
        printf("\nsource code:\n");
        printf("------------\n");
    }
    
    // Scan new characters until the end of the file
    while(fscanf(ifp, "%c", &current)!=EOF)
    {
        // Check for a potential comment
        if(current=='/' && commentsIncluded==0)
        {
            // Read another character
            fscanf(ifp, "%c", &current);
            // Confirm whether or not a comment has been found
            if(current=='*')
            {
                // Replace initial two comment characters with two spaces
                printf("  ");
                // Set halt to 0 until end of comment
                halt=0;
                // Find the end of the comment
                while(!halt)
                {
                    fscanf(ifp, "%c", &current);
                    // Replace comment characters with spaces
                    printf(" ");
                    // Check for potential end of comment
                    if(current=='*')
                    {
                        fscanf(ifp, "%c", &current);
                        // Replace comment characters with spaces
                        printf(" ");
                        // Check for end of comment
                        if(current=='/')
                        {
                            // End of comment found
                            halt=1;
                        }
                    }
                }
            }
            // Not a comment, print the two characters
            else
            {
                printf("/");
                printf("%c", current);
            }
        }
        // Not a comment, print the character
        else
        {
            printf("%c", current);
        }
    }
    // Line break
    printf("\n");
}


// Reads in each token and prints the values
// Should consist of an obnoxiously large switch statement to handle the tokens
void PrintTokens(FILE *ifp)
{
    char string[13]; // stores variable names and reserved words for strcmp
    char current; // stores fgetc returned char
    int found = 0; // used for finding end of comment
    int no_scan = 0; // used to prevent skipping over non-whitespace ex. ">4"
    int counter = 0; // keeps track of array length
    int reserved = 0;
    int i = 0;
    int num;
    
    
    // memset(string, '\0', 12);
    for(i = 0; i < 12; i++)
        string[i] = '\0';

    while(!feof(ifp)){

	// prevents skipping over valid token if scanned for multiple character token during switch statement
	if(no_scan == 0)
	    current = fgetc(ifp);
	// reinitialize no_scan to 0
	else
	    no_scan = 0;
	// reinitialize found to 0
	found = 0;

	// filters out white space from the rest of the if-statements
	if(!isspace(current))
	{
	    // Check to see if the current character is a character other than a letter or number
	    if(!isalpha(current) && !isdigit(current))
	    {
		switch(current)
	        {
		    // possible comment case
		    case '/':
				current = fgetc(ifp);
	
				// if comment loops until the end of the comment
				if(current == '*')
				{
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
					 	}
				     }
				}
	
				// else print slashsym
				else
				{
				    printf("/\t%d\n", slashsym);
				    no_scan = 1;
				}
				break;
				
		    // various single char operator and special symbol cases
		    case '*':
				printf("*\t%d\n", slashsym);
				break;
		    case '+':
		        printf("+\t%d\n", plussym);
				break;
		    case '-':
				printf("-\t%d\n", minussym);
				break;
		    case '(':
				printf("(\t%d\n", lparentsym);
				break;
		    case ')':
				printf(")\t%d\n", rparentsym);
				break;
		    case ',':
				printf(",\t%d\n", commasym);
				break;
		    case '.':
		        printf(".\t%d\n", periodsym);
				break;
		    case ';':
				printf(";\t%d\n", semicolonsym);
				break;
		    case '=':
				printf("=\t%d\n", eqlsym);
				break;
		    case '<':
				// check next char
				current = fgetc(ifp);
				if(current == '=')
			    	printf("<=\t%d\n", leqsym);
				else if(current == '>')
			    	printf("<>\t%d\n", neqsym);
				else
				{
			    	printf("<\t%d\n", lessym);
				}
				break;
		    case '>':
				if(current == '=')
				    printf(">=\t%d\n", geqsym);
				else
				{
				    printf(">\t%d\n", gtrsym);
			    	no_scan = 1;
				}	
				break;

		    // possible becomessym case
		    // error here if no '=' ?
		    case ':':
				// scan for next char
		        current = fgetc(ifp);
				// check for becomessym case, print symbol and associated int if found
				if(current == '=')
				    printf(":=\t%d\n", becomessym);
				else
			    	no_scan = 1;
				break;
			default:				
				continue;
		}
	    }

	    // likely variable or reserved word case
	    if(isalpha(current))
	    {
            // scans for reserved words or variables
	        while(found == 0 && counter < 13)
            {
                string[counter] = current;
                counter++;
                current = fgetc(ifp);

                if(isdigit(current))
                    reserved = 1;

                if(isspace(current))
                    found = 1;

               else if(!isalpha(current) && !isdigit(current))
                {
                	if(!isspace(current) && (current != ',') && (current != ';') && (current != '.') && (current != ')') && (current != '(') && (current != '+') && (current != '-') && (current != '*') && (current != '/') && (current != '=') && (current != ':') && (current != '>') && (current != '<')){
                    	printf("\nERR: Unidentified Token %s",string);
                    	return;
                	}
                	
                    found = 1;
                    no_scan = 1;
                }
            }
            
            // print reserved words or variable here
	        if(reserved == 1 || counter < 2 || (counter > 9 && counter < 12))
                printf("%s\t%d\n", string, identsym);
            // test string for reserved words
            else if(reserved == 0)
            {
                if(counter < 3)
                {
                    // test for if, do
                    if(strcmp(string,"if") == 0)
                        printf("if\t%d", ifsym);
                        
                    else if(strcmp(string,"do") == 0)
                        printf("do\t%d", dosym);
                        
                    else
                        printf("%s\t%d\n", string, identsym);
                }
                else if(counter < 4)
                {
                    // test for var, end, call, odd
                    if(strcmp(string, "var") == 0)
                        printf("var\t%d\n", varsym);
                        
                    else if(strcmp(string, "end") == 0)
                        printf("end\t%d\n", endsym);
                        
                    else
                        printf("%s\t%d\n", string, identsym);
                }
                else if(counter < 5)
                {
                    // test for then, else, read, call
                    if(strcmp(string, "then") == 0)
                        printf("then\t%d\n", thensym);
                        
                    else if(strcmp(string, "else") == 0)
                        printf("else\t%d\n", elsesym);
                        
                    else if(strcmp(string, "read") == 0)
                        printf("read\t%d\n", readsym);
                        
                    else if(strcmp(string, "call") == 0)
                        printf("call\t%d\n", callsym);
                        
                    else
                        printf("%s\t%d\n", string, identsym);
                }
                else if(counter < 6)
                {
                // test for const begin while write
                    if(strcmp(string, "const") == 0)
                        printf("const\t%d\n", constsym);
                        
                    else if(strcmp(string, "begin") == 0)
                        printf("begin\t%d\n", beginsym);
                        
                    else if(strcmp(string, "while") == 0)
                        printf("while\t%d\n", whilesym);
                        
                    else if(strcmp(string, "write") == 0)
                        printf("write\t%d\n", writesym);
                        
                    else
                        printf("%s\t%d\n", string, identsym);
                }
                
                // test string for procedure
                else if(strcmp(string, "procedure") == 0)
                    printf("procedure\t%d\n", procsym);
		    
	       //Throw error if identifier longer than 12 characters
		else if(counter > 11)
		{
			printf("\nERR: Identifier longer than 12 characters detected\n");
			return;
		}
                    
                // else it's a reserved word
                else
                    printf("%s\t%d\n", string, identsym);
            }
            
            else
                printf("%s\t%d\n", string, identsym);

            // reinitialize string & counter
            for(i = 0; i < 12; i++)
                string[i] = '\0';
            counter = 0;
            reserved = 0;
	    }
	    
	    // scans in and prints integers
	    // should print error if alphabetical char comes right after an integer char
	    if(isdigit(current))
		{
			while(found == 0 && counter < 6)
			{
			    string[counter] = current;
			    counter++;
			    current = fgetc(ifp);
			    if(!isdigit(current))
			    {
					if(isalpha(current))
					{
					    // alpha-num error handling
					    printf("\nERR: Invalid alphanumeric combination\n");
					    return;
					}
				else if(!isspace(counter))
				    no_scan = 1;
				found = 1;
			    }
			}
			num = atoi(string);
			
			if(num > 65535){
				printf("\nERR: Integer Value larger than 65,535 detected\n");
				return;
			}
	        printf("%d\t%d\n", num, numbersym);

			// reinitialize string & counter
			for(i = 0; i < 12; i++)
			    string[i] = '\0';
			counter = 0;
	    }
	}
    }
}
