#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h> ///me deja utilizar la funcion sleep
#define USERSFILEPATH "UsersFile.bin"

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
    int deleted; // indica 1 o 0 si la cancion fue eliminada
} stSong;

typedef struct
{
    int idUser;
    char fullName[30];
    int keyPass[2][2];    /// matriz testigo / encriptadora / unica de c/user
    int matrixPass[2][5]; /// matriz que ingresa el usuario char convertido y almacenado en matriz de 2x2
    int birthYear;
    char gender;
    char country[20];
    int songsPlayed[30];  /// IDs de canciones reproducidas por el user
    int totalSongsPlayed; /// valitwo de songsPlayed
    int off;              /// flag 0 = activo. 1 = off
    int admin;            /// flag 0 = user random. 1 = user admin
} stUser;

typedef struct
{
    stSong value;
    struct nodeListSong *next;
} nodeListSong;

typedef struct
{
    stUser user;
    struct node2User *next;
    struct node2User *prev;
} node2User;

typedef struct
{
    int idPlaylist;
    int idUser;
    int idSong;
} stPlaylist;

typedef struct
{
    stSong value;
    struct nodeTreeSong *left;
    struct nodeTreeSong *right;
} nodeTreeSong;

typedef struct
{
    char word[11]; /// struct que permite en una funcion retornar una palabra
} stWord;

//-#################################################
//-                PARTE USUARIOS
//-#################################################
void addUserToFile();
int nameValidation(char toCheck[]);
int totalUsers();
int searchUserByName(char fullName[]);
int searchUserById(int idUser);
node2User *loadUsersFromFile(node2User *userList);
void updateFile(node2User *userList);
int deleteUser(int idUser);
void updateUser(int idUser);
stWord showPassword(stUser toShow);
stUser createOneUser();

/// MATRICES
void showMatrix(int row, int column, int matrix[row][column]);
/// muestra por pantalla cualquier matriz
void createMatrixPass(int two, int five, char pass[], int matrixPass[two][five]);
/// convierte en matriz de enteros el array de caracteres (contraseÃ±a)
int computeDeterminant(int row, int column, int matrix[row][column]);
/// calcula el determinante para validar la inversion del archivo
void encryptMatrix(int two, int five, int keyPass[two][two], int decryptedMatrix[two][five], int encryptedMatrix[two][five]);
/// multiplica la matriz contrasenia por la matriz testigo de cada usuario
void createKeyPass(int two, int keyPass[two][two]);
/// con una semilla, crea una matriz testigo random inversible
void invertMatrix(int two, int five, int keyPass[two][two]);
/// realiza operacion para invertir matriz
void decryptMatrix(int two, int five, int keyPass[two][two], int matrixPass[two][five], int decryptedMatrix[two][five]);
/// con la matriz testigo y la matriz encriptada, calcula la inversa y desencripta la matriz contrasenia de cada usuario
void multiplyMatrix(int two, int five, int firstMultiple[two][two], int secondMultiple[two][five], int result[two][five]);
/// realiza la operacion de multiplicar matrices entre una de 2x2 y una de 2x5 (el resultado es una de 2x5)
int checkCompatibility(int two, int five, int matrixPass[two][five], int keyPass[two][two], char toCheckPass[]);
/// desencripta la matriz contrasenia, y la compara con una contrasenia ingresada convertida en matriz, retorna flag 1 si es valido
void copyMatrix(int row, int column, int copyMatrix[row][column], int originalMatrix[row][column]);
/// copia una matriz en otra, para poder trabajar y guardarlas en auxiliares

/// FUNCIONES PARA LISTA SIMPLE DE CANCIONES
nodeListSong *inicList();
nodeListSong *createNodeList(stSong song);
nodeListSong *addToBegin(nodeListSong *list, nodeListSong *new);
nodeListSong *searchLastNode(nodeListSong *list);
nodeListSong *addToEnd(nodeListSong *list, nodeListSong *new);
nodeListSong *addInOrderBySongName(nodeListSong *list, nodeListSong *newNode);
void showNodenodeListSong(nodeListSong *song);
void showList(nodeListSong *iterator);
void showBackwardsRevursive(nodeListSong *iterator);
nodeListSong *deleteNodeByIdSong(nodeListSong *list, int ID);

/// FUNCIONES stSong
int idClienteNuevo(char archivo[]);
void altaDeCancion(char archivo[]);
void bajaDeCancion(char archivo[]);
void modificarCancion(char archivo[]);
int consultarSiExisteCancion(char archivo[], char tituloCancion[]);
void listarTodasLasCanciones(char archivo[]);

