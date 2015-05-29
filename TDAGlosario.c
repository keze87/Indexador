#include "TDAGlosario.h"

int CrearGlosario(TDAGlosario* g, char* documento, char* arch_config)
{

	int error = 1; /* OK */

	TDAParser ListaParser;

	error = PA_Crear(documento,arch_config,&ListaParser);

	/* Magia */

	return error;

}

int DestruirGlosario(TDAGlosario* g)
{

	/* Magia */

	return TRUE;

}

int ConsultarPalabraGlosario(TDAGlosario* g, char* palabra, TListaSimple* LResultado)
{

	/* Magia */

	return TRUE;

}

int Ranking_palabras_Glosario(TDAGlosario* g, TListaSimple* LResultado)
{

	/* Más Magia */

	return TRUE;

}
