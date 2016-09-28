#include <stdio.h>
#include <string.h>
#include <ctype.h>

void PrintLines(int input);
void PrintTokens(char *ident, int *counter);

int main(int argc, char* argv[]){
	FILE *ifp = fopen(argv[1],"r");
	char temp[13], current;
	int i, counter=0, comment, halt=0;

	memset(temp, '\0', 12);

    // Scan the first character of the first temporary array
    fscanf(ifp, "%c", &current);
	//Scans in each character and builds the temporary array before sending to PrintTokens
	while(!feof(ifp)){
            // Check to see if the current character is a character other than a letter or number
            if(!isalpha(current) && !isdigit(current))
            {
                switch(current)
                {
                    case '+':
                        // Print the token for the previous string
                        PrintTokens(temp, &counter);
                        // Start the new array with the current character
                        temp[0]=current;
                        // Increment the counter
                        counter++;
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
                        // Increment the counter
                        counter++;
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
                        // Increment the counter
                        counter++;
                        // Scan a new character
                        fscanf(ifp, "%c", &current);
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
                            // Indicate that a comment has been detected
                            comment=1;
                            // Find the end of the comment
                            while(comment)
                            {
                                // Search for the end of the comment
                                fscanf(ifp, "%c", &current);
                                if(feof(ifp))
                                {
                                    comment=0;
                                }
                                if(current=='*')
                                {
                                    // Search for the end of the comment
                                    fscanf(ifp, "%c", &current);
                                    if(feof(ifp))
                                    {
                                        comment=0;
                                    }
                                    if(current=='/')
                                    {
                                        // The end of the comment has been found
                                        comment=0;
                                        // Scan a new character
                                        fscanf(ifp, "%c", &current);
                                    }
                                }
                            }
                        }
                        else
                        {
                            // There is not a comment, / is sent to the array
                            temp[0]='/';
                            // Increment the counter
                            counter++;
                            // Print the token for /
                            PrintTokens(temp, &counter);
                        }
                        break;
                    case '=':
                        // Print the token for the previous string
                        PrintTokens(temp, &counter);
                        // Start the new array with the current character
                        temp[0]=current;
                        // Increment the counter
                        counter++;
                        // Scan a new character
                        fscanf(ifp, "%c", &current);
                        // Print the tokens
                        PrintTokens(temp, &counter);
                        break;
                    case '<':
                        // Print the token for the previous string
                        PrintTokens(temp, &counter);
                        // Start the new array with <
                        temp[0]=current;
                        // Increment counter
                        counter++;
                        // Scan a new character
                        fscanf(ifp, "%c", &current);
                        // Check if the following character can be part of a token with the < symbol
                        if(current=='>' || current=='=')
                        {
                            // Copy second character before sending to PrintTokens
                            temp[1]=current;
                            // Increment counter
                            counter++;
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
                        // Increment counter
                        counter++;
                        // Scan a new character
                        fscanf(ifp, "%c", &current);
                        // Check if the following character can part of a token with the > symbol
                        if(current=='=')
                        {
                            // Copy second character before sending to PrintTokens
                            temp[1]=current;
                            // Increment counter
                            counter++;
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
                        // Increment counter
                        counter++;
                        // Scan a new character
                        fscanf(ifp, "%c", &current);
                        // Check if the following character can be part of a token with the : symbol
                        if(current=='=')
                        {
                            // Copy second character before sending to PrintTokens
                            temp[1]=current;
                            // Increment counter
                            counter++;
                            // Scan a new character
                            fscanf(ifp, "%c", &current);
                        }
                        // Print the tokens
                        PrintTokens(temp, &counter);
                        break;
                    case ',':
                        // Print the token for the previous string
                        PrintTokens(temp, &counter);
                        // Start the new array with the current character
                        temp[0]=current;
                        // Increment the counter
                        counter++;
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
                        // Increment the counter
                        counter++;
                        // Scan a new character
                        fscanf(ifp, "%c", &current);
                        // Print the tokens
                        PrintTokens(temp, &counter);
                        break;
                    case '.':
                        // Print the token for the previous string
                        PrintTokens(temp, &counter);
                        // Start the new array with the current character
                        temp[0]=current;
                        // Increment the counter
                        counter++;
                        // Scan a new character
                        fscanf(ifp, "%c", &current);
                        // Print the tokens
                        PrintTokens(temp, &counter);
                        break;
                    case '(':
                        // Print the token for the previous string
                        PrintTokens(temp, &counter);
                        // Start the new array with the current character
                        temp[0]=current;
                        // Increment the counter
                        counter++;
                        // Scan a new character
                        fscanf(ifp, "%c", &current);
                        // Print the tokens
                        PrintTokens(temp, &counter);
                        break;
                    case ')':
                        // Print the token for the previous string
                        PrintTokens(temp, &counter);
                        // Start the new array with the current character
                        temp[0]=current;
                        // Increment the counter
                        counter++;
                        // Scan a new character
                        fscanf(ifp, "%c", &current);
                        // Print the tokens
                        PrintTokens(temp, &counter);
                        break;
                    default:
                        // Print the token for the previous string
                        PrintTokens(temp, &counter);
                        // Ignore the invisible character, scan a new character
                        fscanf(ifp, "%c", &current);
                        break;
                }
            }
            else
            {
                // Save the current letter/number to the current index of the array
                temp[counter]=current;
                // Increment the counter
                counter++;
                // Scan a new character
                fscanf(ifp, "%c", &current);
            }
	}
	// Print the remaining token
	PrintTokens(temp, &counter);

    // Close the file from reading
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
    *counter=0;
    // Reset all the values of the array to null
    memset(ident, '\0', 12);
}