/// FUNCIONES PARA NODOARBOLCANCION
nodeTreeSong *startTree();
nodeTreeSong *createNodeTree(stSong song);
nodeTreeSong *insertNodeTree(nodeTreeSong *tree, stSong song);
void showNodenodeTreeSong(nodeTreeSong *song);
void inorder(nodeTreeSong *tree);
void preorder(nodeTreeSong *tree);
void postorder(nodeTreeSong *tree);
nodeTreeSong *searchNodeByNodeID(nodeTreeSong *tree, int idSong);
nodeTreeSong *deleteNode(nodeTreeSong *tree, int idSong);
void toFile(char fileName[], stSong song[]);
int countRegist(char fileName[]);
nodeTreeSong *insertFromArray(stSong array[], nodeTreeSong *tree, int valid, int middleArray);
nodeTreeSong *fileToTree(char fileName[], nodeTreeSong *tree);

int main()
{
    char usuario[20];
    char password[20];

    printf("\t MENU PRINCIPAL \n");
    printf("\t1. Ingreso con User y Pass para administradores\n");
    printf("\t2. Ingreso con User y Pass para usuarios\n");
    printf("\t3. Registrarse\n");

    // altaDeCancion("canciones.bin");
    listarTodasLasCanciones("canciones.bin");

    return 0;
}

int idClienteNuevo(char archivo[])
{
    FILE *archivito;
    archivito = fopen(archivo, "rb");
    int i = 0;
    if (archivito != NULL)
    {
        fseek(archivito, sizeof(stSong), SEEK_END);
        i = ftell(archivito) / sizeof(stSong);
    }
    else
    {
        printf("ERROR de datos - El archivo no pudo ser abierto");
    }
    return i++;
}

void altaDeCancion(char archivo[])
{
    stSong cancion;
    FILE *archivito;
    archivito = fopen(archivo, "ab");

    if (archivito != NULL)
    {
        cancion.idSong = idClienteNuevo(archivo);

        printf("Ingrese titulo: ");
        fflush(stdin);
        gets(cancion.title);

        printf("Ingrese artista: ");
        fflush(stdin);
        gets(cancion.artist);

        printf("Ingrese duracion: ");
        fflush(stdin);
        scanf("%i", &cancion.duration);

        printf("Ingrese album: ");
        fflush(stdin);
        gets(cancion.album);

        printf("Ingrese anio: ");
        fflush(stdin);
        scanf("%i", &cancion.year);

        printf("Ingrese genero: ");
        fflush(stdin);
        gets(cancion.gender);

        printf("Ingrese comentario: ");
        fflush(stdin);
        gets(cancion.comment);

        cancion.deleted = 0;

        fwrite(&cancion, sizeof(stSong), 1, archivito);
        fclose(archivito);
    }
    else
    {
        printf("ERROR de datos - El archivo no pudo ser abierto");
    }
}

void bajaDeCancion(char archivo[])
{
    stSong cancion;
    FILE *archivito;
    archivito = fopen(archivo, "r+b");
    int aux = 0;
    char ok = 's';
    char idBaja;

    printf("Ingrese el ID de la cancion que quiere dar de baja\n");
    fflush(stdin);
    scanf("%d", idBaja);

    if (archivito != NULL && ok == 's')
    {
        while (aux == 0 && (fread(&cancion, sizeof(stSong), 1, archivito) > 0))
        {

            if (cancion.idSong == idBaja)
            {
                cancion.deleted = 0;
                fseek(archivito, (-1) * sizeof(stSong), SEEK_CUR);
                fwrite(&cancion, sizeof(stSong), 1, archivito);
                aux = 1;
            }
        }
    }
    else
    {
        printf("ERROR de datos - El archivo no pudo ser abierto");
    }
    fclose(archivito);
}

void modificarCancion(char archivo[])
{
    stSong cancion;
    FILE *archivito;
    archivito = fopen(archivo, "r+b");
    int id;
    int eleccion;

    printf("Ingrese ID de la cancion:\n");
    scanf("%d", &id);
    system("cls");

    puts("Opcion 1 - titulo");
    puts("Opcion 2 - artista");
    puts("Opcion 3 - duracion");
    puts("Opcion 4 - album");
    puts("Opcion 5 - anio");
    puts("Opcion 6 - genero");
    puts("Opcion 7 - comentario");
    puts("Opcion 8 - eliminado");

    printf("Ingrese eleccion:\n");
    scanf("%d", &eleccion);
    system("cls");
}

