#include <stdio.h>
#include "TDAParser.h"

typedef enum Separador{
	No = 0,
	Si = 1,
	CambioPagina = 2
}Separador;

int PA_Crear(char* RutaDoc, char* RutaConf, TDAParser* Resultado)
{

	char separadores[255];
	int cant_separadores = 0;

	int error = 1; /* OK */

	cant_separadores = PConfiguraciones(RutaConf,separadores);

	if ((cant_separadores == 0) || (separadores[0] == 0))
		return 0; /* KO */

	error = PA_SigPalabra(RutaDoc,cant_separadores,separadores,&Resultado->parser);

	return error;

}

int PConfiguraciones(char* RutaConf, char separadores[255])
{

	FILE* Conf/*iguraciones*/ = fopen(RutaConf,"r");

	char letra = 0;
	char letra_sgte = 0;

	int cant_separadores = 0;

	separadores[0] = 0;

	while (letra != EOF)
	{

		while (letra != '[')
		{

			letra = fgetc(Conf);

			if (letra == EOF)
			{
				fclose(Conf);
				return cant_separadores;
			}

		}

		if (letra == '[')
		{

			letra = fgetc(Conf);
			letra = fgetc(Conf); /* Adelanto 2 letras */

			if (letra == 'A') /* [SALTO_PAGINA] */
			{

				while ((letra != EOF) && (letra != 34 /* " */) && (letra != 39 /* ' */))
				{

					letra = fgetc(Conf);

					if ((letra == 34 /* " */) || (letra == 39 /* ' */))
					{

						letra = fgetc(Conf);
						separadores[0] = letra;
						letra = fgetc(Conf);

					}

				}

			}

			if (letra == 'E') /* [SEPARA_PALABRA] */
			{

				while ((letra != EOF) || (letra != '['))
				{
					letra = fgetc(Conf);

					if (letra == EOF)
					{
						fclose(Conf);
						return cant_separadores;
					}

					if ((letra == 34 /* " */) || (letra == 39 /* ' */))
					{

						letra = fgetc(Conf);
						letra_sgte = fgetc(Conf);

						if ((letra_sgte == 34 /* " */) || (letra_sgte == 39 /* ' */)) /* por si tengo caracter="" */
						{
							cant_separadores++;
							separadores[cant_separadores] = letra;
							letra = fgetc(Conf);
						}

					}
				}

			}

		}

	}

	fclose(Conf);

	return cant_separadores;

}

int PA_SigPalabra(char* RutaDoc, int cant_separadores, char* separadores, TListaSimple* ListaParser)
{

	int error;

	FILE* Documento = fopen(RutaDoc,"r");

	TElemParser Elem;

	char letra;

	int primera_letra = TRUE;
	int pos = 0;

	int largo = 0; /* tamaño de palabra */

	int aux; /* for de separadores */
	Separador es_separador;

	Elem.pagina = 1;
	Elem.linea = 1;
	Elem.pos = 0;

	L_Crear(ListaParser,sizeof(TElemParser));

	while (!feof(Documento))
	{

		letra = fgetc(Documento);
		pos++;

		for(aux = 0, es_separador = No; aux <= cant_separadores; aux++)
		{
			if (letra == separadores[aux])
			{
				if (aux == 0)
					es_separador = CambioPagina;
				else
					es_separador = Si;

				break;
			}
		}

		if (letra == '\n')
		{
			es_separador = Si;
			Elem.linea++;
			pos = 0;
		}
		if ((letra == EOF) || (letra == 13))
		{
			es_separador = Si;
		}

		if (es_separador == No)
		{
			Elem.palabra[largo] = letra;
			largo++;

			if (primera_letra == TRUE)
			{
				Elem.pos = pos;
				primera_letra = FALSE;
			}
		}
		else
		{
			primera_letra = TRUE;

			Elem.palabra[largo] = 0;

			if (largo > 0)
			{

				/*error = L_Insertar_Cte(ListaParser,L_Siguiente,&Elem);*/
				error=insertar_ordenado(ListaParser, Elem);

			}

			largo = 0;

			if (es_separador == CambioPagina)
				Elem.pagina++;
		}

	}

	fclose(Documento);

	return error;

}

int insertar_ordenado(TListaSimple* ListaParser, TElemParser Elem){
    TElemParser aux;
    int mov=OK;

    if (L_Vacia(*ListaParser)){ /*si esta vacia, lo inserto en el primero y salgo*/
        L_Insertar_Cte(ListaParser, L_Primero, &Elem);
        return OK;
    }

    L_Elem_Cte(*ListaParser, &aux);
    if (strcmp(&(aux.palabra), &(Elem.palabra))>0) /*si el corriente es mayor que el que quiero insertar, voy al primero*/
        L_Mover_Cte(ListaParser, L_Primero);

    L_Elem_Cte(*ListaParser, &aux);
    while ((mov==OK)&&(strcmp(&(aux.palabra), &(Elem.palabra))<=0)){   /*mientras que pueda moverse y el aux sea menor o igual al elem*/
        mov=L_Mover_Cte(ListaParser, L_Siguiente);
        L_Elem_Cte(*ListaParser, &aux);
    }
    if (mov!=OK)
        L_Insertar_Cte(ListaParser, L_Siguiente, &Elem);
    else
        L_Insertar_Cte(ListaParser, L_Anterior, &Elem);

    return OK;

}


int PA_Destruir(TDAParser* Parser)
{

	/* Esto vuela */
	int error = 1;
	TElemParser Elem;

	/* Compruebo que la lista esté creada */
	if (Parser->parser.TamanioDato != sizeof(TElemParser))
		return 0;

	error = L_Mover_Cte(&Parser->parser,L_Primero);

	while (error == 1)
	{
		L_Elem_Cte(Parser->parser,&Elem);
		error = L_Mover_Cte(&Parser->parser,L_Siguiente);

		printf("Palabra: %s\n",Elem.palabra);
		printf("Pagina: %d\n",Elem.pagina);
		printf("Linea: %d\n",Elem.linea);
		printf("Posicion: %d\n\n",Elem.pos);
	}
	/* Esto vuela */

	L_Vaciar(&Parser->parser);

	return 0;

}
