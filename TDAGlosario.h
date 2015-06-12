#ifndef __TDAGlosario_H__
#define __TDAGlosario_H__

#include <stdio.h>
#include "AB.h"
#include "Lista.h"
#include "TDAParser.h"

#define OK 1
#define CANTMAX 255

typedef struct TDAGlosario{
	TAB arbol;
}TDAGlosario;

typedef struct TPalabra{
	char palabra[CANTMAX];
	TListaSimple posiciones;
	int cont; /* veces que aparece */
}TPalabra;

typedef struct TPosicion{
	int pag;
	int linea;
	int pos;
}TPosicion;

int CrearGlosario(TDAGlosario* g, char* documento, char* arch_config);

int DestruirGlosario(TDAGlosario* g);

int ConsultarPalabraGlosario(TDAGlosario* g, char* palabra, TListaSimple* LResultado);

int Ranking_palabras_Glosario(TDAGlosario* g, TListaSimple* LResultado);

int lista_a_arbol(TDAGlosario* g, TDAParser ListaParser);

int guardar_ordenado(TAB *arbol, TPalabra elem);

void in_order(TAB arbol, int mov);

int busqueda(TAB *arbol, char *palabra);

#endif