int consultarSiExisteCancion(char archivo[], char tituloCancion[])
{
    FILE *archivito;
    stSong cancion;
    archivito = fopen(archivo, "rb");
    int resultado = 1;

    if (archivito != NULL)
    {
        while (fread(&cancion, sizeof(stSong), 1, archivito) > 0)
        {
            resultado = strcmp(cancion.title, tituloCancion);

            if (resultado == 0)
            {
                printf("Ya existe cancion\n");
            }
        }
    }
    return resultado;
}

void listarTodasLasCanciones(char archivo[])
{
    FILE *archivito;
    stSong song;
    archivito = fopen(archivo, "rb");
    int i = 0;

    if (archivito != NULL)
    {
        while (fread(&song, sizeof(stSong), 1, archivito) > 0)
        {
            printf("\n Registro numero %d", i++);
            puts("\n-------------------------------------");
            printf("\n IdCancion:.......... %d", song.idSong);
            printf("\n Titulo:............. %s", song.title);
            printf("\n Artista:............ %s", song.artist);
            printf("\n Duracion:........... %i", song.duration);
            printf("\n Album:.............. %s", song.album);
            printf("\n Anio:............... %d", song.year);
            printf("\n Genero:............. %s", song.gender);
            printf("\n Comentario:......... %s", song.comment);
            printf("\n Eliminado 1-Si/0-No: %d", song.deleted);
            puts("\n-------------------------------------");
        }
    }
    fclose(archivito);
}

nodeListSong *inicList()
{
    return NULL;
}

nodeListSong *createNodeList(stSong song)
{
    nodeListSong *nodito = (nodeListSong *)malloc(sizeof(nodeListSong));
    nodito->value = song;
    nodito->next = inicList();
    return nodito;
}

nodeListSong *addToBegin(nodeListSong *list, nodeListSong *new)
{
    if (list == NULL)
    {
        list = new;
    }
    else
    {
        new->next = list;
        list = new;
    }
    return list;
}

nodeListSong *searchLastNode(nodeListSong *list)
{
    nodeListSong *aux = list;
    while (aux->next != NULL)
    {
        aux = aux->next;
    }
    return aux;
}

nodeListSong *addToEnd(nodeListSong *list, nodeListSong *new)
{
    nodeListSong *ultimo;
    if (list == NULL)
    {
        list = new;
    }
    else
    {
        ultimo = searchLastNode(list);
        ultimo->next = new;
    }
    return list;
}

nodeListSong *addInOrderBySongName(nodeListSong *list, nodeListSong *nuevoNodo)
{
    if (list == NULL)
    {
        list = nuevoNodo;
    }
    else
    {
        if (strcmpi(nuevoNodo->value.title, list->value.title) < 0)
        {
            list = addToBegin(list, nuevoNodo);
        }
        else
        {
            nodeListSong *ante = list;
            nodeListSong *aux = list;
            while (aux != NULL && strcmpi(nuevoNodo->value.title, list->value.title) > 0)
            {
                ante = aux;
                aux = aux->next;
            }
            ante->next = nuevoNodo;
            nuevoNodo->next = aux;
        }
    }
}

void showNodenodeListSong(nodeListSong *song)
{
    printf("idSong:..... %d \n", song->value.idSong);
    printf("title:...... %s \n", song->value.title);
    printf("artist:..... %s \n", song->value.artist);
    printf("duration:... %d \n", song->value.duration);
    printf("album:...... %s \n", song->value.album);
    printf("year:....... %d \n", song->value.year);
    printf("gender:..... %s \n", song->value.gender);
    printf("comment:.... %s \n", song->value.comment);
    printf("deleted:.... %c \n", song->value.deleted);
}

void showList(nodeListSong *iterator)
{
    if (iterator != NULL)
    {
        showNodenodeListSong(iterator);
        showList(iterator->next);
    }
}

void showBackwardsRevursive(nodeListSong *iterator)
{
    if (iterator != NULL)
    {
        showList(iterator->next);
        showNodenodeListSong(iterator);
    }
}

nodeListSong *deleteNodeByIdSong(nodeListSong *list, int ID)
{
    nodeListSong *aux = inicList();
    if (list != NULL)
    {
        if (list->value.idSong == ID)
        {
            nodeListSong *deletedNode = list;
            list = list->next;
            free(deletedNode);
        }
        else
        {
            list->next = deleteNodeByIdSong(list->next, ID);
        }
    }
}

