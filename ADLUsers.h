#include "userPlayLists.h"


stCell * loadListFromFile(stCell * userList);
int agregarUsuario(stCelda arrayUser[],int cantUser, stUsuario user);
int buscarUsuario(stCelda arrayUser[],int cantUser, int idUser);  ///Si rta es -1 NO encontro el Usuario
void mostrarUsuarios(stCelda arrayUser[],int cantUser);
void agregarPeliculaToUsuario(stCelda arrayUser[], int cantUser,stUsuario IdUser, int  IDpeli);
nodoListaPelicula * borrarTodaLaLista(nodoListaPelicula * lista);
void limpiarArregloDeListas(stCelda * arrayUser, int * cantUser);






