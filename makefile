main: main.o
	gcc -ansi -Wall -pedantic -pedantic-errors -o main main.c TDAGlosario.c AB.c -I. && rm *.o && rm *.sh && rm *.gch
