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
stCell * addFirst(stCell * cellList, stCell * toAdd);
stCell * searchLastNode(stCell * cellList);
stCell * addLast(stCell * cellList, stCell * toAdd);
stCell * addInOrderByName(stCell * cellList, nodeListSong * toAdd);
stCell * deleteSongById(stCell * cellList, int idSong);
void showCellNode(stCell * toShow);
void showCellList(stCell * toShow);


