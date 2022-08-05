#include "cola.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct nodo{
    void* dato;
    struct nodo* nodo_siguiente;
}nodo_t;

nodo_t* crear_nodo(void* dato){
    nodo_t* nodo_aux = malloc(sizeof(nodo_t));
    if (!nodo_aux) return NULL;
    nodo_aux->dato = dato;
    nodo_aux->nodo_siguiente = NULL;
    return nodo_aux;
}

void destruir_nodo(nodo_t* nodo){
    free(nodo);
}

struct cola{
    nodo_t* prim;
    nodo_t* ult;
};

cola_t* cola_crear(void){
    cola_t* cola = malloc(sizeof(cola_t));
    if (!cola) return NULL;
    cola->prim = NULL;
    cola->ult = NULL;
    return cola;
}


bool cola_esta_vacia(const cola_t* cola){
    return cola->prim == NULL;
}

bool cola_encolar(cola_t* cola, void* valor){
    nodo_t* nodo = crear_nodo(valor);
    if (!nodo) return false;
    if (cola_esta_vacia(cola)){
        cola->prim = nodo;
    }else{
        cola->ult->nodo_siguiente = nodo;
    }
    cola->ult=nodo;
    return true;
}

void* cola_ver_primero(const cola_t* cola){
    if (cola_esta_vacia(cola)) return NULL;
    return cola->prim->dato;
}

void* cola_desencolar(cola_t* cola){
    if (cola_esta_vacia(cola)) return NULL;
    nodo_t* nodo = cola->prim;
    void* dato = nodo->dato;

    if(cola->prim->nodo_siguiente == NULL){
        cola->prim = NULL;
        cola->ult = NULL;
    }else {
        cola->prim = cola->prim->nodo_siguiente;
    }
    
    destruir_nodo(nodo);
    return dato;
}


void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)){
    while (!cola_esta_vacia(cola)){
        void* dato = cola_desencolar(cola);
        if (destruir_dato != NULL) destruir_dato(dato);
    }
    free(cola);

}