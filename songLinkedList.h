#include "songLib.h"

typedef struct
{
    stSong value;
    struct nodeListSong * next;
}nodeListSong;


nodeListSong * startSongList();
nodeListSong * createNodoList(stSong toCreate);
nodeListSong * addFirst(nodeListSong * songList, nodeListSong * toAdd);
nodeListSong * searchLastNode(nodeListSong * songList);
nodeListSong * addLast(nodeListSong * songList, nodeListSong * toAdd);
nodeListSong * addInOrderByName(nodeListSong * songList, nodeListSong * toAdd);
void showNode(nodeListSong * toShow);
void showSongList(nodeListSong * toShow)
void showBackwardsRevursive(nodeListSong * iterator);
nodeListSong * deleteSongById(nodeListSong * songList, int idSong);