nodeTreeSong *startTree()
{
    return NULL;
}

nodeTreeSong *createNodeTree(stSong song)
{
    nodeTreeSong *aux = (nodeTreeSong *)malloc(sizeof(nodeTreeSong));
    aux->value = song;
    aux->left = NULL;
    aux->right = NULL;
    return aux;
}

nodeTreeSong *insertNodeTree(nodeTreeSong *tree, stSong song)
{
    if (tree == NULL)
    {
        tree = createNodeTree(song);
    }
    else
    {
        if (song.idSong > tree->value.idSong)
        {
            tree->right = insertNodeTree(tree->right, song);
        }
        else
        {
            tree->left = insertNodeTree(tree->left, song);
        }
    }
    return tree;
}

void showNodenodeTreeSong(nodeTreeSong *song)
{
    printf("idSong:..... %d \n", song->value.idSong);
    printf("title:...... %s \n", song->value.title);
    printf("artist:..... %s \n", song->value.artist);
    printf("duration:... %d \n", song->value.duration);
    printf("album:...... %s \n", song->value.album);
    printf("year:....... %d \n", song->value.year);
    printf("gender:..... %s \n", song->value.gender);
    printf("comment:.... %s \n", song->value.comment);
    printf("deleted:.... %c \n", song->value.deleted);
}

void inorder(nodeTreeSong *tree)
{
    if (tree != NULL)
    {
        inorder(tree->left);
        showNodenodeTreeSong(tree);
        inorder(tree->right);
    }
}

void preorder(nodeTreeSong *tree)
{
    if (tree != NULL)
    {
        showNodenodeTreeSong(tree);
        preorder(tree->left);
        preorder(tree->right);
    }
}

void postorder(nodeTreeSong *tree)
{
    if (tree != NULL)
    {
        postorder(tree->left);
        postorder(tree->right);
        showNodenodeTreeSong(tree);
    }
}

nodeTreeSong *searchNodeByNodeID(nodeTreeSong *tree, int idSong)
{
    nodeTreeSong *res = NULL;
    if (tree != NULL)
    {
        if (idSong == tree->value.idSong)
            res = tree;
        else if (idSong > tree->value.idSong)
            res = searchNodeByNodeID(tree->right, idSong);
        else
            res = searchNodeByNodeID(tree->left, idSong);
    }
    return res;
}

nodeTreeSong *deleteNode(nodeTreeSong *tree, int idSong)
{
    if (tree != NULL)
    {
        nodeTreeSong *resId = searchNodeByNodeID(tree, idSong);

        if (idSong == resId)
        {
            free(tree);
            tree = NULL;
        }
    }
    return tree;
}

void toFile(char fileName[], stSong song[])
{
    FILE *file;
    file = fopen(fileName, "rb");
    stSong s;
    int i = 0;
    if (file != NULL)
    {
        while (!feof(file))
        {
            fread(&s, sizeof(stSong), 1, file);
            if (!feof(file))
            {
                song[i] = s;
                i++;
            }
        }
    }
}

int countRegist(char fileName[])
{
    FILE *file;
    file = fopen(fileName, "rb");
    stSong song;
    int i = 0;
    if (file != NULL)
    {
        while (!feof(file))
        {
            fread(&song, sizeof(stSong), 1, file);
            if (!feof(file))
            {
                i++;
            }
        }
    }
    return i;
}

nodeTreeSong *insertFromArray(stSong array[], nodeTreeSong *tree, int valid, int middleArray)
{
    int i = 0;
    srand(time(NULL));
    while (i < valid)
    {
        if (tree == NULL)
        {
            tree = insertNodeTree(tree, array[middleArray]);
        }
        else
        {
            tree = insertNodeTree(tree, array[rand() % valid]);
        }
        i++;
    }
    return tree;
}

int middleArray(int valid)
{
    int var;
    if (valid % 2 == 0)
    {
        var = valid / 2;
    }
    else
    {
        valid++;
        var = valid / 2;
    }
    return var;
}

nodeTreeSong *fileToTree(char fileName[], nodeTreeSong *tree)
{
    int var = countRegist(fileName);
    stSong array[var];
    toFile(fileName, array);
    int mide = middleArray(var);
    tree = insertFromArray(array, tree, var, mide);
}

