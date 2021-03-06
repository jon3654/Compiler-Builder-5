#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "tokens.h"
#include "generator.h"
#include "symbol.h"
#include "vm.h"
int main(int argc, char* argv[]){
    // Open the input/output file
    FILE* ifp = fopen(argv[1], "r");
    FILE* ofp = fopen(argv[2], "w");

    if(ifp == NULL) printf("Error: File not found./n");
    // Create a structure that stores the token properties
    tok_prop properties;

    // Initialize counter to 0
    cx=0;

    init_array();
    // Parse the input
    program(ifp, &properties);

    // Generate intermediate code
    generate(ofp);
    fclose(ofp);
    if(argc > 3 && strcmp(argv[3], "--st") == 0)
        vm(argv[2]);
    fclose(ifp);
    return 0;
}
