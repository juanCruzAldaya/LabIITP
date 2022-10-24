#include "userLinkedList.h"


node2User* startLinkedList()
{
    return NULL;
}

node2User* createUserNode (stUser user)
{
    node2User* aux = (node2User*) malloc(sizeof(node2User));
    aux->user = user;
    aux->prev = NULL;
    aux->next = NULL;
    return aux;
}

node2User* addFirst(node2User* userList, node2User* newOne)
{

    newOne->next = userList;
    if (userList)
    {
        userList->prev = newOne;
    }
    return newOne;
}




node2User * searchLastUser(node2User * userList) ///retorna el ultimo usuario, de manera recursiva
{
    node2User * aux;

    if(userList!=NULL)
    {
        if(userList->next == NULL)
        {
            aux = userList;
        }
        else
        {
            aux = buscarUltimoR(userList->next);
        }
    }
    return aux;
}

node2User * addLast(node2User * userList, node2User * toAdd)
{
    if(!userList)
    {
        userList = toAdd;
    }
    else
    {
        node2User * last = searchLastUser(userList);
        last->next = toAdd;
        toAdd->prev = last;
    }
    return userList;
}

node2User * insertUser(node2User * userList, node2User * toInsert)
{
    if(!userList)
    {
        userList = toInsert;
    }
    else if ((toInsert->user.idUser) < (userList->user.idUser))
    {
        userList = addFirst(userList, toInsert);
    }
    else
    {

        node2User * prev = userList;
        node2User * next = userList->next;

        while(next!=NULL && (next->user.idUser < toInsert->user.idUser))
        {
            prev = next;
            next = next->next;
        }

        prev->next = toInsert;

        toInsert->prev = prev;
        toInsert->next = next;

        if(next)
        {
            next->prev= toInsert;
        }
    }
    return userList;
}

node2User * deleteNode(node2User * userList, int idUser)
{
    node2User * toDelete = NULL;
    node2User * next = NULL;

    if(userList)
    {
        if(userList->dato == dato)
        {
            toDelete = userList;

            userList = userList->next;
            if(userList)
                userList->ante = NULL;
            free(toDelete);
        }
        else
        {
            next = userList->next;
            while(next && next->user.idUser != idUser)
            {
                next = next->next;
            }
            if(next)
            {
                node2User * prev = next->ante; // bajo a una variable el anterior

                prev->next = next->next; //salteo el nodo que quiero eliminar.

                if(next->next) // si existe el nodo siguiente
                {
                    node2User * seg = next->next;
                    seg->prev = prev;
                }
                free(next); //elimino el nodo.
            }

        }
    }

    return userList;

}


node2User * deleteFirst (node2User * userList)
{
    node2User * aux = userList;
    if (userList)
    {
        userList = userList->next;
        if(userList)
            userList->ante=NULL;
        free(aux);
    }
    return userList;
}


void showUserNode(node2User * toShow)
{
    puts("-------------------------------------------------------------------\n");
    printf("ID USUARIO: %d\n",toShow->value.idUser);
    printf("NOMBRE COMPLETO: %s\n"toShow->value.fullName);
    stWord pass = showPassword(toShow);
    printf("PASS: %s\n", pass);
    printf("Anio Nacimiento: %i\n",toShow->user.birthYear);
    printf("Genero: ");
    if (toShow->user.gender == 'f')
    {
        printf("Femenino\n");
    }
    else
    {
        printf("Masculino\n");
    }
    printf("country de origen: %s\n",toShow->user.country);
    printf("Cantidad de canciones escuchadas: %d\n",toShow->user.songPlays);

    if (toShow->user.off == 0)
    {
        printf("Estado: ACTIVO\n");
    }
    else
    {
        printf("Estado: INACTIVO\n");
    }
    puts("-------------------------------------------------------------------\n");
}

void showUserList(node2User * toShow) ///recursiva
{
    if (toShow)
    {
        showUserNode(toShow->user);
        showUserList(toShow->next);
    }
}