void addUserToFile()
{
    FILE *userFile;
    stUser userAux;
    userFile = fopen(USERSFILEPATH, "ab");
    if (!userFile)
    {
        printf("Error en crear el fileUser / ruta invalida \n");
    }
    else
    {
        userAux = createOneUser();
        fwrite(&userAux, sizeof(stUser), 1, userFile);
        printf("Se ha registrado correctamente el userAux\n");
        fclose(userFile);
    }
}

stUser createOneUser()
{
    stUser userAux;
    int idUser = totalUsers(USERSFILEPATH); /// funcion que trae cantidad de userAuxs cargados en el fileUservo y autoinrementa 1
    int iterator = 0;
    int resnameValidation = 0;

    char passAux[11];        /// auxiliar de contrasenia
    char passAux1[11];       /// auxiliar de verificacion de contraseña
    int decryptedPass[2][5]; /// cambia la contraseña q ingresa el userAux a una matriz de enteros
    int keyPass[2][2];       /// matriz encriptadora
    int encryptedPass[2][5]; /// matriz Encriptada

    // CARGA DE 1 userAux POR TECLADO
    printf("Ingrese el nombre comnpleto del USER (maximo 30 caracteres)\n");
    fflush(stdin);
    gets(userAux.fullName);
    // VALIDO SI EL NOMBRE DE userAux YA EXISTE
    resnameValidation = nameValidation(userAux.fullName);
    while (resnameValidation == 0)
    {
        printf("El nombre ya existe\n");
        printf("Ingrese otro\n");
        fflush(stdin);
        gets(userAux.fullName);
        resnameValidation = nameValidation(userAux.fullName); // VALIDO NUEVAMENTE EL NOMBRE
    }

    do
    {
        system("cls");
        printf("Ingrese una contrasenia (10 caracteres obligatoriamente):\n");
        gotoxy(30, 21);
        fflush(stdin);
        gets(passAux);
        getch();
        gotoxy(30, 22);
        printf("Una vez mas por favor :) \n");
        gotoxy(30, 23);
        fflush(stdin);
        gets(passAux1);
        getch();
    } while (strcmpi(passAux, passAux1) != 0);

    while (strlen(passAux) != (10 * sizeof(char)))
    {
        system("cls");
        gotoxy(30, 20);
        printf("Recuerde la contrasenia debe tener 10 caracteres, ingrese otra por favor:\n");
        gotoxy(30, 21);
        gets(passAux);
        getch();
    }

    createMatrixPass(2, 5, passAux, decryptedPass);             /// pasa pswd a matriz de enteros
    createKeyPass(2, keyPass);                                  /// crea matriz testigo
    copyMatrix(2, 2, userAux.keyPass, keyPass);                  /// copia la matriz encriptadora del userAux en su campo del userAux
    encryptMatrix(2, 5, keyPass, decryptedPass, encryptedPass); /// encripta la contraseña
    copyMatrix(2, 5, userAux.matrixPass, encryptedPass);         /// fileUserva la contrasenia encriptada en el campo pass de userAux

    printf("Ingrese anio de nacimiento\n");
    scanf("%d", &userAux.birthYear);

    printf("Ingrese Genero\n");
    printf("M: Masculino\n");
    printf("F: Femenino\n");
    printf("X: Otro");
    fflush(stdin);
    gets(&userAux.gender);

    printf("Ingrese pais del userAux\n");
    fflush(stdin);
    gets(userAux.country);

    userAux.off = 0;

    userAux.songsPlayed = 0;

    while (iterator < 30)
    {
        userAux.songsPlayed[iterator] = -1;
        iterator++;
    }

    return userAux;
}

//-----------------------------------------------------
// A.1)FUNCION ADICIONAL QUE VALIDA SI EL USER EXISTE
//-----------------------------------------------------

int nameValidation(char toCheck[])
{
    int flag = 0;
    flag = searchUserByName(toCheck);
    return flag;
}

//-----------------------------------------------------
// FUNCION BAJA DE userAuxS (INACTIVIDAD) REGISTRADOS EN EL fileUser /
//-----------------------------------------------------

int deleteUser(int idUser) /// Si el userAux fue elimiinado con exito devuelve 1, en caso de error devuelve 0;
{
    FILE *userFIle = fopen(USERSFILEPATH, "r+b");
    int pos = 0, flag = 0;
    stUser userAux;
    if (userFIle)
    {
        pos = searchUserById(idUser);                 /// busco la pos del user en el archivo por id.
        fseek(userFIle, pos * sizeof(stUser), 0);     /// busco en el archivo
        fread(&userAux, sizeof(stUser), 1, userFIle); /// escribo en el aux de persona
        userAux.off = 1;
        flag = 1;
    }
    fclose(userFIle);
    return flag;
}

