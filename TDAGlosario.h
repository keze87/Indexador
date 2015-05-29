#ifndef __TDAGlosario_H__
#define __TDAGlosario_H__

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

int CrearGlosario(TDAGlosario* g, char* documento, char* arch_config);

int DestruirGlosario(TDAGlosario* g);

int ConsultarPalabraGlosario(TDAGlosario* g, char* palabra, TListaSimple* LResultado);

int Ranking_palabras_Glosario(TDAGlosario* g, TListaSimple* LResultado);

#endif
