#ifndef __TDAParser_H__
#define __TDAParser_H__

#include "Lista.h"

typedef struct TDAParser{
	TListaSimple parser;
}TDAParser;

int PA_Crear(char* RutaDoc, char* RutaConf, TDAParser* Resultado);

int PA_Destruir(TDAParser* Parser);

int PA_SigPalabra();

#endif