//-----------------------------------------------------
// C)FUNCION BAJA DE userAuxS (INACTIVIDAD) REGISTRADOS EN EL fileUser
//-----------------------------------------------------

/// TODO
/* void deleteUser(node2User * userList, int idUser)
{
    char respuesta = 'y';
    system("pause");
    system("cls");
    printf("Nombre del userAux %s:\n", userAux[pos].nombreuserAux);
    printf("Esta seguro que quiere eliminar el userAux ID: %d ? Y/N \n", userAux[pos].IduserAux);
    fflush(stdin);
    gets(&respuesta);
    while ((respuesta != 'y') && (respuesta != 'n'))
    {
        system("cls");
        printf("Opcion incorrecta!!\n");
        printf("Por favor reingrese la opcion!\n");
        printf("Nombre del userAux %s:\n", userAux[pos].nombreuserAux);
        printf("Esta seguro que quiere eliminar el userAux ID: %d ? Y/N \n", userAux[pos].IduserAux);
        fflush(stdin);
        gets(&respuesta);
    }
    if (respuesta == 'y')
    {
        userAux[pos].eliminado = 1;
        mostrarunuserAux(userAux, pos);
        ActualizarfileUser(USERSFILEPATH, userAux, validos);
        printf("userAux Inactivo!\n");
    }
    if (respuesta == 'n')
    {
        userAux[pos].eliminado = 0;
        mostrarunuserAux(userAux, pos);
        ActualizarfileUser(USERSFILEPATH, userAux, validos);
        printf("No se dio de baja el userAux!\n");
    }
} */

//--------------------------------------------------
// D)FUNCION QUE BUSCA UN userAux POR ID O POR NOMBRE
//--------------------------------------------------
// D.1)FUNCION ADICIONAL PASAR LOS userAuxS GUARDADOS DEL fileUser A UNA ESTRUCTURA
//----------------------------------------------------------------------------

node2User *loadUsersFromFile(node2User *userList)
{
    FILE *fileUser;
    node2User *auxNode;
    stUser aux;
    fileUser = fopen(USERSFILEPATH, "rb");

    if (fileUser)
    {
        node2User *seg = userList;
        while ((fread(&aux, sizeof(stUser), 1, fileUser) > 0))
        {
            auxNode = createNode(aux);
            addLast(seg, auxNode);
            seg = seg->next;
        }
        fclose(fileUser);
    }
    else
    {
        printf("El fileUser no existe / error de lectura!!\n");
    }

    return userList;
}

void showUsers(node2User *userList)
{
    userList = loadUsersFromFile(userList);
    showUserList(userList);
}

//-----------------------------------
// D.2)FUNCION QUE BUSCA USER POR ID
//-----------------------------------
int searchUserById(int idUser)
{
    FILE *fileUser = fopen(USERSFILEPATH, "rb");
    int pos = 0, iterator = 0, flag = 0;
    stUser userAux;
    if (fileUser)
    {
        while (!feof(fileUser) && flag == 0)
        {
            fread(&userAux, sizeof(stUser), 1, fileUser);
            if (!feof(fileUser))
            {
                if (idUser == userAux.idUser)
                {
                    pos = iterator;
                    flag = 1;
                }
                else
                {
                    iterator++;
                }
            }
        }
    }
    fclose(fileUser);
    return pos;
}

int searchUserByName(char fullName[])
{
    FILE *fileUser = fopen(USERSFILEPATH, "rb");
    int pos = 0, iterator = 0, flag = 0;
    stUser userAux;
    if (fileUser)
    {
        while (!feof(fileUser) && flag == 0)
        {
            fread(&fileUser, sizeof(stUser), 1, fileUser);

            if (!feof(fileUser))
            {
                if (strcmpi(userAux.fullName, fullName) == 0)
                {
                    pos = iterator;
                    flag = 1;
                }
                else
                {
                    iterator++;
                }
            }
        }
    }
    fclose(fileUser);
    return pos;
}

