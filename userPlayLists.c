#include "userPlayLists.h"

stCell * startCellList()
{
    return NULL;
}

stCell * createCellNode (stUser toCreate, nodeSongList * songList)
{
    stCell * cellAux = (stCell*)malloc(sizeof(stCell));
    cellAux->userValue = toCreate;
    cellAux->songList = songList;
    cellAux->next = NULL;
    return cellAux;
}

stCell * addFirst(stCell * cellList, stCell * toAdd)
{
    if (!cellList)
    {
        cellList = toAdd;
    }
    else
    {
        toAdd->next = cellList;
        cellList = toAdd;
    }
    return cellList;
}

stCell * searchLastCell(stCell * userList)
{
    stCell * cellAux = userList;
    while (cellAux->next != NULL)
    {
        cellAux = cellAux->next;
    }
    return cellAux;
}

stCell * addLast(stCell * cellList, stCell * toAdd)
{
    stCell * lastSong;
    if (!cellList)
    {
        cellList = toAdd;
    }
    else
    {
        lastSong = searchLastSong(cellList);
        cellList->next = toAdd;
    }
    return cellList;
}

stCell * addInOrderBySongName(stCell *cellList, stCell * toAdd)
{
    if (!cellList)
    {
        cellList = toAdd;
    }
    else
    {
        if (strcmpi(toAdd->userValue.title, cellList->userValue.title) < 0)
        {
            cellList = addFirst(cellList, toAdd);
        }
        else
        {
            stCell * prev = cellList;
            stCell * cellAux = cellList;
            while (cellAux && (strcmpi(toAdd->userValue.title, cellList->userValue.title) > 0))
            {
                prev = cellAux;
                cellAux = cellAux->next;
            }
            prev->next = toAdd;
            toAdd->next = cellAux;
        }
    }
}

stCell * addInOrderById(stCell *cellList, stCell * toAdd)
{
    if (!cellList)
    {
        cellList = toAdd;
    }
    else
    {
        if (toAdd->userValue.idUser < cellList->userValue.idUser)
        {
            cellList = addFirst(cellList, toAdd);
        }
        else
        {
            stCell * prev = cellList;
            stCell * cellAux = cellList;
            while (cellAux && (strcmpi(toAdd->userValue.title, cellList->userValue.title) > 0))
            {
                prev = cellAux;
                cellAux = cellAux->next;
            }
            prev->next = toAdd;
            toAdd->next = cellAux;
        }
    }
}

void showCellNode(stCell * toShow)
{
    puts("-------------------------------------------------------------------\n");
    printf("ID USUARIO: %d\n",toShow->userValue.idUser);
    printf("NOMBRE COMPLETO: %s\n"toShow->userValue.fullName);
    stWord pass = showPassword(toShow);
    printf("PASS: %s\n", pass);
    printf("Anio Nacimiento: %i\n",toShow->userValue.birthYear);
    printf("Genero: ");
    if (toShow->userValue.gender == 'f')
    {
        printf("Femenino\n");
    }
    else
    {
        printf("Masculino\n");
    }
    printf("country de origen: %s\n",toShow->userValue.country);
    printf("Cantidad de canciones escuchadas: %d\n",toShow->userValue.songPlays);
    printf("Canciones escuchadas: \n");
    showSongList(toShow->songList); ///muestra la lista de canciones del usuario

    if (toShow->userValue.off == 0)
    {
        printf("Estado: ACTIVO\n");
    }
    else
    {
        printf("Estado: INACTIVO\n");
    }
    puts("-------------------------------------------------------------------\n");
}

void showCellList(stCell * toShow) ///recursiva
{
    if (toShow)
    {
        showCellNode(toShow->userValue);
        showSongList(toShow->songList);
        showCellList(toShow->next);
    }
}
