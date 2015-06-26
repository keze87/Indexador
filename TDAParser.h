#ifndef __TDAParser_H__
#define __TDAParser_H__

#include <stdio.h>
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

/*
PRE: el archivo de configuración debe tener el formato pedido en el enunciado del TP
POST: crea el TDAParser con las palabras del texto y sus posiciones
*/
int PA_Crear(char* RutaDoc, char* RutaConf, TDAParser* Resultado);

/*
PRE: Parser creado
POST: Destruye la estructura del TDA
*/
int PA_Destruir(TDAParser* Parser);

/*
PRE: ListaParser creada, el archivo de RutaDoc debe ser válido.
POST: Inserta en ListaParser las palabras con su posicion en el archivo <RutaDoc>.
*/
int PA_SigPalabra(char* RutaDoc, int cant_separadores, char* separadores, TListaSimple* ListaParser);


#endif
