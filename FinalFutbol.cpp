#include <iostream>
#include <string.h>
using namespace std;

struct jugador
{
    unsigned id;
    char nombre[51];
    unsigned nacimineto;
    char pais[51];
    unsigned goles;
};

struct jugoEn
{
    unsigned id;
    char pais[51];
};

struct nodoListaJugadores
{
    jugador info;
    nodoListaJugadores* sgte;
};

struct nodoListaJugoEn
{
    jugoEn info;
    nodoListaJugoEn* sgte;
};

nodoListaJugadores *obtenerUltimo (nodoListaJugadores* lista){
while (lista && lista->sgte)
{
    lista = lista->sgte;
}
return lista;
}

void insertarNodoJugadorAlFinal(nodoListaJugadores *& a, jugador j);
void insertarNodoJugadorAlFinal(nodoListaJugadores *& a, jugador j){
      nodoListaJugadores *tmp = new nodoListaJugadores();
    tmp->info.id = j.id;
    tmp->info.nacimineto=j.nacimineto;
    tmp->info.goles=j.goles;
    strcpy(tmp->info.nombre,j.nombre);
    strcpy(tmp->info.pais,j.pais);
    tmp->sgte = NULL;
    if(!a){
        a = tmp;
    }else{
        nodoListaJugadores *aux = a;
        while(aux->sgte != NULL){
            aux = aux->sgte;
        }
        aux->sgte = tmp;
    }
return;
}
void insertarNodoJugoEnAlFinal(nodoListaJugoEn *& a, jugoEn j);
void insertarNodoJugoEnAlFinal(nodoListaJugoEn *& a, jugoEn j){
      nodoListaJugoEn *tmp = new nodoListaJugoEn();
    tmp->info.id = j.id;
    strcpy(tmp->info.pais,j.pais);
    tmp->sgte = NULL;
    if(!a){
        a = tmp;
    }else{
        nodoListaJugoEn *aux = a;
        while(aux->sgte != NULL){
            aux = aux->sgte;
        }
        aux->sgte = tmp;
    }
return;
}

nodoListaJugadores *crearListaJugadores(FILE *archivoJugadores);
nodoListaJugadores *crearListaJugadores(FILE *archivoJugadores){
    nodoListaJugadores *ljugadores = NULL;
    jugador j;
    while (fread(&j,sizeof(jugador),1,archivoJugadores));
    {
        cout<<"inserto id: "<<j.id<<endl;
        insertarNodoJugadorAlFinal(ljugadores,j);
    }
    fclose(archivoJugadores);
    return ljugadores;
    
}
nodoListaJugoEn *crearListaDondeJugo(FILE *archivo);
nodoListaJugoEn *crearListaDondeJugo(FILE *archivo){
    nodoListaJugoEn *dondeJugo = NULL;
    jugoEn s;
    while (fread(&s,sizeof(s),1,archivo))
    {
       insertarNodoJugoEnAlFinal(dondeJugo,s);
    }
    fclose(archivo);
    return dondeJugo;
    
}
// PUNTO 1
void cargarDatosEnMemoria(FILE *archivoJugadores, FILE *archivoDondeJugo, nodoListaJugadores *&listaJugadores, nodoListaJugoEn *&listaJugoEn);
void cargarDatosEnMemoria(FILE *archivoJugadores, FILE *archivoDondeJugo, nodoListaJugadores *&listaJugadores, nodoListaJugoEn *&listaJugoEn){
    listaJugoEn= crearListaDondeJugo(archivoDondeJugo);
    listaJugadores= crearListaJugadores(archivoJugadores);
return;
}

// PUNTO 2
nodoListaJugoEn *buscarJugadorYSeleccion(nodoListaJugoEn *&listaJugadores, int idJugador, char pais[]);
nodoListaJugoEn *buscarJugadorYSeleccion(nodoListaJugoEn *&listaJugadores, int idJugador, char pais[]){
    nodoListaJugoEn* aux = listaJugadores;
    while(aux){
        if(aux->info.id == idJugador && strcmp(aux->info.pais,pais)){
            return aux;
        }
        aux = aux->sgte;
    }
    return NULL;
}

bool jugoEnOtraSeleccion(nodoListaJugoEn *listaJugadores, int idJugador, char pais[]);
bool jugoEnOtraSeleccion(nodoListaJugoEn *listaJugadores, int idJugador, char pais[]){
nodoListaJugoEn *aux = listaJugadores;
if(buscarJugadorYSeleccion(listaJugadores,idJugador,pais)!= NULL)
    return 0;
else 
    return 1;
}

// PUNTO 3 
int edadDelCandidato(int fechanacimiento);
int edadDelCandidato(int fechanacimiento)
{
 int agnos = 2015 - fechanacimiento / 10000;
 return agnos;
}
nodoListaJugadores *buscarJugador(nodoListaJugadores *jugadores, int id);
nodoListaJugadores *buscarJugador(nodoListaJugadores *jugadores, int id){
    nodoListaJugadores * aux =jugadores;
    while (aux)
    {
        if(aux->info.id == id){
            return aux;
        }
    aux = aux->sgte;
    }
    return NULL;
    
}
bool esDelPais(nodoListaJugadores *listaJugadores, int idJugador, char pais[]);
bool esDelPais(nodoListaJugadores *listaJugadores, int idJugador, char pais[]){
    nodoListaJugadores *aux = buscarJugador(listaJugadores,idJugador);
    if (strcmp(aux->info.pais,pais)){
        return 0;
    }
    else
        return 1;
}

