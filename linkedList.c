#include "linkedList.h"



usersList* startLinkedList()
{
    return NULL;
}

usersList* createNode (usersList value)
{
    usersList* aux = (usersList*) malloc(sizeof(usersList));
    aux->value = value;
    aux->prev = NULL;
    aux->next = NULL;
    return aux;
}

usersList* addFirst(usersList* userList, usersList* newOne)
{

    newOne->next = userList;
    if (userList)
    {
        userList->prev = newOne;
    }
    return newOne;
}


void showDoubleList(usersList* toShow)
{
    if (toShow)
    {
        showCar(toShow->value);
        showDoubleList(toShow->next);
    }
    puts("---------------------");
}


usersList * buscarUltimoR(usersList * list)
{
    usersList * aux = NULL;
    if(lista!=NULL)
    {
        if(lista->ste==NULL)
        {
            rta=lista;
        }
        else
        {
            rta=buscarUltimoR(lista->ste);
        }
    }
    return rta;
}

nodo2 * agregarAlFinal(nodo2 * lista, nodo2 * nuevoNodo)
{
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else
    {
        nodo2 * ultimo = buscarUltimoR(lista);
        ultimo->ste = nuevoNodo;
        nuevoNodo->ante = ultimo;
    }
    return lista;
}

nodo2 * insertarNodo(nodo2 * lista, nodo2 * nuevoNodo)
{
    if(lista==NULL)
    {
        lista=nuevoNodo;
    }
    else if (nuevoNodo->dato< lista->dato)
    {
        lista=agregarAlPrincipio(lista, nuevoNodo);
    }
    else
    {

        nodo2 * anterior=lista;
        nodo2 * seg=lista->ste;

        while(seg!=NULL && seg->dato < nuevoNodo->dato)
        {
            anterior=seg;
            seg=seg->ste;
        }

        anterior->ste =nuevoNodo;

        nuevoNodo->ante = anterior;
        nuevoNodo->ste=seg;

        if(seg!=NULL)
        {
            seg->ante= nuevoNodo;
        }
    }
    return lista;
}

nodo2 * borrarNodo(nodo2 * lista, int dato)
{
    nodo2 * aBorrar=NULL;
    nodo2 * seg=NULL;

    if(lista!=NULL)
    {
        if(lista->dato==dato)
        {
            aBorrar=lista;

            lista=lista->ste;
            if(lista!=NULL)
                lista->ante=NULL;

            free(aBorrar);
        }
        else
        {
            seg=lista->ste;
            while(seg!=NULL && seg->dato!=dato)
            {
                seg=seg->ste;
            }

            if( seg!= NULL)
            {
                nodo2 * anterior=seg->ante; // bajo a una variable el anterior

                anterior->ste = seg->ste; //salteo el nodo que quiero eliminar.

                if(seg->ste) // si existe el nodo siguiente
                {
                    nodo2 * siguiente = seg->ste;
                    siguiente->ante=anterior;
                }
                free(seg); //elimino el nodo.
            }

        }
    }

    return lista;

}

int verPrimero2 (nodo2 * lista)
{
    int rta=0;

    if(lista)
        rta=lista->dato;

    return rta;

}

nodo2 * borrarPrimero (nodo2 * lista)
{
    nodo2 * aux = lista;;
    if (lista)
    {
        lista=lista->ste;
        if(lista)
            lista->ante=NULL;
        free(aux);
    }
    return lista;
}


void mostrarNodo2(nodo2 * aux)
{
    printf("[%d] ", aux->dato);
}

void recorrerYmostrar2(nodo2 * lista)
{
    nodo2 * seg = lista;
    while (seg != NULL)
    {
        mostrarNodo2(seg);
        seg= seg->ste;
    }
}
