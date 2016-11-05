# -*- MakeFile -*-

objects = compile.o generator.o get_token.o parser.o

compile : $(objects)
	gcc -o compile $(objects)
	
compile.o : parser.h tokens.h generator.h	
generator.o :  generator.h
get_token.o : tokens.h parser.h
parser.o : tokens.h parser.h
	
.PHONY : clean
clean : 
	rm -f compile *.o 
