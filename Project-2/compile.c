#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "tokens.h"
#include "generator.h"

int main(int argc, char* argv[]){
    // Open the input/output file
    FILE* ifp = fopen(argv[1], "r");
    FILE* ofp = fopen(argv[2], "w");

    // Create a structure that stores the token properties
    tok_prop properties;

    // Initialize counter to 0
    cx=0;

    // Parse the input
    program(ifp, ofp, &properties);

    // Generate intermediate code
    generate(ofp);

    return 0;
}
