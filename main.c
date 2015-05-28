#include <stdio.h>
#define FALSE 0
#define OK 1

int main(int argc, char *argv[])
{

	/* recibe 3 rutas a archivo
	 * documento a leer
	 * archivo de configuraciones
	 * archivo de instrucciones */
	if (argc < 4)
	{

		fprintf(stderr,"Parametros necesarios:\n");
		fprintf(stderr,"<Documento> <Configuraciones> <Instrucciones>\n");

		return FALSE;

	}

	return OK;

}
