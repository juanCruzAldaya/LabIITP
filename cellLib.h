#include "userPlayLists.h"


stCell * loadListFromFile(stCell * userList);
stCell * createCellUser();
stCell * addUserToList(stCell * userList, nodeSongList * songList, stUser toAdd);
stCell * searchUserById(stCell * userList, int idUser);
stCell * addSongToUser(stCell * userList, int idUser, stSong toAdd);
stCell * clearSongList (stCell * cellList, int idUser);
void showUserPlaylists (stCell * userList);




