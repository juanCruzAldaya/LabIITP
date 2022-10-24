#define USERSPLAYLISTS "UserPlayLists.bin"
#include "ADLUsers.h"




int loadListFromFile(stCell * userList)
{
    FILE * fileUser;
    nodeSongList * auxSongList;
    stUser userAux;
    stCell * userList;
    fileUser = fopen(USERSFILEPATH,"rb");
    if(fileUser)
    {
        while(!feof(fileUser))
        {
            fread(&userAux,1,sizeof(stUser),fileUser);

            ///PARA BUSCAR CANCIONES X ID, ES MEJOR HACERLO MEDIANTE EL ARBOL AL SER MAS OPTIMO PARA ESO
            ///UNA VEZ CON LA LIBRERIA DE ARBOL, AGREGAR QUE ACÁ A LA LISTA DE USER

            ///MIENTRAS USERAUX->SONGPLAYED != 0
            ///ALGORITMO DE BUSQUEDA DE CANCION X ID QUE DEVUELVA STSONG DEL ID ACTUAL -> Y ACA CREAR NODO SONG
            ///SONG LIST = CARGA EL NODO EN LA LISTA
            ///USERAUX->SONGPLAYED[i++];

            userList = addUserToList(userList,auxSongList); ///ACA PASA LA LISTA CARGADA ARRIBA DE CANCIONES ESCUCHADAS X EL USER
        }
    }
    else
    {
        printf("error en abrir el archivo!\n");
    }
    return validos;

}


stCell * createCellUser()
{
    stCell * userCellAux;
    stUser userAux;
    userAux = createOneUser();
    userCellAux->userValue = userAux;
    userCellAux->songList = startSongList();
    userCellAux->next = NULL;
    return userCellAux;
}

stCell * addUserToList(stCell * userList,nodeSongList * songList, stUser toAdd)
{
    stCell * userAux;
    userAux = createCellNode(toAdd, songList);
    if(userList)
    {
        userList = addLast(userList,toAdd);
    }
    auxUser->songList = songList;
    return auxUser;
}

stCell * searchUserById(stCell * userList, int idUser)
{
    stCell * userAux = NULL;
    while (userList)
    {
        if(userList->userValue.idUser == idUser)
            userAux = userList;
        userList = userList->next;
    }
    return userAux;
}


void showUserPlaylists (stCell * userList)
{
    printf("\nMostrando el ADL de usuarios \n");
    if (userList)
    {
        showCellList(userList);
    }
    else
        printf("There is nothing to show\n");
}

stCell * addSongToUser(stCell * userList, int idUser, stSong toAdd)
{
    nodeSongList * auxSong = createSongNode(toAdd);
    stCell * auxUser;
    auxUser = searchUserById(userList, idUser);
    if(auxUser)
    {
        auxUser->songList = addLast(auxUser->songList, auxSong);
    }
    return userList;
}

