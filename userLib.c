#include "userLib.h"
//-****************************************************
//-***************************************************************************************
//SECTOR ADMINISTRACION DE userAuxS
//-***************************************************************************************
//A)FUNCION QUE CARGA 1 usuario A LA ESTRUCTURA AUXILIAR Y LA GUARDA EN EL fileUser
//-----------------------------------------------------


void addUserToFile()
{

    int valids = 0;
    FILE * userFile;
    stUser userAux;
    int idUser = totalUsers();
    int iterator = 0;
    int userValidation = 0;

    char passAux[11]; ///auxiliar de contrasenia
    char passAux1[11];    ///auxiliar de verificacion de contraseña
    int decryptedPass[2][5]; ///cambia la contraseña q ingresa el userAux a una matriz de enteros
    int keyPass[2][2]; ///matriz encriptadora
    int encryptedPass[2][5]; ///matriz Encriptada




    userFile = fopen(USERSFILEPATH, "ab");
    if (!userFile)
    {
        printf("Error en crear el fileUser / ruta invalida \n");
    }
    else
    {
        userAux.idUser = cont++; //AUTOINCREMENTABLE

        //CARGA DE 1 userAux POR TECLADO
        printf("Ingrese el nombre comnpleto del USER (maximo 30 caracteres)\n");
        fflush(stdin);
        gets(userAux.fullName);
        // VALIDO SI EL NOMBRE DE userAux YA EXISTE
        userValidation = userValidation(USERSFILEPATH,userAux,userAux.idUser);
        while (userValidation == 0)
        {
            printf("El nombre ya existe\n");
            printf("Ingrese otro\n");
            fflush(stdin);
            gets(userAux.fullName);
            userValidation = userValidation(userAux,userAux.idUser);//VALIDO NUEVAMENTE EL NOMBRE
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
        copyMatrix(2, 5, stUser.matrixPass, encryptedPass);///archiva la contrasenia encriptada en el campo pass de userAux



        printf("Ingrese anio de nacimiento\n");
        scanf("%d",&userAux.birthYear);

        printf("Ingrese Genero\n");
        printf("M: Masculino\n");
        printf("F: Femenino\n");
        printf("X: Otro")
        fflush(stdin);
        gets(&userAux.genero);

        printf("Ingrese pais del usuario\n");
        fflush(stdin);
        gets(userAux.country);

        userAux.off = 0;

        userAux.songsPlayed = 0;

        while (iterator<30)
        {
            userAux.songsPlayed[iterator] = -1;
            iterator++;
        }

        fwrite(&userAux,sizeof(stUser),1,fileUser);
        printf("Se ha registrado correctamente el usuario\n");
        fclose(fileUser);
    }
}




USERSFILEPATH
//-----------------------------------------------------
//A.1)FUNCION ADICIONAL QUE VALIDA SI EL USER EXISTE
//-----------------------------------------------------


int userValidation(USERSFILEPATH,stUser toCheck);
{
    FILE * userFile;
    int flag = -1;
    node2User * aux;
    int i=0;
    fileUser=fopen(USERSFILEPATH,"rb");
    if (userFile)
    {
        CargafileUsersEstructura(USERSFILEPATH,Aux,validos);
        while ((flag!=0)&&(i<validos))
        {
            flag=strcmp(Aux[i].nombreuserAux,userAux.nombreuserAux);
            i++;
        }
        fclose(fileUser);
    }
    if (fileUser==NULL)
    {
        flag=-1;
    }
    return flag;
}


//-----------------------------------------------------
//FUNCION QUE MUESTRA 1 userAux


void mostrarunuserAux(stuserAux userAux[],int pos)
{
    int pass[11];
    puts("-------------------------------------------------------------------\n");
    printf("userAux NRO/ID %d\n",userAux[pos].IduserAux);
    printf("Nombre de userAux: %s\n",userAux[pos].nombreuserAux);
    //  pasajeMatriztoArreglo(pass,userAux[pos].pass);
    //  printf("PASS: %s\n",pass);
    printf("Anio Nacimiento: %i\n",userAux[pos].birthYear);
    printf("Genero: ");
    if (userAux[pos].genero=='f')
    {
        printf("Femenino\n");
    }
    else
    {
        printf("Masculino\n");
    }
    printf("country de origen: %s\n",userAux[pos].country);
    printf("Cantidad de Peliculas vistas: %d\n",userAux[pos].canVistas);
    if (userAux[pos].eliminado==0)
    {
        printf("Estado: ACTIVO\n");
    }
    else
    {
        printf("Estado: INACTIVO\n");
    }
    puts("-------------------------------------------------------------------\n");
}


//-----------------------------------------------------
//B)FUNCION QUE MUESTRA LISTA DE userAuxS  // FALTA LA ENCRIPTACION SOLAMENTE
//-----------------------------------------------------


void mostraruserAux(USERSFILEPATH)
{
    FILE *fileUser;
    int validos=CantidadValida(USERSFILEPATH);
    stuserAux userAux[validos];
    int i=0;
    fileUser=fopen(USERSFILEPATH,"rb");
    if ((fileUser)!=NULL)
    {
        printf("Apertura del fileUser exitosa!\n");
        CargafileUsersEstructura(USERSFILEPATH,userAux,validos);
        while (i<validos)
        {
            mostrarunuserAux(userAux,i);
            i++;
        }
        fclose(fileUser);
    }
    if (fileUser==NULL)
    {
        printf("Error no existe el fileUser\n");
    }
}


//EN DESARROLLO.... ENCRIPTACION
//-----------------------------------------------------
//C)FUNCION BAJA DE userAuxS (INACTIVIDAD) REGISTRADOS EN EL fileUser //EN DESARROLLO.....
//-----------------------------------------------------


void BajauserAux(USERSFILEPATH,stuserAux userAux[],int validos,int pos)
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


//--------------------------------------------------
//D)FUNCION QUE BUSCA UN userAux POR ID O POR NOMBRE
//--------------------------------------------------
//D.1)FUNCION ADICIONAL PASAR LOS userAuxS GUARDADOS DEL fileUser A UNA ESTRUCTURA
//----------------------------------------------------------------------------
node2User * loadUsersFromFile(node2User * userList)
{
    FILE *fileUser;
    stUser aux;
    fileUser=fopen(USERSFILEPATH,"rb");

    if (fileUser)
    {
        node2User * seg = userList;
        while ((fread(&aux,sizeof(stUser),1,fileUser)>0) && (seg))
        {
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
//-----------------------------------
//D.2)FUNCION QUE BUSCAR userAux POR ID
//-----------------------------------
int BuscaruserAuxxxID(stuserAux userAuxs[],int id,int validos)
{
    int posid=0;
    int flag=0;
    int i=0;
    while ((i<validos)&&(flag==0))
    {
        if (id==userAuxs[i].IduserAux)
        {
            flag=1;
            posid=i;
        }
        i++;
    }
    if (flag==0)//EN CASO QUE NO EXISTA EL userAux SE RETORNA -1 COMO VALOR
    {
        printf("El userAux no se encuentra en el registro!\n");
        posid=-1;
    }
    if (flag!=0)//EN CASO QUE SE ENCONTRO EL userAux RETORNA SU POSICION
    {
        printf("El userAux se encuentra en el registro!\n");
    }
    return posid;
}
//-----------------------------------------------
//D.3)BUSQUEDA DE userAux POR NOMBRE
//-----------------------------------------------
int BuscaruserAuxxNombre(stuserAux userAux[],int validos,char nombre[])
{
    int flag=0;
    int i=0;
    int comparacion=0;
    int pos=0;
    while ((i<validos)&&(flag==0))
    {
        comparacion=strcmpi(nombre,userAux[i].nombreuserAux);//COMPARO NOMBRES DE LOS REGISTRADOS CON EL BUSCADO
        if (comparacion==0)//SI SE ENCUENTRA SE TERMINA EL CICLO
        {
            flag=1;//VALOR QUE CORTA EL CICLO
            pos=i;
        }
        i++;
    }
    if (flag==0)//EN CASO QUE NO EXISTA EL userAux SE RETORNA -1 COMO VALOR
    {
        printf("El userAux no se encuentra en el registro!\n");
        pos=-1;
    }
    if (flag!=0)//EN CASO QUE SE ENCONTRO EL userAux RETORNA SU POSICION
    {
        printf("El userAux se encuentra en el registro!\n");
    }
    return pos;
}
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
//-------------------------------------------
void ActualizarfileUser(USERSFILEPATH,stuserAux userAux[],int validos)
{
    int i=0;
    FILE *fileUser;
    fileUser=fopen(USERSFILEPATH,"wb");
    if (fileUser!=NULL)
    {
        while(i<validos)
        {
            fwrite(&userAux[i],sizeof(stuserAux),1,fileUser);
            i++;
        }
        fclose(fileUser);
    }
    if (fileUser==NULL)
    {
        printf("Error en abrir el fileUser\n");
    }
}
//---------------------------------------
//FUNCION QUE MODIFICA UN userAux
//----------------------------------------
void modificacionuserAux(stuserAux userAux[],int pos,int subopciones)
{
    char passaux[11];
    int eliminado=0;
    switch (subopciones)
    {
    case 1:
        printf("Su nombre actual: %s\n",userAux[pos].nombreuserAux);
        printf("Ingrese nombre nuevo\n");
        fflush(stdin);
        gets(userAux[pos].nombreuserAux);
        printf("Nombre Cambiado!\n");
        printf("Su nombre nuevo es: %s\n",userAux[pos].nombreuserAux);
        system("pause");
        system("cls");
        break;

    case 2:
        printf("Ingrese Nueva contrasenia\n");
        break;

    case 3:
        printf("Su Anio nacimiento actual es: %d\n",userAux[pos].birthYear);
        printf("Ingrese anio de nacimiento\n");
        scanf("%d",&userAux[pos].birthYear);
        break;

    case 4:
        printf("Ingrese genero:\n");
        printf("M:Masculino\n");
        printf("F:Femenino\n");
        fflush(stdin);
        gets(&userAux[pos].genero);
        while ((userAux[pos].genero!='f')&&(userAux[pos].genero!='m'))
        {
            printf("Genero incorrecto reingrese genero\n");
            printf("M:Masculino\n");
            printf("F:Femenino\n");
            fflush(stdin);
            gets(&userAux[pos].genero);
        }

        if (userAux[pos].genero=='f')
        {
            printf("Genero modificado a Femenino\n");
        }
        if (userAux[pos].genero=='m')
        {
            printf("Genero modificado a Masculino\n");
        }
        break;

    case 5:
        printf("country viejo %s\n",userAux[pos].country);
        printf("country a modificar: %s\n",userAux[pos].country);
        printf("Ingrese country de origen\n");
        fflush(stdin);
        gets(userAux[pos].country);
        printf("country Nuevo %s\n",userAux[pos].country);
        break;

    case 6:
        printf("Cantidad de peliculas vistas a modificar :%d\n",userAux[pos].canVistas);
        printf("Ingrese cantidad de peliculas vistas\n");
        scanf("%d",&userAux[pos].canVistas);
        printf("Cantidad de peliculas vistas Modificadas :%d\n",userAux[pos].canVistas);
        break;

    case 7:
        if (userAux[pos].eliminado==1)
        {
            printf("Estado actual del userAux es: INACTiVO\n");
        }
        if (userAux[pos].eliminado==0)
        {
            printf("Estado actual del userAux es: ACTIVO\n");
        }
        printf("Dar de alta/baja userAux\n");
        scanf("%d",&eliminado);
        while ((eliminado!=0)&&(eliminado!=1))
        {
            printf("Numero incorrecto\n");
            printf("Reingrese opcion\n");
            printf("0-Alta de userAux\n");
            printf("1-Baja de userAux\n");
            scanf("%d",&eliminado);
        }
        if (eliminado==0)
        {
            userAux[pos].eliminado=eliminado;
            printf("Estado Modificado a ACTIVO\n");
        }
        if (eliminado==1)
        {
            userAux[pos].eliminado=eliminado;
            printf("Estado Modificado a INACTIVO\n");
        }
        break;

    default:
        system("cls");
        printf("Opcion incorrecta!\n");
        printf("Reingrese nuevamente la opcion!!\n");
        submenuModificacion();
        scanf("%d",&subopciones);
        break;

    }
}
///FUNCION DE PRINTEO DE LA MODIFICACION DE UN userAux
void submenuModificacion()
{
    {
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
        printf("%c          MODIFICAR:          %c\n",186,186);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,187,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
        printf("%c1%c  NOMBRE                    %c\n",186,186,179);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,188,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,187,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
        printf("%c2%c  CONTRASEÑA                %c\n",186,186,179);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,188,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,187,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
        printf("%c3%c  A%CO DE NACIOMIENTO        %c\n",186,186,165,179);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,188,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,187,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
        printf("%c4%c  GENERO                    %c\n",186,186,179);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,188,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,187,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
        printf("%c5%c  country DE ORIGEN            %c\n",186,186,179);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,188,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,187,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
        printf("%c6%c  CANTIDAD PELICULAS VISTAS %c\n",186,186,179);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,188,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,187,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
        printf("%c7%c  DAR DE BAJA / ALTA        %c\n",186,186,179);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,188,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
    }
}
///FUNCION QUE CARGA LOS ID DE PELICULAS EN UN userAux DETERMINADO
void cargaIDpelisauserAux(stuserAux userAux[],int pos,int pospeli)
{
    int i=0;
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

