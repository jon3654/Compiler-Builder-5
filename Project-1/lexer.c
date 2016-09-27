#include<stdio.h>

void PrintLines(int input);
int StringReader(char* ident);

int main(int argc, char* argv[]){
	FILE *ifp = fopen(arg[1],"r");
	char temp[13];
	int i;

	//Checks for --source or --clean command arguments for printing
	if(argv[2] != NULL){
		for(i = 2; i < argc; i++){
		
			if(strcmp(argv[i],"--source"))
				PrintLines(0);
			if(strcmp(argv[i],"--clean"))
				PrintLines(1);
		}
	}
	
	//Scans in each identifier and passes it to PrintTokens
	while(!feof(ifp)){
		temp = fscanf(ifp);
		PrintTokens(temp);
	}
	
	return 0;
}


// Prints output if --source or --clean are given as command arguments
//if commentsIncluded = 1, print comments. If 0, don't.
void PrintLines(int commentsIncluded){
	
}


// Reads in each token and prints the values
// Should consist of an obnoxiously large switch statement to handle the tokens
int PrintTokens(char* ident){

}
