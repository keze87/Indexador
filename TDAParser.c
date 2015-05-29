#include <stdio.h>
#include "TDAParser.h"

int PConfiguraciones(char* RutaConf, char separadores[255]/*, int cant_separadores*/)
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
				return cant_separadores;

		}

		if (letra == '[')
		{

			letra = fgetc(Conf);
			letra = fgetc(Conf); /*Adelanto 2 letras*/

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
						return cant_separadores;

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

	return TRUE;

}

int PA_Crear(char* RutaDoc, char* RutaConf, TDAParser* Resultado)
{

	/*FILE* Documento = fopen(RutaDoc,"r");*/

	char separadores[255];
	int cant_separadores = 0;

	int error = 1; /* OK */

	cant_separadores = PConfiguraciones(RutaConf,separadores/*,cant_separadores*/);

	printf("%d\n",cant_separadores);

	return error;

}
