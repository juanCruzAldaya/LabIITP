#include "userLib.h"
//-****************************************************
//-***************************************************************************************
//SECTOR ADMINISTRACION DE userAuxS
//-***************************************************************************************
//A)FUNCION QUE CARGA 1 userAux A LA ESTRUCTURA AUXILIAR Y LA GUARDA EN EL fileUser
//-----------------------------------------------------


void addUserToFile()
{
    FILE * userFile;
    stUser userAux;
    userFile = fopen(USERSFILEPATH, "ab");
    if (!userFile)
    {
        printf("Error en crear el fileUser / ruta invalida \n");
    }
    else
    {
        userAux = createOneUser();
        fwrite(&userAux,sizeof(stUser),1,fileUser);
        printf("Se ha registrado correctamente el userAux\n");
        fclose(fileUser);
    }
}

stUser createOneUser ()
{
    stUser userAux;
    int idUser = totalUsers(); ///funcion que trae cantidad de userAuxs cargados en el fileUservo y autoinrementa 1
    int iterator = 0;
    int nameValidation = 0;

    char passAux[11]; ///auxiliar de contrasenia
    char passAux1[11];    ///auxiliar de verificacion de contraseña
    int decryptedPass[2][5]; ///cambia la contraseña q ingresa el userAux a una matriz de enteros
    int keyPass[2][2]; ///matriz encriptadora
    int encryptedPass[2][5]; ///matriz Encriptada
    userAux.idUser = cont++; //AUTOINCREMENTABLE

    //CARGA DE 1 userAux POR TECLADO
    printf("Ingrese el nombre comnpleto del USER (maximo 30 caracteres)\n");
    fflush(stdin);
    gets(userAux.fullName);
    // VALIDO SI EL NOMBRE DE userAux YA EXISTE
    nameValidation = nameValidation(userAux.fullName);
    while (nameValidation == 0)
    {
        printf("El nombre ya existe\n");
        printf("Ingrese otro\n");
        fflush(stdin);
        gets(userAux.fullName);
        nameValidation = nameValidation(userAux.fullName);//VALIDO NUEVAMENTE EL NOMBRE
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
    }
    while(strcmpi(passAux,passAux1) != 0);
    while(strlen(passAux) != (10 * sizeof(char)))
    {
        system("cls");
        gotoxy(30, 20);
        printf("Recuerde la contrasenia debe tener 10 caracteres, ingrese otra por favor:\n");
        gotoxy(30, 21);
        gets(passAux);
        getch();
    }

    createMatrixPass(2, 5, passAux, decryptedPass);///pasa pswd a matriz de enteros
    createKeyPass(2, keyPass);///crea matriz testigo
    copyMatrix(2,2, stUser.keyPass, keyPass); /// copia la matriz encriptadora del userAux en su campo del userAux
    encryptMatrix(2, 5, keyPass, decryptedPass, encryptedPass); ///encripta la contraseña
    copyMatrix(2, 5, stUser.matrixPass, encryptedPass);///fileUserva la contrasenia encriptada en el campo pass de userAux



    printf("Ingrese anio de nacimiento\n");
    scanf("%d",&userAux.birthYear);

    printf("Ingrese Genero\n");
    printf("M: Masculino\n");
    printf("F: Femenino\n");
    printf("X: Otro")
    fflush(stdin);
    gets(&userAux.genero);

    printf("Ingrese pais del userAux\n");
    fflush(stdin);
    gets(userAux.country);

    userAux.off = 0;

    userAux.songsPlayed = 0;

    while (iterator<30)
    {
        userAux.songsPlayed[iterator] = -1;
        iterator++;
    }

}
return userAux;
}


//-----------------------------------------------------
//A.1)FUNCION ADICIONAL QUE VALIDA SI EL USER EXISTE
//-----------------------------------------------------


int nameValidation(char toCheck[])
{
    int flag = 0;
    flag = searchUserByName(toCheck);
    return flag;
}

//-----------------------------------------------------
//FUNCION BAJA DE userAuxS (INACTIVIDAD) REGISTRADOS EN EL fileUser /
//-----------------------------------------------------

