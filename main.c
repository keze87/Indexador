#include "TDAGlosario.h"

int Proceso(char* RutaDoc, char* RutaConf, char* RutaIns);

/* Realiza un ranking de palabras
 * Si se puede realizar, devuelve TRUE, sino devuelve FALSE
 */
int MostrarRankingPalabras (TDAGlosario* g,TListaSimple* Lista);

/* Se encarga de invertir los elemento de una lista
 * Si se puede realizar, devuelve TRUE, sino devuelve FALSE
 */
int InvertirLista(TListaSimple* L1, TListaSimple* L2);

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

	while ((!feof(Instrucciones)) && (error == OK)) /* Leo hasta que llegue al final */
	{

		fgets(Linea, 5, Instrucciones); /* Las instrucciones solo miden 4 caracteres (con el espacio) */

		if (strcmp(Linea,"-cp ") == 0)
		{

			fscanf(Instrucciones, "%s", Linea);

			ConsultarPalabraGlosario(&Glosario,Linea,&Lista);

		}
		else
		{
			if (strcmp(Linea,"-rp") >= 0)
			{
				error = MostrarRankingPalabras(&Glosario,&Lista);
				if (error == FALSE)
					fprintf(stderr,"No existe suficiente memoria\n");
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

	return error;

}

int MostrarRankingPalabras(TDAGlosario* g,TListaSimple* Lista)
{
	int mov,result;
	TListaSimple ListaAux;
	TPalabra elem;
	result = Ranking_palabras_Glosario(g, Lista);
	if (result != TRUE)
		return FALSE; /* No existe suficiente memoria */
	else {
		if (L_Vacia(*Lista) == TRUE) {
			fprintf(stderr,"El ranking se encuentra vacio.\n");
			return TRUE;
        	}
        	L_Crear(&ListaAux, sizeof(TPalabra));
        	result = InvertirLista(Lista, &ListaAux);
        	if (result != TRUE)
        		return FALSE; /* No existe suficiente memoria */
        	else {
        		mov = L_Mover_Cte(&ListaAux, L_Primero); /* Sé que existe porque no esta vacía */
        		while (mov) { /* Mientras pueda moverme */
        			L_Elem_Cte(ListaAux, &elem);
				fprintf(stdout, "%s %d repeticiones\n", elem.palabra, elem.cont);
				mov = L_Mover_Cte(&ListaAux, L_Siguiente);
        		}
        		return TRUE;
        	}

	}
}

int InvertirLista(TListaSimple* L1, TListaSimple* L2)
{
	int mov;
	TPalabra elem;
	if (L_Vacia(*L1) == TRUE)
        	return TRUE;
	else {
        	mov = L_Mover_Cte(L1, L_Primero);
        	while (mov) { /* Mientras pueda moverme */
            		L_Elem_Cte(*L1,&elem);
            		if (L_Insertar_Cte(L2, L_Primero, &elem) == FALSE)
                		return FALSE; /* No se pudo insertar por falta de memoria */
            		mov = L_Mover_Cte(L1, L_Siguiente);
        	}
        return TRUE;
	}
}
