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
    int idSong;
    char title[30];
    char artist[20];
    int duration;
    char album[20];
    int year;
    char gender[20];
    char comments[100];
    int off; // indica 1 o 0 si la canción fue eliminada
} stSong;

typedef struct
{
    stSong value;
    struct songListNode * sig;
} songListNode;



typedef struct
{
    stUser user;
    songListNode * songList;
    usersList * next;
    usersList * prev;
}node2; ///LISTA ENLAZADA DE USUARIOS




usersList* startDoubleList ();
usersList* createDoubleNode (stCar value);
usersList* addFirst (usersList* doubleList, usersList* newNode);
void showDoubleList (usersList* toShow);