//-----------------------------------------------
//------------------------------------------------
// D.4)FUNCION QUE RETORNA LA  CANTIDAD DE REGISTROS VALIDOS EN EL fileUser
//------------------------------------------------
int totalUsers(char userFile[])
{
    int cantidad = 0;
    FILE *fileUser;
    stUser userAuxAux;
    fileUser = fopen(USERSFILEPATH, "rb");
    if ((fileUser) != NULL) // EN CASO DE DAR OK EN LA LECTURA DEVUELVE LA CANTIDAD EXACTA DE userAuxS EN EL fileUser
    {
        while (fread(&userAuxAux, sizeof(stUser), 1, fileUser) > 0)
        {
            cantidad++;
        }
        fclose(fileUser);
    }
    if ((fileUser) == NULL) // EN CASO DE DAR ERROR DEVUELVE COMO CANTIDAD 0 YA QUE NO EXISTE EL fileUser
    {
        cantidad = 0;
    }
    return cantidad;
}
//-***************************************************************************************
// FUNCION DE ACTUALIZACION DE userAuxS
//------------------------------------------
void updateFile(node2User *userList)
{
    int i = 0;
    FILE *fileUser;
    fileUser = fopen(USERSFILEPATH, "wb");
    if (fileUser)
    {
        while (userList)
        {
            fwrite(&userList->user, sizeof(stUser), 1, fileUser);
            userList = userList->next;
        }
        fclose(fileUser);
    }
}

//---------------------------------------
// FUNCION QUE MODIFICA UN userAux
//----------------------------------------

void updateUser(int idUser)
{
    FILE *fileUser = fopen(USERSFILEPATH, "r+b");
    stUser userAux;
    int keyPass[2][2];
    int decryptedMatrix[2][5];
    int encryptedMatrix[2][5];
    char passAux[15];
    int fieldOption = 0;
    char newName[20];
    int posInFile = searchUserById(fileUser, idUser);

    if (fileUser)
    {
        fseek(fileUser, posInFile * sizeof(stUser), 0);
        fread(&userAux, sizeof(stUser), 1, fileUser);

        if (idUser == userAux.idUser)
        {
            do
            {
                printf("\n1.Nombre de usuario: %s", userAux.idUser);
                printf("\n2.Pass: %s", showPassword(userAux));
                printf("\n3.Nacimiento: %d", userAux.birthYear);
                printf("\n4.Genero: %c", userAux.gender);
                printf("\n5.Pais: %s", userAux.country);

                printf("\n\nEscriba el numero del campo que desea modificar o 6 para salir :");
                scanf("%d", &fieldOption);

                switch (fieldOption)
                {
                case 1:
                    printf("Ingrese nuevo nombre: ");
                    fflush(stdin);
                    gets(newName);
                    if (nameValidation(newName) == 0)
                    {
                        strcpy(userAux.fullName, newName);
                    }
                    else
                    {
                        printf("\nEl nombre elegido ya esta en uso.");
                    }
                    break;

                case 2:
                    printf("\nIngrese Pass: ");
                    fflush(stdin);
                    gets(passAux);
                    createMatrixPass(2, 5, passAux, decryptedMatrix);
                    encryptMatrix(2, 5, userAux.keyPass, decryptedMatrix, encryptedMatrix);
                    copyMatrix(2, 5, userAux.matrixPass, encryptedMatrix);
                    break;

                case 3:
                    printf("\nIngrese anio de nacimiento:");
                    scanf("%d", &userAux.birthYear);
                    break;

                case 4:
                    printf("\nIngrese genero:");
                    fflush(stdin);
                    scanf("%c", &userAux.gender);
                    break;

                case 5:
                    printf("\nIngrese pais:");
                    fflush(stdin);
                    gets(userAux.country);
                    break;
                }

            } while (fieldOption != 6);

            fseek(fileUser, posInFile * sizeof(stUser), 0);
            fwrite(&userAux, sizeof(stUser), 1, fileUser);
            fclose(fileUser);
        }
        else
        {
            printf("El usuario no existe \n");
        }
    }
}
    /// FUNCION QUE CARGA LOS ID DE PELICULAS EN UN userAux DETERMINADO
/* void cargaIDpelisauserAux(stUser userAux[], int pos, int pospeli)
{
    int i = 0;
    int flag = 0;
    while ((i < 30) && (flag == 0))
    {
        if ((userAux[pos].peliculasVistas[i]) == -1)
        {
            userAux[pos].peliculasVistas[i] = pospeli;
            flag = 1;
        }
        i++;
    }
} */

/// FUNCION DE PRUEBA QUE MUESTRA LOS ID DE LAS PELICULAS GUARDADAS EN UN userAux DETERMINADO
/* void mostrarIDpelisauserAux(stuserAux userAux[], int pos)
{
    int i = 0;
    int flag = 0;
    printf("PElICULAS VISTAS!\n");
    while ((i < 30))
    {
        if ((userAux[pos].peliculasVistas[i]) != -1)
        {
            printf("%d\n", userAux[pos].peliculasVistas[i]);
        }
        i++;
    }
} */