int deleteUser(int idUser)  /// Si el userAux fue elimiinado con exito devuelve 1, en caso de error devuelve 0;
{
    FILE * userFIle = fopen(USERSFILEPATH,"r+b");
    int pos = 0, flag = 0;
    stUser userAux;
    if(userFIle)
    {
        pos = searchUserById(idUser); ///busco la pos del user en el archivo por id.
        fseek(fileUser,pos*sizeof(stUser),0);///busco en el archivo
        fread(&userAux,sizeof(stUser),1,fileUser); ///escribo en el aux de persona
        userAux.eliminado = 1;
        flag = 1;
    }
    fclose(userFIle);
    return flag;
}

<<<<<<< HEAD
=======
//-----------------------------------------------------
//C)FUNCION BAJA DE userAuxS (INACTIVIDAD) REGISTRADOS EN EL fileUser
//-----------------------------------------------------


    void deleteUser(node2User * userList, int idUser)
{
    char respuesta='y';
    system("pause");
    system("cls");
    printf("Nombre del userAux %s:\n",userAux[pos].nombreuserAux);
    printf("Esta seguro que quiere eliminar el userAux ID: %d ? Y/N \n",userAux[pos].IduserAux);
    fflush(stdin);
    gets(&respuesta);
    while ((respuesta!='y')&&(respuesta!='n'))
    {
        system("cls");
        printf("Opcion incorrecta!!\n");
        printf("Por favor reingrese la opcion!\n");
        printf("Nombre del userAux %s:\n",userAux[pos].nombreuserAux);
        printf("Esta seguro que quiere eliminar el userAux ID: %d ? Y/N \n",userAux[pos].IduserAux);
        fflush(stdin);
        gets(&respuesta);
    }
    if (respuesta=='y')
    {
        userAux[pos].eliminado=1;
        mostrarunuserAux(userAux,pos);
        ActualizarfileUser(USERSFILEPATH,userAux,validos);
        printf("userAux Inactivo!\n");
    }
    if (respuesta=='n')
    {
        userAux[pos].eliminado=0;
        mostrarunuserAux(userAux,pos);
        ActualizarfileUser(USERSFILEPATH,userAux,validos);
        printf("No se dio de baja el userAux!\n");
    }

}
>>>>>>> 844ac3901b9c0b05aae615d91c018ea561c70790


//--------------------------------------------------
//D)FUNCION QUE BUSCA UN userAux POR ID O POR NOMBRE
//--------------------------------------------------
//D.1)FUNCION ADICIONAL PASAR LOS userAuxS GUARDADOS DEL fileUser A UNA ESTRUCTURA
//----------------------------------------------------------------------------

