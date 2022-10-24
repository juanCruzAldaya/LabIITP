#include "songLinkedList.h"

nodeListSong *startSongList()
{
    return NULL;
}

nodeListSong * createSongNode (stSong toCreate)
{
    nodeListSong * songAux = (nodeListSong*)malloc(sizeof(nodeListSong));
    songAux->value = toCreate;
    songAux->next = NULL;
    return songAux;
}

nodeListSong * addFirst(nodeListSong * songsongList, nodeListSong * toAdd)
{
    if (!songsongList)
    {
        songsongList = toAdd;
    }
    else
    {
        toAdd->next = songsongList;
        songsongList = toAdd;
    }
    return songsongList;
}

nodeListSong * searchLastSong(nodeListSong * songList)
{
    nodeListSong * songAux = songList;
    while (songAux->next != NULL)
    {
        songAux = songAux->next;
    }
    return songAux;
}

nodeListSong * addLast(nodeListSong * songList, nodeListSong * toAdd)
{
    nodeListSong * lastSong;
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

nodeListSong * addInOrderBySongName(nodeListSong *songList, nodeListSong * toAdd)
{
    if (!songList)
    {
        songList = toAdd;
    }
    else
    {
        if (strcmpi(toAdd->value.title, songList->value.title) < 0)
        {
            songList = addFirst(songList, toAdd);
        }
        else
        {
            nodeListSong * prev = songList;
            nodeListSong * songAux = songList;
            while (songAux && (strcmpi(toAdd->value.title, songList->value.title) > 0))
            {
                prev = songAux;
                songAux = songAux->next;
            }
            prev->next = toAdd;
            toAdd->next = songAux;
        }
    }
}

void showNode(nodeListSong * song)
{
    printf("idSong:.. %d \n", song->value.idSong);
    printf("title:..... %s \n", song->value.title);
    printf("artist:.... %s \n", song->value.artist);
    printf("duration:... %d \n", song->value.duration);
    printf("album:...... %s \n", song->value.album);
    printf("year:....... %d \n", song->value.year);
    printf("genres:..... %s \n", song->value.genres);
    printf("comment:. %s \n", song->value.comment);
    printf("deleted:.. %c \n", song->value.deleted);
}

void showSongList(nodeListSong * toShow)
{
    if (toShow)
    {
        showNode(toShow);
        showSongList(toShow->next);
    }
}

void showBackwardsRevursive(nodeListSong *iterator)
{
    if (iterator != NULL)
    {
        showsongList(iterator->next);
        showNode(iterator);
    }
}

nodeListSong * deleteNodeById(nodeListSong * songList, int idSong)

{
    nodeListSong * next;
    nodeListSong * prev;



    if((songList) && (songList->value.idSong == idSong))
    {
        nodeListSong * auxSong = songList;
        songList = songList->next;
        free(auxSong);
    }
    else
    {
        next = songList;
        while(next) && (next->value.idSong != idSong))
        {
            prev = next;
            next = next->next;
        }

        if(next)
        {
            prev->next = next->next;
            free(next);
        }
    }
    return songList;

}

nodeSongList * deleteSongList (nodeListSong * toDelete)
{
    nodeSongList * next;
    nodeSongList * auxSong;
    auxSong = toDelete;
    while(auxSong != NULL)
    {
        next = auxSong->next;
        free(auxSong);
        auxSong =  next;
    }
    return auxSong;
}
