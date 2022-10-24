#define SONGSFILEPATH "SongsFile.bin"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userLinkedList.h"




typedef struct
{
    int idSong;
    char title[30];
    char artist[20];
    int duration;
    char album[20];
    int year;
    char gender[20];
    char comment[100];
    int off; // indica 1 o 0 si la canci�n fue eliminada
} stSong;


int idClienteNuevo();
void altaDeCancion();
void bajaDeCancion();
void modificarCancion();
int consultarSiExisteCancion(char songName[]);
void listarTodasLasCanciones();