bool puedeSerCitado(nodoListaJugadores *listaJugadores, nodoListaJugoEn *listaDondeJugo, int idJugador, char pais[]);
bool puedeSerCitado(nodoListaJugadores *listaJugadores, nodoListaJugoEn *listaDondeJugo, int idJugador, char pais[]){
    nodoListaJugadores *aux = listaJugadores;
    nodoListaJugoEn *aux1 = listaDondeJugo;
    nodoListaJugadores *aux2 = buscarJugador(listaJugadores,idJugador);
    if(!(jugoEnOtraSeleccion(aux1,idJugador,pais)) && (edadDelCandidato(aux->info.nacimineto)<30) && esDelPais(listaJugadores,idJugador,pais))
    return 0;
        else
    return 1;
}
void CargaDatosDePruebaJugadores()
{
 jugador j;
 FILE *f;
 f=fopen("RUTA_JUGADORES","rb+");
 j.id = 1;
 strcpy(j.nombre,"Messi Leo");
j.nacimineto=19870627;
strcpy(j.pais,"Argentina");
j.goles=386;
 fwrite(&j,sizeof(j),1,f);
 j.id = 2;
 strcpy(j.nombre,"Mascherano Javier");
j.nacimineto=19850608;
strcpy(j.pais,"Argentina");
j.goles=3;
 fwrite(&j,sizeof(j),1,f);
 j.id = 3;
 strcpy(j.nombre,"Francisco dos Santos");
j.nacimineto=19331028;
strcpy(j.pais,"Brasil");
j.goles=244;
 fwrite(&j,sizeof(j),1,f);
 j.id = 4;
 strcpy(j.nombre,"Lucas Barrios");
j.nacimineto=19901028;
strcpy(j.pais,"Argentina");
j.goles=15;
 fwrite(&j,sizeof(j),1,f);
}
void CargaDatosDePruebaJugoEn()
{
 jugoEn j;
 FILE *f;
 f=fopen("RUTA_DONDEJUGO","w");
 j.id = 3;
 strcpy(j.pais,"Brasil");
fwrite(&j,sizeof(j),1,f);
 j.id = 1;
strcpy(j.pais,"Argentina");
 fwrite(&j,sizeof(j),1,f);
 j.id = 2;
 strcpy(j.pais,"Argentina");
fwrite(&j,sizeof(j),1,f);
j.id = 4;
strcpy(j.pais,"Paraguay");
fwrite(&j,sizeof(j),1,f);
 fclose(f);
}
void CargaDatosDePrueba()
{
 CargaDatosDePruebaJugadores();
 CargaDatosDePruebaJugoEn();
}

void ImprimirListaJugadores(nodoListaJugadores*&lista){
    nodoListaJugadores* aux = lista;
    while(aux){
        cout<<aux->info.id<<endl;
        cout<<aux->info.nombre<<endl;
        cout<<aux->info.goles<<endl;
        cout<<aux->info.nacimineto<<endl;
        cout<<aux->info.pais<<endl;
        if(aux->sgte) cout<<"*************"<<endl;
        aux = aux->sgte;
    }
    cout<<endl;
    delete aux;
}
void ImprimirLista(nodoListaJugoEn*&lista){
    nodoListaJugoEn* aux = lista;
    while(aux){
        cout<<aux->info.id<<endl;
        cout<<aux->info.pais<<endl;
        if(aux->sgte) cout<<"*************"<<endl;
        aux = aux->sgte;
    }
    cout<<endl;
    delete aux;
}

int main()
{
 CargaDatosDePrueba();
FILE *fnomina;
FILE *fdondejugo;
nodoListaJugadores *ljugadores =NULL;
nodoListaJugoEn *ljugoen=NULL;
nodoListaJugadores *aux;
bool puede;
 //muestraArchivos();
if ((fnomina =fopen("RUTA_JUGADORES","r")) && (fdondejugo =fopen("RUTA_DONDEJUGO","r")))
{
cargarDatosEnMemoria(fnomina, fdondejugo, ljugadores, ljugoen);
/*Cerramos los archivos, total, como ya tenemos los datos en memoria para procesar no los vamos a usar */
fclose(fnomina);
fclose(fdondejugo);
/* Ahora vamos ir recorriendo la lista de jugadores e indicando si puede jugar o no cada uno de ellos */
aux = ljugadores;
while (aux)
 {
 puede =puedeSerCitado(ljugadores,ljugoen,aux->info.id,aux->info.pais);
 if (puede)
 cout << "El jugador " << aux->info.nombre << " puede jugar para " << aux->info.pais << endl;
 else
 cout << "El jugador " << aux->info.nombre << " NO puede jugar para " << aux->info.pais << endl;
 aux= aux->sgte;
 }
}
else
cout << "Error al intentar abrir un archivo" << endl;
return 0;
}