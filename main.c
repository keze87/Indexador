#include <stdio.h>
#include "TDAGlosario.h"

int Proceso(char* RutaDoc, char* RutaConf, char* RutaIns);

int main(int argc, char *argv[])
{

	/* recibe 3 rutas
	 * documento a leer
	 * archivo de configuraciones
	 * archivo de instrucciones */
	if (argc != 4)
	{

		fprintf(stderr,"Parámetros necesarios:\n");
		fprintf(stderr,"<Documento> <Configuraciones> <Instrucciones>\n");

		return FALSE;

	}

	return Proceso(argv[1],argv[2],argv[3]);

}

int Proceso(char* RutaDoc, char* RutaConf, char* RutaIns)
{

	FILE* Instrucciones;
	char Linea[255];
	TDAGlosario Glosario;
	TListaSimple Lista;

	int error = OK;

	if ((fopen(RutaIns,"r") == NULL) || (fopen(RutaConf,"r") == NULL) || (fopen(RutaDoc,"r") == NULL)) /* Compruebo que los archivos existan */
	{
		fprintf(stderr,"Archivo(s) Inexistente(s)\n");
		return FALSE; /* Un Enum quedaría mejor */
	}

	Instrucciones = fopen(RutaIns,"r");

	error = CrearGlosario(&Glosario,RutaDoc,RutaIns);

	while (!feof(Instrucciones)) /* Leo hasta que llegue al final */ /* No estoy seguro si se hace así */
	{

		fgets(Linea, 4, Instrucciones); /* Las instrucciones solo miden 3 caracteres (con el espacio) */

		if (strcmp(Linea,"cp ") == 0)
		{

			fgets(Linea, 250, Instrucciones);

			error = ConsultarPalabraGlosario(&Glosario,Linea,&Lista);

		}
		else
		{
			if (strcmp(Linea,"rp ") == 0)
			{

				error = Ranking_palabras_Glosario(&Glosario,&Lista);

			}
			else
			{
				if (strcmp(Linea,"dg") == 0)
				{

					error = DestruirGlosario(&Glosario);

				}
			}
		}

	}

	return error;

}
