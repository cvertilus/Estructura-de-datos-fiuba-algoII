#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#define VACIO 0

typedef struct nodo{
    void* dato;
    struct nodo* prox;
} nodo_t;

nodo_t* crear_nodo(void* dato){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (!nodo){
        return NULL;
    }
    nodo->dato = dato;
    nodo->prox = NULL;
    return nodo;
}

void destruir_nodo(nodo_t* nodo){
    free(nodo);
}

struct lista{
    nodo_t* prim;
    nodo_t* ultimo;
    size_t largo; 
};

lista_t* lista_crear(){
    lista_t* lista = malloc(sizeof(lista_t));
    if (!lista){
        return NULL;
    }
    lista->prim = NULL;
    lista->ultimo = NULL;
    lista->largo = VACIO;
    return lista;
}

bool lista_esta_vacia(const lista_t* lista){
    return lista->largo == VACIO || !lista->prim || !lista->ultimo;
}

bool lista_insertar_primero(lista_t* lista, void* dato){
    nodo_t* nodo = crear_nodo(dato);
    if (!nodo){
        return false;
    }
    if(lista_esta_vacia(lista)){
        lista->ultimo = nodo;
    }else{
        
        nodo->prox = lista->prim;
    }
    lista->prim = nodo;
    lista->largo++;
    return true;
}

bool lista_insertar_ultimo(lista_t* lista, void* dato){
    nodo_t* nodo = crear_nodo(dato);
    if (!nodo){
        return false;
    }
    if (lista_esta_vacia(lista)){
        lista->prim = nodo;
    }else{
        lista->ultimo->prox = nodo;
    }
    lista->ultimo = nodo;
    lista->largo++;
    return true;
}
 
void* lista_borrar_primero(lista_t* lista){
    if(lista_esta_vacia(lista)){
        return NULL;
    }

    nodo_t* nodo = lista->prim;
    void* dato = nodo->dato;
    
    if (lista->prim->prox == NULL){
        lista->prim = lista->prim->prox ;
        lista->ultimo = NULL;
    }else{
        lista->prim = lista->prim->prox;
    }
    destruir_nodo(nodo);
    lista->largo--;
    return dato;

}

void* lista_ver_primero(const lista_t* lista){
    if (lista_esta_vacia(lista)){
        return NULL;
    }
    return lista->prim->dato;
}

void* lista_ver_ultimo(const lista_t* lista){
    if (lista_esta_vacia(lista)){
        return NULL;
    }
    return lista->ultimo->dato;
}

size_t lista_largo(const lista_t* lista){
    return lista->largo;
}

void lista_destruir (lista_t* lista,void (*destruir_dato)(void*)){
    while(!lista_esta_vacia(lista)){
        void* dato = lista_borrar_primero(lista);
        if(destruir_dato) {
            destruir_dato(dato);
        }
    }
    free(lista);
}

/********************************************************
 ********************* LISTA ITER EXTERNO ***************
 *******************************************************/

struct lista_iter{
    lista_t* lista;
    nodo_t* anterior;
    nodo_t* actual;
};


lista_iter_t* lista_iter_crear(lista_t* lista){
    lista_iter_t* iter = malloc(sizeof(lista_iter_t));
    if (!iter){
        return NULL;
    }
    iter->lista = lista;
    iter->actual= lista->prim;
    iter->anterior = NULL;
    return iter;
}


bool lista_iter_avanzar(lista_iter_t* iter){
    if(lista_iter_al_final(iter)){
        return false;
    }
    iter->anterior = iter->actual;
    iter->actual = iter->actual->prox;
    return true;
}


bool lista_iter_al_final(const lista_iter_t* iter){
    return iter->actual == NULL;
}


void* lista_iter_ver_actual(const lista_iter_t* iter){
    if(lista_iter_al_final(iter)){
        return NULL;
    }
    return iter->actual->dato;
}


void lista_iter_destruir(lista_iter_t* iter){
    free(iter);
}


bool lista_iter_insertar(lista_iter_t* iter,void* dato){
    nodo_t* nodo_aux = crear_nodo(dato);
    if(!nodo_aux) return false;
    nodo_aux->prox = iter->actual;
    if (iter->actual == iter->lista->prim) iter->lista->prim = nodo_aux; 

    if(lista_iter_al_final(iter)) iter->lista->ultimo = nodo_aux;
    
    if (iter->anterior) iter->anterior->prox = nodo_aux;
    iter->actual = nodo_aux;
    iter->lista->largo++;
    return true;
}


void* lista_iter_borrar(lista_iter_t* iter){
    if(lista_iter_al_final(iter)) return NULL;
    void* dato = iter->actual->dato;
    nodo_t* nodo_aux = iter->actual;
    iter->actual = iter->actual->prox;
    if (!iter->anterior) iter->lista->prim = iter->actual;
    if(lista_iter_al_final(iter)) iter->lista->ultimo = iter->anterior;
    if(iter->anterior) iter->anterior->prox = iter->actual;
    iter->lista->largo--;
    free(nodo_aux);
    return dato;
}


/******************************************************************
 ******************* LISTA ITER INTERNO ***************************
 *****************************************************************/


void lista_iterar(lista_t* lista,bool visitar(void* dato, void* extra),void* extra){
    nodo_t* nodo = lista->prim;
    while (nodo && visitar(nodo->dato,extra))
    {
        nodo = nodo->prox;
    }
    
}
