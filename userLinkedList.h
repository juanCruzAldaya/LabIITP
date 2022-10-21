#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//*****************************************************
//-----------------------------------------------------
//ESTRUCTURAS DE USUARIOS
//-----------------------------------------------------
typedef struct
{
    int idUser;
    char fullName[30];
    int keyPass[2][2]; ///matriz testigo / encriptadora / unica de c/user
    int matrixPass[2][5]; ///matriz que ingresa el usuario char convertido y almacenado en matriz de 2x2
    int birthYear;
    char gender;
    char country[20];
    int songsPlayed[30]; ///IDs de canciones reproducidas por el user
    int totalSongsPlayed; ///valitwo de songsPlayed
    int off; ///flag 0 = activo. 1 = off
    int admin; ///flag 0 = user random. 1 = user admin
}stUser;

typedef struct
{
    stUser value;
    struct node2User* next;
    struct node2User * prev;
}node2User;  ///al momento de pasar el archivo a la colección, vuelca los usuarios en notwo de lista doblemente enlazada

typedef struct
{
    char word[11]; ///struct que permite en una funcion retornar una palabra
}stWord;


void showNode(node2User * toShow);
void showList(node2User* toShow);
node2User* startDoubleList ();
node2User* createDoubleNode (stUser value);
node2User* addFirst (node2User* doubleList, node2User* newNode);
node2User * searchLastUser(node2User * userList);
node2User * addLast(node2User * userList, node2User * toAdd);
node2User * insertUser(node2User * userList, node2User * toInsert);
node2User * deleteNode(node2User * userList, int idUser);
