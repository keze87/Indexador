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

int guardar_ordenado(TAB *arbol, TPalabra elem){    /*esta hecho recursivo*/
    int error=OK;
    int mov=OK;
    TPalabra aux;

    if (AB_Vacio(*arbol)){ /*si el arbol esta vacio, lo inserto en el raiz*/
        error=AB_Insertar(arbol, RAIZ, &elem);
        return error;
    }

    AB_ElemCte(*arbol, &aux);

    if(strcmp(elem.palabra, aux.palabra)<0){
        error=AB_MoverCte(arbol, IZQ);
        if (error==FALSE) /*si no se pudo mover es porque no tiene un hijo IZQ. entonces inserto a la izquierda*/
            return AB_Insertar(arbol, IZQ, &elem);
        else
            return(guardar_ordenado(arbol, elem));
    }

    if(strcmp(elem.palabra, aux.palabra)>0){
        error=AB_MoverCte(arbol, DER);
        if (error==FALSE) /*si no se pudo mover es porque no tiene un hijo DER. entonces inserto a la derecha*/
            return AB_Insertar(arbol, DER, &elem);
        else
            return(guardar_ordenado(arbol, elem));
    }

}

void in_order(TAB arbol, int mov){
    TPalabra elem;
    int error;
    int movim=OK;
    TPosicion pos;

    error=AB_MoverCte(&arbol, mov);
    if(error==TRUE){
        in_order(arbol, IZQ);
        AB_ElemCte(arbol, &elem);
        printf("\n%s. %d\n", elem.palabra, elem.cont);
        L_Mover_Cte(&(elem.posiciones), L_Primero);

        while(movim==OK){   /*recorro la lista de las posiciones de cada palabra*/
            L_Elem_Cte(elem.posiciones, &pos);
            printf("PAG: %d - LIN: %d - POS: %d\n", pos.pag, pos.linea, pos.pos);

            movim=L_Mover_Cte(&(elem.posiciones), L_Siguiente);
        }
        in_order(arbol, DER);

    }


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
