#ifndef __TDAParser_H__
#define __TDAParser_H__

#include "Lista.h"

typedef struct TElemParser{
	char palabra[255];
	int pagina;
	int linea;
	int pos;
}TElemParser;

typedef struct TDAParser{
	TListaSimple parser;
}TDAParser;

int PA_Crear(char* RutaDoc, char* RutaConf, TDAParser* Resultado);

int PA_Destruir(TDAParser* Parser);

int PA_SigPalabra(char* RutaDoc, int cant_separadores, char* separadores, TListaSimple* ListaParser);

/* Procesa archivo Configraciones */
int PConfiguraciones(char* RutaConf, char separadores[255]);

int insertar_ordenado(TListaSimple* ListaParser, TElemParser Elem);

#endif
