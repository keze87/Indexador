main: main.o
	rm *.o && gcc -ansi -Wall -pedantic -pedantic-errors -o main main.c TDAGlosario.c AB.c Lista.c TDAParser.c -I. && rm *.o && rm *.sh && rm *.gch
