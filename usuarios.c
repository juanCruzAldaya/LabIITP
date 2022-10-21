#include "userLib.h"
//-****************************************************
//-***************************************************************************************
//SECTOR ADMINISTRACION DE userAuxS
//-***************************************************************************************
//A)FUNCION QUE CARGA 1 usuario A LA ESTRUCTURA AUXILIAR Y LA GUARDA EN EL fileUser
//-----------------------------------------------------


void addUserToFile(char patchUser[])
{

    int valids = 0;
    FILE * userFile;
    stUser userAux;
    int idUser = CantidadValida(patchUser);
    int cont = 0;
    int userValidation = 0;

    char passAux[11]; ///auxiliar de contrasenia
    char passAux1[11];    ///auxiliar de verificacion de contraseña
    int decryptedPass[2][5]; ///cambia la contraseña q ingresa el userAux a una matriz de enteros
    int keyPass[2][2]; ///matriz encriptadora
    int encryptedPass[2][5]; ///matriz Encriptada




    userFile = fopen(patchUser, "ab");
    if (!userFile)
    {
        printf("Error en crear el fileUser / ruta invalida \n");
    }
    else
    {
        userAux.idUser = cont++; //AUTOINCREMENTABLE

        //CARGA DE 1 userAux POR TECLADO
        printf("Ingrese el nombre comnpleto del userAux (maximo 30 caracteres)\n");
        fflush(stdin);
        gets(userAux.fullName);
        // VALIDO SI EL NOMBRE DE userAux YA EXISTE
        userValidation = userValidation(patchUser,userAux,userAux.idUser);
        while (userValidation == 0)
        {
            printf("El nombre de userAux ya existe!\n");
            printf("Ingrese otro nombre de userAux!\n");
            fflush(stdin);
            gets(userAux.fullName);
            userValidation = userValidation(patchUser,userAux,userAux.idUser);//VALIDO NUEVAMENTE EL NOMBRE
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
            printf("Ingrese una vez mas su contrasenia\n");
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

        while (i<30)
        {
            userAux.totalSongsPlayed[i]=-1;
            i++;
        }


        fwrite(&userAux,sizeof(stUser),1,fileUser);
        printf("Se ha registrado correctamente el usuario\n");
        fclose(fileUser);
    }
}





//-----------------------------------------------------
//A.1)FUNCION ADICIONAL QUE VALIDA SI EL USER EXISTE
//-----------------------------------------------------


int userValidation(char userFile[],stUser toCheck);
{
    FILE * userFile;
    int flag = -1;
    stUser Aux[validos];
    int i=0;
    fileUser=fopen(PatchUser,"rb");
    if ((fileUser)!=NULL)
    {
        CargafileUsersEstructura(PatchUser,Aux,validos);
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


void mostraruserAux(char PatchUser[])
{
    FILE *fileUser;
    int validos=CantidadValida(PatchUser);
    stuserAux userAux[validos];
    int i=0;
    fileUser=fopen(PatchUser,"rb");
    if ((fileUser)!=NULL)
    {
        printf("Apertura del fileUser exitosa!\n");
        CargafileUsersEstructura(PatchUser,userAux,validos);
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


void BajauserAux(char PatchUser[],stuserAux userAux[],int validos,int pos)
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
        ActualizarfileUser(PatchUser,userAux,validos);
        printf("userAux Inactivo!\n");
    }
    if (respuesta=='n')
    {
        userAux[pos].eliminado=0;
        mostrarunuserAux(userAux,pos);
        ActualizarfileUser(PatchUser,userAux,validos);
        printf("No se dio de baja el userAux!\n");
    }

}


//--------------------------------------------------
//D)FUNCION QUE BUSCA UN userAux POR ID O POR NOMBRE
//--------------------------------------------------
//D.1)FUNCION ADICIONAL PASAR LOS userAuxS GUARDADOS DEL fileUser A UNA ESTRUCTURA
//----------------------------------------------------------------------------
void CargafileUsersEstructura(char PatchUser[],stuserAux userAux[],int validos)
{
    FILE *fileUser;
    int pos=0;
    fileUser=fopen(PatchUser,"rb");
    if ((fileUser)!=NULL)
    {
        while ((fread(&userAux[pos],sizeof(stuserAux),1,fileUser)>0)&&(pos<validos))
        {
            pos++;
        }
        fclose(fileUser);
    }
    if ((fileUser)==NULL)
    {
        printf("El fileUser no existe / error de lectura!!\n");
    }
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
    fileUser=fopen(PatchUser,"rb");
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
void ActualizarfileUser(char PatchUser[],stuserAux userAux[],int validos)
{
    int i=0;
    FILE *fileUser;
    fileUser=fopen(PatchUser,"wb");
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

void mostrar_matriz (int fila, int columna, int matrix[fila][columna])
{
    int i;
    int u;
    int aux;
    for (i=0; i<fila; i++)
    {
        for (u=0; u<columna; u++)
        {
            aux=matrix[i][u];
            printf("[%d] ", matrix[i][u]);

        }
        printf("\n");

    }

}

void multiplicar_matrices (int dos, int cinco,int matriz_multiplo1[dos][dos], int matriz_multiplo2 [dos][cinco], int matriz_resultado[dos][cinco])
{

    int i=0;
    int u;
    int q=1;
    for (u=0; u<cinco; u++)
    {
        matriz_resultado[i][u]=(matriz_multiplo1[i][i]*matriz_multiplo2[i][u])+(matriz_multiplo1[i][q]*matriz_multiplo2[q][u]);

        matriz_resultado[q][u]=(matriz_multiplo1[q][i]*matriz_multiplo2[i][u])+(matriz_multiplo1[q][q]*matriz_multiplo2[q][u]);
    }

}


void pasar_pswd_matriz (int dos, int cinco, char contrasenia[],  int matriz_contrasenia[dos][cinco])
{
    int j=0;
    int i;
    int u;


    for (i=0; i<2; i++)
    {
        for (u=0; u<5; u++)
        {
            matriz_contrasenia[i][u]=(int)contrasenia[j];


            j++;

        }
    }

}

int calcular_determinante (int fila, int columna, int matrix[fila][columna])
{
    int determinante=0;
    determinante =((matrix[0][0]* matrix[1][1]) - (matrix[1][0]*matrix[0][1]));

    return determinante;

}

void encriptar_matriz (int dos, int cinco,int matriz_encriptadora[dos][dos], int matriz_contrasenia[dos][cinco], int matriz_encriptada[dos][cinco])
{
    multiplicar_matrices(2, 5, matriz_encriptadora, matriz_contrasenia, matriz_encriptada);
}

void desencriptar_matriz (int dos, int cinco,int matriz_encriptadora[dos][dos], int matriz_encriptada [dos][cinco], int matriz_desencriptada[dos][cinco])
{
    invertir_matriz(2, 2, matriz_encriptadora);

    multiplicar_matrices(2, 5, matriz_encriptadora, matriz_encriptada, matriz_desencriptada);
}

void crear_matriz_encriptadora (int dos,int matriz_encriptadora[dos][dos])
{
    srand(time(NULL));

    do
    {
        int aux = rand()%100;

        matriz_encriptadora[0][0] = aux;
        matriz_encriptadora[0][1] = aux-1;
        matriz_encriptadora[1][0] = aux+1;
        matriz_encriptadora[1][1] = aux;
    }
    while (calcular_determinante(2, 2, matriz_encriptadora)==0);
}

void invertir_matriz (int dos, int dos,int matriz_encriptadora [dos][dos])
{
    int determinante=calcular_determinante(2, 2, matriz_encriptadora);
    int m00=matriz_encriptadora[0][0];
    int m01=matriz_encriptadora[0][1];

    matriz_encriptadora[0][0]=(matriz_encriptadora[1][1])/determinante;
    matriz_encriptadora[0][1]=-1*(m01)/determinante;
    matriz_encriptadora[1][0]=-1*(matriz_encriptadora[1][0])/determinante;
    matriz_encriptadora[1][1]=(m00)/determinante;

}

int calcular_compatibilidad (int dos, int cinco, int matriz_encriptada[dos][cinco], int matriz_encriptadora [dos][dos], char contrasenia_ingreasda[])
{
    int i;
    int u;
    int j=0;
    int flag=0;
    int matriz_pswd_ingresada [2][5];
    int matriz_desencriptada[2][5];
    pasar_pswd_matriz(2, 5, contrasenia_ingreasda, matriz_pswd_ingresada);
    ///crea la matriz de la contrasenia ingresada
    desencriptar_matriz(2, 5, matriz_encriptadora, matriz_encriptada, matriz_desencriptada);
    ///desencripta la matriz de la contrasenia del userAux
    for (i=0; i<dos; i++)
    {
        for (u=0; u<cinco; u++)
        {
            if (matriz_desencriptada[i][u]==matriz_pswd_ingresada[i][u])
                j++;
        }
    }
    if (j==10)
    {
        flag=1;
    }
    return flag;
}

void cpyMatr (int filas, int columnas, int destino[filas][columnas], int origen [filas][columnas])

{
    int i, u;
    for (i=0; i<filas; i++)
    {
        for (u=0; u<columnas; u++)
        {
            destino[i][u]=origen[i][u];
        }

    }
}