/// MATRICES

void showMatrix(int row, int column, int matrix[row][column])
{
    int i;
    int u;
    int aux;

    for (i = 0; i < row; i++)
    {
        for (u = 0; u < column; u++)
        {
            printf("[%d] ", matrix[i][u]);
        }
        printf("\n");
    }
}

void multiplyMatrix(int two, int five, int firstMultiple[two][two], int secondMultiple[two][five], int result[two][five])
{

    int i = 0;
    int u;
    int q = 1;

    for (u = 0; u < five; u++)
    {
        result[i][u] = (firstMultiple[i][i] * secondMultiple[i][u]) + (firstMultiple[i][q] * secondMultiple[q][u]);

        result[q][u] = (firstMultiple[q][i] * secondMultiple[i][u]) + (firstMultiple[q][q] * secondMultiple[q][u]);
    }
}

void createMatrixPass(int two, int five, char pass[], int matrixPass[two][five])
{
    int iterator = 0;
    int j;
    int k;

    for (j = 0; j < 2; j++)
    {
        for (k = 0; k < 5; k++)
        {
            matrixPass[j][k]=(int)pass[iterator];
            iterator++;
        }
    }
}

int computeDeterminant(int row, int column, int matrix[row][column])
{
    int determinant = 0;
    determinant = ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));

    return determinant;
}

void encryptMatrix(int two, int five, int keyPass[two][two], int decryptedMatrix[two][five], int encryptedMatrix[two][five])
{
    multiplicar_matrices(2, 5, keyPass, decryptedMatrix, encryptedMatrix);
}

void decryptMatrix(int two, int five, int keyPass[two][two], int matrixPass[two][five], int decryptedMatrix[two][five])
{
    invertir_matriz(2, 2, keyPass);

    multiplicar_matrices(2, 5, keyPass, encryptedMatrix, decryptedMatrix);
}

void createKeyPass(int two, int keyPass[two][two])
{
    srand(time(NULL));
    do
    {
        int aux = rand() % 100;

        keyPass[0][0] = aux;
        keyPass[0][1] = aux - 1;
        keyPass[1][0] = aux + 1;
        keyPass[1][1] = aux;
    } while (computeDeterminant(2, 2, keyPass) == 0);
}

void invertMatrix(int two, int keyPass[two][two])
{
    int determinant = computeDeterminant(two, two, keyPass);
    int p00 = keyPass[0][0];
    int p01 = keyPass[0][1];

    keyPass[0][0] = (keyPass[1][1]) / determinant;
    keyPass[0][1] = -1 * (p01) / determinant;
    keyPass[1][0] = -1 * (keyPass[1][0]) / determinant;
    keyPass[1][1] = (p00) / determinant;
}

int checkCompatibility(int two, int five, int matrixPass[two][five], int keyPass[two][two], char toCheckPass[])
{
    int j;
    int k;
    int iterator = 0;
    int flag = 0;
    int toCheckMatrix[2][5];
    int decryptedMatrix[2][5];

    createMatrixPass(2, 5, toCheckPass, toCheckMatrix);
    /// crea la matriz de la contrasenia ingresada
    decryptMatrix(2, 5, keyPass, matrixPass, decryptedMatrix);
    /// desencripta la matriz de la contrasenia del userAux
    for (j = 0; j < two; j++)
    {
        for (k = 0; k < five; k++)
        {
            if (decryptedMatrix[j][k] == toCheckMatrix[j][u])
                iterator++;
        }
    }
    if (iterator == 10) // es decir que coincidieron todos los chars
    {
        flag = 1; /// flag 1 ==
    }
    return flag;
}

void copyMatrix(int rows, int columns, int copy[rows][columns], int original[rows][columns])
{
    int j, k;
    for (j = 0; j < rows; j++)
    {
        for (k = 0; k < columns; k++)
        {
            copy[j][k] = original[j][k];
        }
    }
}

stWord showPassword(stUser toShow)
{
    int j;
    int k;
    int iterator = 0;
    stWord pass;
    int decryptedMatrix[2][5];

    decryptMatrix(2, 5, toShow.keyPass, toShow.matrixPass, decryptedMatrix);

    for (j = 0; j < 2; j++)
    {
        for (k = 0; k < 5; k++)
        {
            pass.word[iterator] = (char)decryptedMatrix[j][k];
            iterator++;
        }
    }
    return pass;
}
