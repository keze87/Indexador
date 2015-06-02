#include "TDAGlosario.h"

int CrearGlosario(TDAGlosario* g, char* documento, char* arch_config)
{

	int error = 1; /* OK */

	TDAParser ListaParser;

	error = PA_Crear(documento,arch_config,&ListaParser);
	if (error != 1)
	{
		PA_Destruir(&ListaParser);
		return error;
	}

	AB_Crear(&g->arbol,sizeof(TPalabra));

	/* Magia */

	error = PA_Destruir(&ListaParser);

	return error;

}

int DestruirGlosario(TDAGlosario* g)
{

	AB_Vaciar(&g->arbol);

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
