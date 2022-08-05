#define _POSIX_C_SOURCE  200809L // para usar strdup
#include "abb.h"
#include "pila.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define VACIO 0
#define SIN_HIJO 0
#define UN_HIJO 1
#define DOS_HIJOS 2

typedef struct nodo_abb {
    void* dato;
    char* clave;
    struct nodo_abb* izq;
    struct nodo_abb* der;
}nodo_abb_t;

struct abb{
    nodo_abb_t* raiz;
    abb_comparar_clave_t cmp;
    abb_destruir_dato_t destruir_dato;
    size_t abb_cantidad;
};

nodo_abb_t* nodo_abb_crear(const char* clave, void* dato){
    nodo_abb_t* nodo = malloc(sizeof(nodo_abb_t));
    if(!nodo) return NULL;
    nodo->clave = strdup(clave);
    if(!nodo->clave){
        free(nodo);
        return NULL;
    }
    nodo->dato = dato;
    nodo->der = NULL;
    nodo->izq = NULL;
    return nodo;
}

void nodo_actualizar(nodo_abb_t* nodo_nodo_a_borrar, abb_destruir_dato_t destruir_dato,void* dato_a_insertar){
    if(destruir_dato) destruir_dato(nodo_nodo_a_borrar->dato);
    nodo_nodo_a_borrar->dato = dato_a_insertar;
}

void* destruir_nodo (nodo_abb_t* nodo){
    void* dato = nodo->dato;
    free(nodo->clave);
    free(nodo);
    return dato;
}

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t* abb = malloc(sizeof(abb_t));
    if(!abb) return NULL;
    abb->raiz = NULL;
    abb->cmp = cmp;
    abb->destruir_dato = destruir_dato;
    abb->abb_cantidad = VACIO;
    return abb;
}

size_t abb_cantidad(const abb_t* arbol){
    return arbol->abb_cantidad;
}

nodo_abb_t* _abb_guardar(abb_t* arbol,nodo_abb_t* nodo_arbol,nodo_abb_t* nodo_a_insertar){
    if(!nodo_arbol){
        arbol->abb_cantidad++;
        return nodo_a_insertar;
    }
    int cmp = arbol->cmp(nodo_arbol->clave,nodo_a_insertar->clave);
    if(cmp == VACIO) {
        void* dato = destruir_nodo(nodo_a_insertar);
        nodo_actualizar(nodo_arbol,arbol->destruir_dato,dato);
        return nodo_arbol;
    }
    if (cmp > VACIO) nodo_arbol->izq = _abb_guardar(arbol,nodo_arbol->izq,nodo_a_insertar);
    if (cmp < VACIO) nodo_arbol->der = _abb_guardar(arbol,nodo_arbol->der,nodo_a_insertar);
    return nodo_arbol;
}

bool abb_guardar(abb_t* arbol, const char* clave, void* dato){
    nodo_abb_t* nodo = nodo_abb_crear(clave,dato);
    if(!nodo) return false;
    arbol->raiz =_abb_guardar(arbol, arbol->raiz, nodo);
    return true;
}

size_t cantidad_de_hijos(nodo_abb_t* nodo){
    if(!nodo->der && !nodo->izq){
        return SIN_HIJO;
    }
    if (nodo->der && nodo->izq) {
        return DOS_HIJOS;
    }
    return UN_HIJO;
}
// como no se puede devolver dos cosas , la funcion busacar nodo recibe
// un puntero que se llama padre, para saber el padre del nodo que 
// estamos buscando.
nodo_abb_t* buscar_nodo(nodo_abb_t** padre,nodo_abb_t* nodo,const char* clave, abb_comparar_clave_t cmp){
    if (!nodo) return NULL;
    int comp = cmp(nodo->clave,clave);
    if (comp == VACIO) return nodo;
    *padre = nodo;
    if(comp > VACIO) return buscar_nodo(padre,nodo->izq,clave,cmp);
    return buscar_nodo(padre,nodo->der,clave,cmp);
}

void* abb_obtener(const abb_t* arbol,const char* clave){
    nodo_abb_t* padre = NULL;
    nodo_abb_t* nodo = buscar_nodo(&padre,arbol->raiz,clave,arbol->cmp);
    if(!nodo) return NULL;
    return nodo->dato;
}

bool abb_pertenece(const abb_t* arbol, const char* clave){
    nodo_abb_t* padre = NULL;
    nodo_abb_t* nodo = buscar_nodo(&padre,arbol->raiz,clave, arbol->cmp) ;
    return nodo != NULL;
}

void* actualizar_nodo_anterior_del_borrado(abb_t* arbol,nodo_abb_t* padre,nodo_abb_t* nodo_a_borrar,nodo_abb_t* nodo_insertar){
    if (!padre) {
        arbol->raiz = nodo_insertar;
    } else if (padre->der && arbol->cmp(padre->der->clave, nodo_a_borrar->clave) == VACIO) {
        padre->der = nodo_insertar;
    } else {
        padre->izq = nodo_insertar;
    }
    arbol->abb_cantidad--;
    return destruir_nodo(nodo_a_borrar);

}
void* _abb_borrar_un_hijo(abb_t* arbol,nodo_abb_t* padre, nodo_abb_t* nodo_a_borrar){
    nodo_abb_t* hijo = nodo_a_borrar->izq ? nodo_a_borrar->izq : nodo_a_borrar->der;
    return actualizar_nodo_anterior_del_borrado(arbol,padre,nodo_a_borrar,hijo);  
}

