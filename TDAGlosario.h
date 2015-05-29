#ifndef __TDAGlosario_H__
#define __TDAGlosario_H__

#include "AB.h"
#include "Lista.h"

#define OK 1

typedef struct TDAGlosario{
	TAB arbol;
}TDAGlosario;

int CrearGlosario(TDAGlosario* g, char* documento, char* arch_config);

int DestruirGlosario(TDAGlosario* g);

int ConsultarPalabraGlosario(TDAGlosario* g, char* palabra, TListaSimple* LResultado);

int Ranking_palabras_Glosario(TDAGlosario* g, TListaSimple* LResultado);

#endif
