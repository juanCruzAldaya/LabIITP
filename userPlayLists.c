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

stCell * searchLastCell(stCell * songList)
{
    stCell * cellAux = songList;
    while (cellAux->next != NULL)
    {
        cellAux = cellAux->next;
    }
    return cellAux;
}

stCell * addLast(stCell * songList, stCell * toAdd)
{
    stCell * lastSong;
    if (!songList)
    {
        songList = toAdd;
    }
    else
    {
        lastSong = searchLastSong(songList);
        lastSong->next = toAdd;
    }
    return songList;
}

stCell * addInOrderBySongName(stCell *songList, stCell * toAdd)
{
    if (!songList)
    {
        songList = toAdd;
    }
    else
    {
        if (strcmpi(toAdd->userValue.title, songList->userValue.title) < 0)
        {
            songList = addFirst(songList, toAdd);
        }
        else
        {
            stCell * prev = songList;
            stCell * cellAux = songList;
            while (cellAux && (strcmpi(toAdd->userValue.title, songList->userValue.title) > 0))
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
        showCellList(toShow->next);
    }
}


nodeSongList * deleteNodeByIdSong(stCell *songList, int ID)
{
    stCell *aux = inicsongList();
    if (songList != NULL)
    {
        if (songList->userValue.idSong == ID)
        {
            stCell * deletedNode = songList;
            songList = songList->next;
            free(deletedNode);
        }
        else
        {
            songList->next = deleteNodeByIdSong(songList->next, ID);
        }
    }
}

