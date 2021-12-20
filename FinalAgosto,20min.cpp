#include <iostream>
#include <string.h>
using namespace std;

// PUNTO 1
struct vehiculo
{
    int patente[7];
    char delito[51];
    int horaDelDelito[6];
};

struct nodo {
    int numeroDeZona;
    char lugar[31];
    registro *registroVehiculo;
    nodo *sgte;
};
struct registro
{
    int registrarPatenete[7];
    int horaRegistro[6];
    registro *sgte;
};


//PUNTO 2 y 3
struct vehiculoSospechoso
{
     int patente[7];
    char delito[51];
    nodo *recorrido; // Contiene la lista de lugares con sus vehiculos(para saber el recorrido que hizo el auto en que zonas y horarios)//
    //  hora registro tiene ser posterior a la hora ilicito  "horarRegistro > horaIlicito"
};
nodo *buscarNodo(nodo *&lista, int patente[7]){
    nodo* aux = lista;
    while(aux){
        if(aux->registroVehiculo->registrarPatenete == patente){
            return aux;
        }
        aux = aux->sgte;
    }
    return NULL;
}

void insertarOrdenado(vehiculoSospechoso *&lista, int numeroDeZona,char lugar[31],int horaRegistro[6],int registrarPatenete[7]){
    vehiculoSospechoso *nuevo = new vehiculoSospechoso();
    nuevo->recorrido->numeroDeZona = numeroDeZona;
    for(int i=0; i>=6;i++){
        nuevo->recorrido->registroVehiculo->horaRegistro[i] = horaRegistro[i];
    }
     for(int i=0; i>=7;i++){
        nuevo->recorrido->registroVehiculo->registrarPatenete[i] = registrarPatenete[i];
    }
    nuevo->recorrido->numeroDeZona = numeroDeZona;
    strcpy(nuevo->recorrido->lugar,lugar);
    vehiculoSospechoso *aux1 = lista;
    vehiculoSospechoso *aux2;

    while(aux1->recorrido && aux1->recorrido->registroVehiculo->horaRegistro<horaRegistro){
        aux2->recorrido= aux1->recorrido;
        aux1->recorrido = aux1->recorrido->sgte;
    }
    if(lista->recorrido==aux1->recorrido){
        lista->recorrido = nuevo->recorrido;
    }
    else{
        aux2->recorrido = nuevo->recorrido;
    }
    nuevo->recorrido->sgte = aux1->recorrido;
}
vehiculoSospechoso *recorrido(nodo *vehiculosRegistrados,vehiculo vehiculoASospechar);

vehiculoSospechoso *recorrido(nodo *vehiculosRegistrados,vehiculo vehiculoASospechar){
    nodo *aux = vehiculosRegistrados;
    nodo *aux1=  buscarNodo(aux,vehiculoASospechar.patente);
    vehiculoSospechoso *aux2 = new vehiculoSospechoso();
    if(aux1){
        for(int i=0; i>=7;i++)
        aux2->patente[i] = aux1->registroVehiculo->registrarPatenete[i];
        strcpy(aux2->delito,vehiculoASospechar.delito);
    }
    while (aux)
    {
        if(aux->registroVehiculo->registrarPatenete == aux1->registroVehiculo->registrarPatenete && aux->registroVehiculo->horaRegistro > vehiculoASospechar.horaDelDelito){
            insertarOrdenado(aux2,aux1->numeroDeZona, aux->lugar,aux1->registroVehiculo->horaRegistro,aux1->registroVehiculo->registrarPatenete);
            strcpy(aux2->recorrido->lugar,aux1->lugar);
        }
       aux = aux->sgte;
    }
    if(!aux2->recorrido)
    aux2->recorrido= NULL; 
    return aux2;
}

// PUNTO 4, LO QUE YO USARIA SERIAN COLAS, YA QUE ESTO NOS PERMITE CARGAR EN UN ORDEN EN EL CUAL LO PRIMERO QUE ENTRA ES LO ULTIMO EN SALIR.