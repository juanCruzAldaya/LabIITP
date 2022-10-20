
#include "TDAARREGLO.h"
#include "usuarios.h"
#include "listaEnlazada.h"



int pasarArchivotoArregloUsuario(arregloUsuarios adl[],char patch[],int dimension, nodoListaPelicula *lista)
{
    FILE * archivo;
    int validos=0;
    stUsuario usuario;
    archivo=fopen(patch,"rb");
    if(!archivo)
    {
    while(!feof(archivo))
    {
        fread(&usuario,1,sizeof(stUsuario),archivo);
        validos=altaUsuarioaArreglo(adl,usuario.IdUsuario,validos,lista, usuario);
    }
    }
    else
    {
        printf("error en abrir el archivo!\n");
    }
    return validos;

}


int agregarUsuario(arregloUsuarios adl[],stUsuario datos,int validos)
{
    adl[validos].usr.IdUsuario=datos.IdUsuario;
    strcpy(adl[validos].usr.nombreUsuario, datos.nombreUsuario);
    adl[validos].usr.pass[2][5]=datos.pass;
    adl[validos].usr.anioNacimiento=datos.anioNacimiento;
    strcpy(adl[validos].usr.genero, datos.genero);
    strcpy(adl[validos].usr.pais, datos.pais);
    adl[validos].usr.canVistas=datos.canVistas;
    adl[validos].usr.eliminado=datos.eliminado;
    adl[validos].listaPelis=inicLista();

    validos++;
    return validos;
}


int altaUsuarioaArreglo(arregloUsuarios adl[],int idUsuario,int validos,nodoListaPelicula *lista, stUsuario datos)
{
    nodoListaPelicula *aux=lista;
    int pos=buscarxUsuario(adl,idUsuario,validos);
    if(pos==-1)
    {
        validos=agregarUsuario(adl,datos,validos);
        pos=validos-1;
    }
    adl[pos].listaPelis=agregarPpio(adl[pos].listaPelis,aux);
    return validos;
}

int buscarxUsuario(arregloUsuarios adl[], int idUsuario, int validos)
{
    int rta=-1;
    int i=0;
    while ((i<validos)&&(rta==-1))
    {
        if(adl[i].usr.IdUsuario == idUsuario)
            rta=i;
        i++;
    }
    return rta;
}


void mostrarUsuarios (arregloUsuarios adl[], int validos)
{
    printf("\nMostrando el ADL de usuarios \n");
    int i=0;
    while(i<validos)
    {
        printf("\nUsuario ID %d: %s",adl[i].usr.IdUsuario,adl[i].usr.nombreUsuario);
        printf("\nPeliculas vistas por el usuario: ");
        recorrerYmostrar(adl[i].listaPelis);
        i++;
    }
}

int AgregarPeliculaToUsuario(arregloUsuarios adl[], char usuario[], char pelicula[], int validos, stPelicula p)
{
    nodoListaPelicula * aux = crearNodo(p);
    int pos = buscarxUsuario(adl,usuario,validos);
    if(pos==-1)
    {
        ///validos=agregarUsuario(adl,,validos);
        pos=validos-1;
    }
    adl[pos].listaPelis=agregarFinal(adl[pos].listaPelis, aux);
    return validos;
}

nodoListaPelicula * limpiarArregloDeListas (nodoListaPelicula * lista)
{
    nodoListaPelicula * proximo;
    nodoListaPelicula * seg;
    seg = lista;
    while(seg != NULL)
    {
        proximo = seg->sig;
        free(seg);
        seg = proximo;
    }
    return seg;
}

void persistirPeliculasVistas (char archivo[], arregloUsuarios adl[], int validos)
{
    FILE * arch=NULL;
    arch=fopen(archivo, "wb");

    int i=0;
    nodoListaPelicula * seg = NULL;
    arregloUsuarios aux;
    if(arch!=NULL)
    {
        for(i=0;i<validos; i++)
        {
            //strcpy(aux.usr, adl[i].usr);
            seg=adl[i].listaPelis;
            while(seg!=NULL)
            {
                //
                fwrite(&aux,sizeof(arregloUsuarios),1,arch);
                seg=seg->sig;
            }
        }
        fclose(arch);
    }
}
