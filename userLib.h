#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED
#define USERSFILEPATH "UsersFile.bin"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userLinkedList.h"


//-#################################################
//-                PARTE USUARIOS
//-#################################################
void addUserToFile();
void showUserList();
int nameValidation(char toCheck[]);
int searchUserByName(node2Player * userList,char name[]);
int totalUsers();
int searchUserById(node2Player * userList, int idUser);
node2User * loadUsersFromFile(node2User * userList);
void updateFile(node2Player * userList);
void deleteUser(node2Player * userList,int idUser);
void updateUser(node2Player,int subopciones);
stWord showPassword (stUser toShow);

///MATRICES
void showMatrix (int row, int column, int matrix[row][column]);
///muestra por pantalla cualquier matriz
void createMatrixPass (int two, int five, char pass[],  int matrixPass[two][five]);
///convierte en matriz de enteros el array de caracteres (contraseña)
int computeDeterminant (int row, int column, int matrix[row][column]);
///calcula el determinante para validar la inversion del archivo
void encryptMatrix (int two, int five,int keyPass[two][two], int decryptedMatrix[two][five], int encryptedMatrix[two][five]);
///multiplica la matriz contrasenia por la matriz testigo de cada usuario
void createKeyPass (int two, int keyPass[two][two]);
///con una semilla, crea una matriz testigo random inversible
void invertMatrix (int two, int five,int keyPass[two][two]);
///realiza operacion para invertir matriz
void decryptMatrix (int two, int five,int keyPass[two][two], int matrixPass [two][five], int decryptedMatrix[two][five]);
///con la matriz testigo y la matriz encriptada, calcula la inversa y desencripta la matriz contrasenia de cada usuario
void multiplyMatrix (int two, int five,int firstMultiple[two][two], int secondMultiple [two][five], int result[two][five]);
///realiza la operacion de multiplicar matrices entre una de 2x2 y una de 2x5 (el resultado es una de 2x5)
int checkCompatibility (int two, int five, int matrixPass[two][five], int keyPass[two][two], char toCheckPass[]);
///desencripta la matriz contrasenia, y la compara con una contrasenia ingresada convertida en matriz, retorna flag 1 si es valido
void copyMatrix (int row, int column , int copyMatrix[row][column], int originalMatrix[row][column]);
///copia una matriz en otra, para poder trabajar y guardarlas en auxiliares



#endif // USUARIOS_H_INCLUDED
