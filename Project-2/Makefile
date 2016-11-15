# -*- MakeFile -*-

objects = compile.o generator.o get_token.o parser.o symbol.o

compile : $(objects)
	gcc -o compile $(objects)


#compile.o : parser.h tokens.h generator.h	
#generator.o : generator.h symbol.h
#get_token.o : tokens.h parser.h symbol.h
#parser.o : tokens.h parser.h generator.h symbol.h	
#symbol.o : symbol.h
	
clean : 
	rm *.o 
