#include "TDAGlosario.h"

int Proceso(char* RutaDoc, char* RutaConf, char* RutaIns);

/* Realiza un ranking de palabras
 * Si se puede realizar, devuelve TRUE, sino devuelve FALSE
 */
int MostrarRankingPalabras (TDAGlosario* g,TListaSimple* Lista);

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

	FILE* Documento;
	FILE* Configuraciones;
	FILE* Instrucciones;
	char Linea[255];
	TDAGlosario Glosario;
	TListaSimple Lista;

	int error = OK;
	int aux;
	int destruido = FALSE;

	/* Compruebo que los archivos existan */
	Documento = fopen(RutaDoc,"r");

	if (Documento == NULL)
	{
		fprintf(stderr,"Archivo %s Inexistente\n",RutaDoc);
		return FALSE;
	}
	else
		fclose(Documento);

	Configuraciones = fopen(RutaConf,"r");

	if (Configuraciones == NULL)
	{
		fprintf(stderr,"Archivo %s Inexistente\n",RutaConf);
		return FALSE;
	}
	else
		fclose(Configuraciones);

	Instrucciones = fopen(RutaIns,"r");

	if (Instrucciones == NULL)
	{
		fprintf(stderr,"Archivo %s Inexistente\n",RutaIns);
		return FALSE;
	}

	error = CrearGlosario(&Glosario,RutaDoc,RutaConf);

	printf("\n");

	while ((!feof(Instrucciones)) && (error == OK)) /* Leo hasta que llegue al final */
	{

		fgets(Linea, 5, Instrucciones); /* Las instrucciones solo miden 4 caracteres (con el espacio) */

		if (strcmp(Linea,"-cp ") == 0)
		{

			fscanf(Instrucciones, "%s", Linea);

			for (aux = 0; aux < strlen(Linea); aux++)
				if ((Linea[aux] >= 'A') && (Linea[aux] <= 'Z'))
					Linea[aux] = Linea[aux] + 'a' - 'A';

			if ((Linea[0] >= 'a') && (Linea[0] <= 'z'))
				Linea[0] = Linea[0] - 'a' + 'A';

			ConsultarPalabraGlosario(&Glosario,Linea,&Lista);

			printf("\n");

		}
		else
		{
			if (strcmp(Linea,"-rp") >= 0)
			{
				error = MostrarRankingPalabras(&Glosario,&Lista);
				if (error == FALSE)
					fprintf(stderr,"No existe suficiente memoria\n");

				printf("\n");
			}
			else
			{
				if ((strcmp(Linea,"-dg") >= 0) && (destruido == FALSE))
				{

					error = DestruirGlosario(&Glosario);

					destruido = TRUE;

				}
			}
		}

	}

	if (destruido == FALSE)
		error = DestruirGlosario(&Glosario);

	fclose(Instrucciones);

	L_Vaciar(&Lista);

	return error;

}

int MostrarRankingPalabras(TDAGlosario* g,TListaSimple* Lista)
{
	int mov,result;
	TPalabra elem;
	result = Ranking_palabras_Glosario(g, Lista);
	if (result != TRUE)
		return FALSE; /* No existe suficiente memoria */
	else {
		if (L_Vacia(*Lista) == TRUE) {
			fprintf(stderr,"El ranking se encuentra vacio.\n");
			return TRUE;
        	}
        	else {
        		mov = L_Mover_Cte(Lista, L_Primero); /* Sé que existe porque no esta vacía */
        		while (mov) { /* Mientras pueda moverme */
        			L_Elem_Cte(*Lista, &elem);
				fprintf(stdout, "%s %d repeticiones\n", elem.palabra, elem.cont);
				mov = L_Mover_Cte(Lista, L_Siguiente);
        		}
        		return TRUE;
        	}
	}
}
