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

	lista_a_arbol(g, ListaParser);

	error = PA_Destruir(&ListaParser);

	return error;

}

int lista_a_arbol(TDAGlosario* g, TDAParser ListaParser){
    int mov=OK;
    TPalabra elem;
    TElemParser aux_parser;
    TPosicion posicion;

    if (L_Vacia(ListaParser.parser))
        return 0; /*si esta vacia, deja vacio el glosario tambien*/

    mov=L_Mover_Cte(&(ListaParser.parser), L_Primero);
    L_Elem_Cte(ListaParser.parser, &aux_parser);

    while (mov==OK){

        strcpy(elem.palabra, aux_parser.palabra);
        /*printf("ASD: %s\n", elem.palabra);*/
        L_Crear(&(elem.posiciones), sizeof(TPosicion));
        elem.cont=0; /*inicializo el contador*/
        while((mov==OK)&&(strcmp(elem.palabra, aux_parser.palabra)==0)){   /*mientras no termine y sea igual la palabra*/
            posicion.linea=aux_parser.linea;
            posicion.pag=aux_parser.pagina;
            posicion.pos=aux_parser.pos;
            if (L_Vacia(elem.posiciones))   /*si esta vacia la lista, lo agrego en el primero. si no, en el siguiente*/
                L_Insertar_Cte(&(elem.posiciones), L_Primero, &posicion);
            else
                L_Insertar_Cte(&(elem.posiciones), L_Siguiente, &posicion);
            (elem.cont)++;
            mov=L_Mover_Cte(&(ListaParser.parser), L_Siguiente);
            L_Elem_Cte(ListaParser.parser, &aux_parser);
        }
        /*guardo el elem en el arbol*/

        if (AB_Vacio(g->arbol)){ /*si el arbol esta vacio, lo inserto en el raiz*/
            AB_Insertar(&(g->arbol), RAIZ, &elem);
            /*printf("%s. %d\n", elem.palabra, elem.cont);*/
        }
        else{
            AB_MoverCte(&(g->arbol), RAIZ); /*como no esta vacio el arbol, no puede dar error*/
            guardar_ordenado(&(g->arbol), elem);
            /*printf("%s. %d\n", elem.palabra, elem.cont);*/
        }

    }

    if (mov!=OK)
        return 0; /*termino de recorrer la lista parser*/

	return 1;

}

int guardar_ordenado(TAB *arbol, TPalabra elem){    /*esta hecho recursivo*/
    int error=OK;
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

    return error;

}

/* Inserta un elemento en la lista de forma ordenada
 * POST: Si puede insertar el elemento devuelve TRUE, sino devuelve FALSE
 */
int L_Insertar_Ordenado(TListaSimple* Lista, TPalabra Elem){
	TPalabra aux;
	int mov=TRUE;
	if (L_Vacia(*Lista)) /* Si está vacía lo inserto como L_Primero y devuelvo el valor correspondiente */
        	return (L_Insertar_Cte(Lista, L_Primero, &Elem)); /* Si pudo insertar: TRUE, sino FALSE */
	L_Elem_Cte(*Lista, &aux);
	if (aux.cont < Elem.cont) /* Si el corriente es menor que el que quiero insertar, voy al primero */
        	mov = L_Mover_Cte(Lista, L_Primero);
	L_Elem_Cte(*Lista, &aux);
	while ((mov == OK)&&(aux.cont >= Elem.cont)) { /* Mientras que pueda moverse y aux sea mayor o igual al elem */
		mov = L_Mover_Cte(Lista, L_Siguiente);
		L_Elem_Cte(*Lista, &aux);
	}
	if (mov != TRUE)
		return (L_Insertar_Cte(Lista, L_Siguiente, &Elem));
	else
        	return (L_Insertar_Cte(Lista, L_Anterior, &Elem));
}

void DestruirListas(TAB arbol, int mov)
{

	TPalabra elem;
	int error;

	error = AB_MoverCte(&arbol, mov);

	if (error == TRUE)
	{
		DestruirListas(arbol, IZQ);

		AB_ElemCte(arbol, &elem);
		L_Vaciar(&elem.posiciones);

		DestruirListas(arbol, DER);
	}

}

int DestruirGlosario(TDAGlosario* g)
{

	DestruirListas(g->arbol,RAIZ);

	AB_Vaciar(&g->arbol);

	return TRUE;

}

int ConsultarPalabraGlosario(TDAGlosario* g, char* palabra, TListaSimple* LResultado)
{
    int error=OK;
    TPalabra elem;
    TPosicion elem_pos;
    int mov;

    /*si busqueda   devuelve FALSE es porque no se encontro
                    devuelve TRUE si se encontro
    */
    AB_MoverCte(&(g->arbol), RAIZ);
    error=busqueda(&(g->arbol), palabra);
    if (error==FALSE){  /*si no lo encontro*/
        printf("La palabra %s no se encontro\n", palabra);
        return error;
    }
    AB_ElemCte(g->arbol, &elem);
    printf("%s\n", elem.palabra);
    /*recorro la lista de las posiciones*/
    mov = L_Mover_Cte(&(elem.posiciones), L_Primero);
    while(mov==TRUE){
        L_Elem_Cte(elem.posiciones, &elem_pos);
        printf("pagina %d linea %d posicion %d\n", elem_pos.pag, elem_pos.linea, elem_pos.pos);
        mov=L_Mover_Cte(&(elem.posiciones), L_Siguiente);
    }

	return TRUE;

}

int busqueda(TAB *arbol, char *palabra){
    TPalabra elem;
    int error=OK;
    int mov=RAIZ;

    if (AB_Vacio(*arbol)){
        return FALSE;
    }
    AB_ElemCte(*arbol, &elem);

    if(strcmp(elem.palabra, palabra)==0)
        return TRUE;
    if(strcmp(elem.palabra, palabra)>0)
        mov=IZQ;
    else
        mov=DER;
    /*printf("MOV=%d\n",mov);*/
    error=AB_MoverCte(arbol, mov);
    if(error!=FALSE){
        error=busqueda(arbol, palabra);
        return error;
    }
    else{
        return FALSE;
    }

}

/* Realiza un recorrido InOrder del árbol e inserta cada elemento en una lista
 * La inserción puede fallar por falta de memoria. Si es exitosa devuelve TRUE, sino FALSE
 */
int RecorrerInOrder_InsertarEnLista(TAB arbol, int mov, TListaSimple* LResultado)
{
	TPalabra elem;
	int error;
	int result = TRUE;
	error = AB_MoverCte(&arbol, mov);
	if (error == TRUE) {
        	RecorrerInOrder_InsertarEnLista(arbol, IZQ, LResultado);
        	AB_ElemCte(arbol, &elem);
        	result = L_Insertar_Ordenado(LResultado, elem);
        	/* Inserto el elemento ordenado por cantidad de repeticiones */
        	RecorrerInOrder_InsertarEnLista(arbol, DER, LResultado);
    	}
	return result;
}

int Ranking_palabras_Glosario(TDAGlosario* g, TListaSimple* LResultado)
{
	if (LResultado->TamanioDato == sizeof(TPalabra))
		L_Vaciar(LResultado);

	L_Crear(LResultado, sizeof(TPalabra));

	return (RecorrerInOrder_InsertarEnLista((g->arbol), RAIZ, LResultado));
}
