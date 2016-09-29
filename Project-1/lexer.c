#include <stdio.h>
#include <string.h>
#include <ctype.h>

void PrintLines(int commentsIncluded, FILE *ifp);
void PrintTokens(FILE *ifp);

typedef enum token {nulsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5, multsym = 6, slashsym = 7, oddsym = 8,
eqlsym = 9, neqsym = 10, lessym = 11, leqsym = 12,
gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17, semicolonsym = 18, periodsym = 19,
becomessym = 20, beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26, callsym = 27,
		    constsym = 28, varsym = 29, procsym = 30, writesym = 31, readsym = 32, elsesym = 33} token_type;

int main(int argc, char* argv[]){
	FILE *ifp = fopen(argv[1],"r");
	char current;
	int i, counter=0, comment, halt=0;

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
    char current; // stores fgetc returned char
    int found = 0; // used for finding end of comment

    while(!feof(ifp)){

	current = fgetc(ifp);

        // Check to see if the current character is a character other than a letter or number or whitespace/tab/newline
        if(!isalpha(current) && !isdigit(current) && !isspace(current))
        {
            switch(current)
            {
		// possible comment case
	        case '/':
		{
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
			// reinitialize found to 0
			found = 0;
		    }

		    // else print slashsym
		    else
			printf("/\t%d", slashsym);
		}

		// possible becomessym case
	        case ':':
	        {
		    // scan for next char
	            current = fgetc(ifp);

		    // check for becomessym case, print symbol and associated int if found
		    if(current == '=')
			printf(":=\t%d\n", becomessym);
	        }
            }
        }
    }

}
