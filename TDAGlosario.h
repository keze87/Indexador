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

/*
PRE: arch_config debe tener el formato enunciado en el TP.
POST: crea la estructura parseando documento, teniendo en
cuenta el arch_config para parsearlo y deja lista la estructura para su explotación.
*/
int CrearGlosario(TDAGlosario* g, char* documento, char* arch_config);

/*
PRE: g creado
POST: elimina la información de la estructura
*/
int DestruirGlosario(TDAGlosario* g);

/*
PRE: LResultado lista simple creada y vacía, g creado.
POST: devuelve en LResultado la lista con las posiciones en que fue encontrada la palabra
*/
int ConsultarPalabraGlosario(TDAGlosario* g, char* palabra, TListaSimple* LResultado);

/*
PRE: Lresultado creada y vacía, g creado.
POST: Devuelve en LResultado el ranking de las palabras ordenado de forma descendente por cantidad de apariciones.
*/
int Ranking_palabras_Glosario(TDAGlosario* g, TListaSimple* LResultado);


#endif
