#include <stdio.h>
#include <string.h>
#include <ctype.h>

void PrintLines(int input);
void PrintTokens(char *ident, int *counter);

int main(int argc, char* argv[]){
	FILE *ifp = fopen(argv[1],"r");
	char temp[13], current;
	int i, counter=0, halt;

	//Checks for --source or --clean command arguments for printing
	if(argv[2] != NULL){
		for(i = 2; i < argc; i++){

			if(strcmp(argv[i],"--source"))
				PrintLines(0);
			if(strcmp(argv[i],"--clean"))
				PrintLines(1);
		}
	}

    memset(temp, '\0', 12);

    // Scan the first character of the first temporary array
    fscanf(ifp, "%c", &current);
	while(!feof(ifp)){
            // Check to see if the current character is a character other than a letter or number
            if(!isalpha(current) && !isdigit(current))
            {
                switch(current)
                {
                    case '<':
                        // Print the token for the previous string
                        PrintTokens(temp, &counter);

                        // Start the new array with <
                        temp[0]=current;
                        // Scan a new character
                        fscanf(ifp, "%c", &current);
                        // Check if the following character can be part of a token with the < symbol
                        if(current=='>' || current=='=')
                        {
                            // Copy second character before sending to PrintTokens
                            temp[1]=current;
                            // Scan a new character
                            fscanf(ifp, "%c", &current);
                        }
                        // Print the token
                        PrintTokens(temp, &counter);
                        break;
                    case '>':
                        // Print the token for the previous string
                        PrintTokens(temp, &counter);

                        // Start the new array with >
                        temp[0]=current;
                        // Scan a new character
                        fscanf(ifp, "%c", &current);
                        // Check if the following character can part of a token with the > symbol
                        if(current=='=')
                        {
                            // Copy second character before sending to PrintTokens
                            temp[1]=current;
                            // Scan a new character
                            fscanf(ifp, "%c", &current);
                        }
                        // Print the token
                        PrintTokens(temp, &counter);
                        break;
                    case ':':
                        // Print the token for the previous string
                        PrintTokens(temp, &counter);

                        // Start the new array with :
                        temp[0]=current;
                        // Scan a new character
                        fscanf(ifp, "%c", &current);
                        // Check if the following character can be part of a token with the : symbol
                        if(current=='=')
                        {
                            // Copy second character before sending to PrintTokens
                            temp[1]=current;
                            // Scan a new character
                            fscanf(ifp, "%c", &current);
                        }
                        // Print the tokens
                        PrintTokens(temp, &counter);
                        break;
                    case '/':
                        // Print the token for the previous string
                        PrintTokens(temp, &counter);

                        // Scan a new character
                        fscanf(ifp, "%c", &current);
                        // Check to see if a comment has been found
                        if(current=='*')
                        {
                            halt==0;
                            while(halt==0)
                            {
                                fscanf(ifp, "%c", &current);
                                if(current=='*')
                                {
                                    fscanf(ifp, "%c", &current);
                                    if(current=='/')
                                    {
                                        halt=1;
                                        fscanf(ifp, "%c", &current);
                                    }
                                }
                            }
                        }
                        else
                        {
                            temp[0]='/';
                            PrintTokens(temp, &counter);
                        }
                    case '+':
                        // Print the token for the previous string
                        PrintTokens(temp, &counter);

                        // Start the new array with the current character
                        temp[0]=current;
                        // Scan a new character
                        fscanf(ifp, "%c", &current);
                        // Print the tokens
                        PrintTokens(temp, &counter);
                        break;
                    case '-':
                        // Print the token for the previous string
                        PrintTokens(temp, &counter);

                        // Start the new array with the current character
                        temp[0]=current;
                        // Scan a new character
                        fscanf(ifp, "%c", &current);
                        // Print the tokens
                        PrintTokens(temp, &counter);
                        break;
                    case '*':
                        // Print the token for the previous string
                        PrintTokens(temp, &counter);

                        // Start the new array with the current character
                        temp[0]=current;
                        // Scan a new character
                        fscanf(ifp, "%c", &current);
                        // Print the tokens
                        PrintTokens(temp, &counter);
                        break;
                    case '=':
                        // Print the token for the previous string
                        PrintTokens(temp, &counter);

                        // Start the new array with the current character
                        temp[0]=current;
                        // Scan a new character
                        fscanf(ifp, "%c", &current);
                        // Print the tokens
                        PrintTokens(temp, &counter);
                        break;
                    case ';':
                        // Print the token for the previous string
                        PrintTokens(temp, &counter);

                        // Start the new array with the current character
                        temp[0]=current;
                        // Scan a new character
                        fscanf(ifp, "%c", &current);
                        // Print the tokens
                        PrintTokens(temp, &counter);
                        break;
                    default:
                        // Print the token for the previous string
                        PrintTokens(temp, &counter);
                        // Ignore the space, scan a new character
                        fscanf(ifp, "%c", &current);
                        break;
                }
            }
            else
            {
                temp[counter]=current;
                fscanf(ifp, "%c", &current);
                counter++;
            }
	}
	temp[counter]=current;
	PrintTokens(temp, &counter);



	// Close the file
	fclose(ifp);

	return 0;
}


// Prints output if --source or --clean are given as command arguments
//if commentsIncluded = 1, print comments. If 0, don't.
void PrintLines(int commentsIncluded){

}


// Reads in each token and prints the values
// Should consist of an obnoxiously large switch statement to handle the tokens
void PrintTokens(char *ident, int *counter){
    // Make sure the string isn't null
    if(ident[0]=='\0')
    {
        return;
    }


    // Reset the counter to 0
    counter=0;
    // Reset all the values of the array to null
    memset(ident, '\0', 12);
}
