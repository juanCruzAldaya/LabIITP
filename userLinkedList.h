#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userLib.h"



typedef struct
{
    int idUser;
    char name[30]; //name and lastName
    int pass[2][5]; // la pswd es una matriz que se encripta y desencripta con un key generado para c/ user.
    int birthYear;
    char gender; // (? podríamos evitar esto. qué sentido tiene en un reproductor de musica? ninguno.
    char country[20];
    int songPlays[30]; //cantidad de canciones reproducidas
    int off; // indica 1 o 0 si el cliente fue eliminado ->1  / 0 no
} stUser;





typedef struct
{
    stUser user;
    node2User * next;
    node2User * prev;
}node2User; ///LISTA ENLAZADA DE USUARIOS


void showNode(node2User * toShow);
void showList(node2User* toShow);
node2User* startDoubleList ();
node2User* createDoubleNode (stUser value);
node2User* addFirst (node2User* doubleList, node2User* newNode);
node2User * searchLastUser(node2User * userList);
node2User * addLast(node2User * userList, node2User * toAdd);
node2User * insertUser(node2User * userList, node2User * toInsert);
node2User * deleteNode(node2User * userList, int idUser);





