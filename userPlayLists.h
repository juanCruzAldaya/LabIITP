#include "userLinkedList.h"
#include "songLinkedList.h"

typedef struct
{
    stUser userValue;
    nodeListSong * songList;
    struct stCell * next;
}stCell;


stCell * inicList();
stCell * createNodePlayList(stUser toCreate);
stCell * addFirst(stCell * userList, stCell * toAdd);
stCell * searchLastNode(stCell * songList);
stCell * addLast(stCell * songList, stCell * toAdd);
stCell * addInOrderByName(stCell * songList, nodeListSong * toAdd);

void showCellNode(stCell * toShow);
void showCellList(stCell * toShow);

stCell * deleteSongById(stCell * songList, int idSong);