node2User * loadUsersFromFile(node2User * userList)
{
    FILE *fileUser;
    node2User * auxNode;
    stUser aux;
    fileUser = fopen(USERSFILEPATH,"rb");

    if (fileUser)
    {
        node2User * seg = userList;
        while ((fread(&aux,sizeof(stUser),1,fileUser)>0))
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
void showUsers (node2User * userList)
{
    userList = loadUsersFromFile(userList);
    showUserList(userList);
}

//-----------------------------------
//D.2)FUNCION QUE BUSCA USER POR ID
//-----------------------------------
int searchUserById(int idUser)
{
    FILE * fileUser = fopen(USERSFILEPATH, "rb");
    int pos = 0, iterator = 0, flag = 0;
    stUser userAux;
    if(fileUser)
    {
        while(!feof(fileUser) && flag == 0)
        {
            fread(&userAux,sizeof(stUser),1,fileUser);
            if(!feof(fileUser))
            {
                if(idUser == stUser.idUser)
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
    FILE * fileUser = fopen(nombrefileUser, "rb");
    int pos = 0, iterator = 0, flag = 0;
    stUser userAux;
    if(fileUser)
    {
        while(!feof(fileUser) && flag == 0)
        {
            fread(&fileUser,sizeof(stUser),1,fileUser);

            if(!feof(fileUser))
            {
                if(strcmpi(userAux.fullName,fullName) == 0)
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
//D.4)FUNCION QUE RETORNA LA  CANTIDAD DE REGISTROS VALIDOS EN EL fileUser
//------------------------------------------------
int totalUsers (char userFile[])
{
    int cantidad=0;
    FILE *fileUser;
    stuserAux userAuxAux;
    fileUser=fopen(USERSFILEPATH,"rb");
    if ((fileUser)!=NULL)//EN CASO DE DAR OK EN LA LECTURA DEVUELVE LA CANTIDAD EXACTA DE userAuxS EN EL fileUser
    {
        while (fread(&userAuxAux,sizeof(stuserAux),1,fileUser)>0)
        {
            cantidad++;
        }
        fclose(fileUser);
    }
    if ((fileUser)==NULL)//EN CASO DE DAR ERROR DEVUELVE COMO CANTIDAD 0 YA QUE NO EXISTE EL fileUser
    {
        cantidad=0;
    }
    return cantidad;
}
//-***************************************************************************************
//FUNCION DE ACTUALIZACION DE userAuxS
//------------------------------------------
void updateFile(node2User * userList)
{
    int i=0;
    FILE * fileUser;
    fileUser = fopen(USERSFILEPATH,"wb");
    if (fileUser)
    {
        while(userList)
        {
            fwrite(&userList->value,sizeof(stUser),1,fileUser);
            userList = userList->next;
        }
        fclose(fileUser);
    }
}

//---------------------------------------
//FUNCION QUE MODIFICA UN userAux
//----------------------------------------



void updateUser(int idUser)
{
    FILE * fileUser = fopen(USERSFILEPATH,"r+b");
    stUser userAux;
    int keyPass[2][2];
    int decryptedMatrix[2][5];
    int encryptedMatrix[2][5];
    char passAux[15];
    int fieldOption = 0;
    char newName[20];
    int posInFile = searchUserById(fileUser,idUser);

    if(fileUser)
    {
        fseek(fileUser,posInFile*sizeof(stUser),0);
        fread(&userAux,sizeof(stUser),1,fileUser);

        if(idUser == userArux.idUser)
        {
            do
            {
                printf("\n1.Nombre de usuario: %s",userAux.idUser);
                printf("\n2.Pass: %s", showPassword(userAux));
                printf("\n3.Nacimiento: %d",userAux.anioNacimiento);
                printf("\n4.Genero: %c",userAux.genero);
                printf("\n5.Pais: %s",userAux.pais);


                printf("\n\nEscriba el numero del campo que desea modificar o 6 para salir :");
                scanf("%d",&fieldOption);

                switch(fieldOption)
                {
                case 1:
                    printf("Ingrese nuevo nombre: ");
                    fflush(stdin);
                    gets(newName);
                    if(nameValidation(newName) == 0)
                    {
                        strcpy(userAux.nombreuserAux,nuevouserAux);

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
                    copyMatrix(2, 5, stUser.matrixPass, encryptedPass);
                    break;
                case 3:
                    printf("\nIngrese anio de nacimiento:");
                    scanf("%d",&userAux.birthYear);
                    break;
                case 4:
                    printf("\nIngrese genero:");
                    fflush(stdin);
                    scanf("%c",&userAux.gender);
                    break;

                case 5:
                    printf("\nIngrese pais:");
                    fflush(stdin);
                    gets(userAux.country);
                    break;
                }

            }
            while(fieldOption != 6);
            fseek(fileUser,posInFile*sizeof(stUser),0);
            fwrite(&userAux,sizeof(stUser),1,fileUser);
            fclose(fileUser);
        }
        else
        {
            printf("El usuario no existe \n");
        }
    }
}
--
///FUNCION QUE CARGA LOS ID DE PELICULAS EN UN userAux DETERMINADO
void cargaIDpelisauserAux(stuserAux userAux[],int pos,int pospeli)
{
    int i = 0;
    int flag=0;
    while ((i<30)&&(flag==0))
    {
        if((userAux[pos].peliculasVistas[i])==-1)
        {
            userAux[pos].peliculasVistas[i]=pospeli;
            flag=1;
        }
        i++;
    }
}
///FUNCION DE PRUEBA QUE MUESTRA LOS ID DE LAS PELICULAS GUARDADAS EN UN userAux DETERMINADO
void mostrarIDpelisauserAux(stuserAux userAux[],int pos)
{
    int i=0;
    int flag=0;
    printf("PElICULAS VISTAS!\n");
    while ((i<30))
    {
        if((userAux[pos].peliculasVistas[i])!=-1)
        {
            printf("%d\n",userAux[pos].peliculasVistas[i]);
        }
        i++;
    }
}


///MATRICES

void showMatrix (int row, int column, int matrix[row][column])
{
    int i;
    int u;
    int aux;

    for (i=0; i<row; i++)
    {
        for (u=0; u<column; u++)
        {
            printf("[%d] ", matrix[i][u]);

        }
        printf("\n");

    }

}

void multiplyMatrix (int two, int five,int firstMultiple[two][two], int secondMultiple [two][five], int result[two][five])
{

    int i = 0;
    int u;
    int q = 1;

    for (u=0; u<cinco; u++)
    {
        result[i][u]=(firstMultiple[i][i]*secondMultiple[i][u])+(firstMultiple[i][q]*secondMultiple[q][u]);

        result[q][u]=(firstMultiple[q][i]*secondMultiple[i][u])+(firstMultiple[q][q]*secondMultiple[q][u]);
    }

}


void createMatrixPass (int two, int five, char pass[],  int matrixPass[two][five]);
{
    int iterator= 0;
    int j;
    int k;


    for (j=0; j<2; j++)
    {
        for (k=0; k<5; k++)
        {
            matrixPass[j]k]=(int)pass[iterator];
            iterator++;
        }
    }
}

int computeDeterminant (int row, int column, int matrix[row][column])
{
    int determinant = 0;
    determinant = ((matrix[0][0]* matrix[1][1]) - (matrix[1][0]*matrix[0][1]));

    return determinant;
}

void encryptMatrix (int two, int five,int keyPass[two][two], int decryptedMatrix[two][five], int encryptedMatrix[two][five])
{
    multiplicar_matrices(2, 5, keyPass, matriz_contrasenia, encryptedMatrix);
}

void decryptMatrix (int two, int five,int keyPass[two][two], int matrixPass [two][five], int decryptedMatrix[two][five])
{
    invertir_matriz(2, 2, keyPass);

    multiplicar_matrices(2, 5, keyPass, encryptedMatrix, decryptedMatrix);
}

void createKeyPass (int two,int keyPass[two][two])
{
    srand(time(NULL));
    do
    {
        int aux = rand()%100;

        keyPass[0][0] = aux;
        keyPass[0][1] = aux-1;
        keyPass[1][0] = aux+1;
        keyPass[1][1] = aux;
    }
    while (computeDeterminant(2, 2, keyPass) == 0);
}

void invertMatrix() (int two,int keyPass[two][two])
{
    int determinant = computeDeterminant(two, two, keyPass);
    int p00 = keyPass[0][0];
    int p01 = keyPass[0][1];

    keyPass[0][0] = (keyPass[1][1])/determinant;
    keyPass[0][1] = -1*(p01)/determinant;
    keyPass[1][0] = -1*(keyPass[1][0])/determinant;
    keyPass[1][1] = (p00)/determinant;
}

int int checkCompatibility (int two, int five, int matrixPass[two][five], int keyPass[two][two], char toCheckPass[])
{
    int j;
    int k;
    int iterator = 0;
    int flag = 0;
    int toCheckMatrix [2][5];
    int decryptedMatrix[2][5];

    createMatrixPass(2, 5, toCheckPass, toCheckMatrix);
    ///crea la matriz de la contrasenia ingresada
    decryptMatrix(2, 5, keyPass, matrixPass, decryptedMatrix);
    ///desencripta la matriz de la contrasenia del userAux
    for (j=0; j<two; j++)
    {
        for (k=0; k<five; k++)
        {
            if (decryptedMatrix[j][u] == toCheckMatrix[j][u])
                iterator++;
        }
    }
    if (iterator == 10) //es decir que coincidieron todos los chars
    {
        flag = 1; ///flag 1 ==
    }
    return flag;
}

void copyMatrix (int rows, int columns, int copy[rows][columns], int original [rows][columns])
{
    int j, k;
    for (j=0; j<rows; j++)
    {
        for (k=0; k<columns; k++)
        {
            copy[j][k]=original[j][k];
        }
    }
}


stWord showPassword (stUser toShow)
{
    int j;
    int k;
    int iterator = 0;
    stWord pass;
    int decryptedMatrix[2][5];

    decryptMatrix(2, 5, toShow.keyPass, toShow.matrixPass, decryptedMatrix);

    for (j=0; j<2; j++)
    {
        for (k=0; k<5; k++)
        {
            pass.word[iterator]=(char)decryptedMatrix[j][k];
            iterator++;
        }
    }
    return pass;
}

