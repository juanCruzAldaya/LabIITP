#include "songLib.h"


int idClienteNuevo(char archivo[])
{
    FILE *archivito;
    archivito = fopen(archivo, "rb");
    int i = 0;
    if (archivito != NULL)
    {
        fseek(archivito, sizeof(stCancion), SEEK_END);
        i = ftell(archivito) / sizeof(stCancion);
    }
    else
    {
        printf("ERROR de datos - El archivo no pudo ser abierto");
    }
    return i++;
}

void altaDeCancion(char archivo[])
{
    stCancion cancion;
    FILE *archivito;
    archivito = fopen(archivo, "ab");

    if (archivito != NULL)
    {
        cancion.idCancion = idClienteNuevo(archivo);

        do
        {
            printf("Ingrese titulo: ");
            fflush(stdin);
            scanf("%s", &cancion.titulo);
        } while (strlen(cancion.titulo) > 30);
        do
        {
            printf("Ingrese artista: ");
            fflush(stdin);
            scanf("%s", &cancion.artista);
        } while (strlen(cancion.artista) > 30);
        do
        {
            printf("Ingrese duracion: ");
            fflush(stdin);
            scanf("%.2f", &cancion.duracion);
        } while (cancion.duracion <= 0);

        do
        {
            printf("Ingrese album: ");
            fflush(stdin);
            scanf("%s", &cancion.album);
        } while (strlen(cancion.album) > 30);

        do
        {
            printf("Ingrese anio: ");
            fflush(stdin);
            scanf("%i", &cancion.anio);
        } while (cancion.anio != 0);

        do
        {
            printf("Ingrese genero: ");
            fflush(stdin);
            scanf("%s", &cancion.genero);
        } while (strlen(cancion.genero) > 30);

        do
        {
            printf("Ingrese comentario: ");
            fflush(stdin);
            scanf("%s", &cancion.comentario);
        } while (strlen(cancion.comentario) <= 100);

        cancion.eliminado = 1;

        fwrite(&cancion, sizeof(stCancion), 1, archivito);
        fclose(archivito);
    }
    else
    {
        printf("ERROR de datos - El archivo no pudo ser abierto");
    }
}

void bajaDeCancion(char archivo[])
{
    stCancion cancion;
    FILE *archivito;
    archivito = fopen(archivo, "r+b");
    int aux = 0;
    char ok = 's';
    char idBaja;

    printf("Ingrese el id de la cancion que quiere dar de baja\n");
    fflush(stdin);
    scanf("%d", idBaja);

    if (archivito != NULL && ok == 's')
    {
        while (aux == 0 && (fread(&cancion, sizeof(stCancion), 1, archivito) > 0))
        {

            if (cancion.idCancion == idBaja)
            {
                cancion.eliminado = 0;
                fseek(archivito, (-1) * sizeof(stCancion), SEEK_CUR);
                fwrite(&cancion, sizeof(stCancion), 1, archivito);
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
    stCancion cancion;
    FILE *archivito;
    archivito = fopen(archivo, "r+b");
    int id;
    int eleccion;

    printf("Ingrese id de la cancion:\n");
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

    if (archivito != NULL)
    {
        while (fread(&cancion, sizeof(stCancion), 1, archivito) > 0)
        {

            if (cancion.idCancion == id)
            {
                switch (eleccion)
                {
                case 1:
                    printf("\nIngrese nuevo titulo:");
                    fflush(stdin);
                    scanf("%s", &cancion.titulo);
                    break;
                case 2:
                    printf("\nIngrese nuevo artista:");
                    fflush(stdin);
                    scanf("%s", &cancion.artista);
                    break;
                case 3:
                    printf("\nIngrese nueva duracion: ");
                    fflush(stdin);
                    scanf("%s", &cancion.duracion);
                    break;
                case 4:
                    printf("\nIngrese nuevo album: ");
                    fflush(stdin);
                    scanf("%s", &cancion.album);
                    break;
                case 5:
                    printf("\nIngrese nuevo anio: ");
                    fflush(stdin);
                    scanf("%d", &cancion.anio);
                    break;
                case 6:
                    printf("\nIngrese nuevo genero: ");
                    fflush(stdin);
                    scanf("%s", &cancion.genero);
                    break;
                case 7:
                    printf("\nIngrese nuevo comentario: ");
                    fflush(stdin);
                    scanf("%s", &cancion.comentario);
                    break;
                case 8:
                    printf("\nIngrese eliminado: ");
                    fflush(stdin);
                    scanf("%d", &cancion.eliminado);
                    break;
                }

                fseek(archivito, (-1) * sizeof(stCancion), SEEK_CUR);
                fwrite(&cancion, sizeof(stCancion), 1, archivito);
                fseek(archivito, sizeof(stCancion), SEEK_END);
            }
        }
    }
    fclose(archivito);
}

int consultarSiExisteCancion(char archivo[], char tituloCancion[])
{
    FILE *archivito;
    stCancion cancion;
    archivito = fopen(archivo, "rb");
    int resultado = 1;

    if (archivito != NULL)
    {
        while (fread(&cancion, sizeof(stCancion), 1, archivito) > 0)
        {
            resultado = strcmp(cancion.titulo, tituloCancion);

            if (resultado == 0)
            {
                printf("Ya existe cancion\n");
            }
        }
    }
    return resultado;
}

void showSongList(char archivo[])
{
    FILE * songFile;
    stCancion auxSong;
    songFile = fopen(archivo, "rb");
    if (songFile)
    {
        while (fread(&auxSong, sizeof(stSong), 1, songFile) > 0)
        {
            showSong(auxSong);
        }
    }
    fclose(archivito);
}

void showSong (stSong toShow)
{
     printf("\n Registro numero %d", i++);
            puts("\n-------------------------------------");
            printf("\n IdCancion: %d", toShow.idSong);
            printf("\n Titulo: %s", toShow.title);
            printf("\n Artista: %s", toShow.artist);
            printf("\n Duracion: %.2f", toShow.duration);
            printf("\n Album: %s", toShow.album);
            printf("\n Anio: %d", toShow.year);
            printf("\n Genero: %s", toShow.gender);
            printf("\n Comentario: %s", toShow.comment);
            printf("\n Eliminado 1-Si/0-No: %d", toShow.off);
            puts("\n-------------------------------------");
}
