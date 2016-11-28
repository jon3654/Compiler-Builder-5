# -*- MakeFile -*-
CFLAGS = -g -Wall -Wextra
objects = compile.o generator.o get_token.o parser.o symbol.o vm.o

compile : $(objects)
	gcc $(CFLAGS) -o compile $(objects)

#compile.o: compile.c
#	gcc $(CFLAGS) -c compile.c
#generator.o: generator.c
#	gcc $(CFLAGS) -c generator.c
#get_token.o: get_token.c
#	gcc $(CFLAGS) -c get_token.c
#parser.o: parser.c
#	gcc $(CFLAGS) -c parser.c
#symbol.o: symbol.c
#	gcc $(CFLAGS) -c symbol.c
#vm.o: vm.c
#	gcc $(CFLAGS) -c vm.c
clean :
	rm *.o