void * _abb_borrar_sin_hijo(abb_t* arbol,nodo_abb_t* padre, nodo_abb_t* nodo_a_borrar){
    return actualizar_nodo_anterior_del_borrado(arbol,padre,nodo_a_borrar,NULL);

}

nodo_abb_t* buscar_reemplazante(nodo_abb_t* nodo){
    nodo_abb_t* aux = nodo;
    while (aux->izq){
    
        aux = aux->izq;
    }
    return aux;
}

void* _abb_borrar_dos_hijos(abb_t* arbol ,nodo_abb_t* nodo_a_borrar){
    nodo_abb_t* nodo_reemp = buscar_reemplazante(nodo_a_borrar->der);
    void* dato_borrado = nodo_a_borrar->dato;
    char* clave = strdup(nodo_reemp->clave);
    void* dato_aux = abb_borrar(arbol,clave);
    free(nodo_a_borrar->clave);
    nodo_a_borrar->clave = clave;
    nodo_a_borrar->dato = dato_aux;
    return dato_borrado;
}

void* _abb_borrar(abb_t* arbol , nodo_abb_t* raiz, const char* clave){
    nodo_abb_t* padre = NULL;
    nodo_abb_t* nodo_a_borrar = buscar_nodo(&padre,raiz,clave,arbol->cmp);
    size_t  cant_hijo = cantidad_de_hijos(nodo_a_borrar);
    if(cant_hijo == SIN_HIJO) return _abb_borrar_sin_hijo(arbol,padre,nodo_a_borrar);
    if(cant_hijo == UN_HIJO ) return _abb_borrar_un_hijo(arbol,padre,nodo_a_borrar);
    return _abb_borrar_dos_hijos(arbol,nodo_a_borrar);
}

void* abb_borrar(abb_t* arbol, const char* clave){
    if(!abb_pertenece(arbol,clave)) return NULL;
    return _abb_borrar(arbol,arbol->raiz,clave);
}

void _destruir_nodo(abb_destruir_dato_t destruir_dato, nodo_abb_t* raiz_arbol){
    if(!raiz_arbol){
        return;
    }
    _destruir_nodo(destruir_dato,raiz_arbol->izq);
    _destruir_nodo(destruir_dato,raiz_arbol->der);
    void* dato = destruir_nodo(raiz_arbol);
    if (destruir_dato) destruir_dato (dato);
}

void abb_destruir(abb_t* arborl){
    _destruir_nodo(arborl->destruir_dato,arborl->raiz);
    free(arborl);
}


//////////////////////////// ITERADOR INTERNO //////////////////////////



void _abb_in_order(nodo_abb_t* nodo, bool visitar(const char*,void*,void*),void* extra,bool* seguir){
    if(!nodo) return;
    _abb_in_order(nodo->izq,visitar,extra,seguir);

    if(*seguir){
        *seguir = visitar(nodo->clave,nodo->dato,extra);
    }
    if(*seguir) _abb_in_order(nodo->der,visitar,extra,seguir);
}

void abb_in_order(abb_t* arbol,bool visitar(const char*, void*, void*),void* extra){
    bool seguir = true;
    _abb_in_order(arbol->raiz,visitar,extra,&seguir);
}


//////////////////////////// ITERADOR EXTERO ///////////////////////////

void apilar_elemento(pila_t* pila , nodo_abb_t* nodo){
    if (!nodo) return;
    pila_apilar(pila,nodo);
    apilar_elemento(pila,nodo->izq);
}

struct abb_iter {
    pila_t* pila;
};

abb_iter_t* abb_iter_in_crear(const abb_t* arbol){
    abb_iter_t* iter_abb = malloc(sizeof(abb_iter_t));
    if(!iter_abb) return NULL;
    pila_t* pila = pila_crear();
    if(!pila) {
        free(iter_abb);
        return NULL;
    }
    iter_abb->pila = pila;
    apilar_elemento(iter_abb->pila,arbol->raiz);
    return iter_abb;
}

bool abb_iter_in_al_final(const abb_iter_t* iter){
    return pila_esta_vacia(iter->pila);
}

const char* abb_iter_in_ver_actual(const abb_iter_t* iter){
    if(abb_iter_in_al_final(iter))  return NULL;
    return((nodo_abb_t*) pila_ver_tope(iter->pila))->clave;
}

bool abb_iter_in_avanzar(abb_iter_t* iter){
    if(abb_iter_in_al_final(iter)) return false;
    nodo_abb_t* actual = pila_desapilar(iter->pila);
    apilar_elemento(iter->pila,actual->der);
    return true;
}

void abb_iter_in_destruir(abb_iter_t* iter){
    pila_destruir(iter->pila);
    free(iter);
}