#include "pila.h"

#include <stdlib.h>
#include <stdbool.h>

#define TAM_INICIO 20
#define VACIO 0
#define FAC_CARGA 2

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...
pila_t* pila_crear(void){
    pila_t* pila = malloc (sizeof(pila_t));
    if (!pila) return NULL;
    pila->datos = malloc(TAM_INICIO * sizeof(void*));
    if (!pila->datos){
        free (pila);
        return NULL;
    }
    pila->capacidad = TAM_INICIO;
    pila->cantidad = VACIO;
    return pila;
}

void pila_destruir(pila_t* pila){
    free(pila->datos);
    free (pila);
}

bool pila_esta_vacia(const pila_t* pila){
    return pila->cantidad == VACIO;
}

void* pila_ver_tope(const pila_t* pila){
    if(pila_esta_vacia(pila)) return NULL;
    return pila->datos[pila->cantidad - 1];
}


bool pila_redimencionar(pila_t* pila, size_t tam_nuevo){
    void** datos = realloc(pila->datos, tam_nuevo * sizeof(void*));
    if (!datos) return false;
    pila->datos = datos;
    pila->capacidad = tam_nuevo;
    return true;
}


bool pila_apilar(pila_t* pila, void* valor){
    if ((pila->cantidad == pila->capacidad) && (!pila_redimencionar(pila,pila->capacidad * FAC_CARGA))){
        return false;
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    return true;
}

void* pila_desapilar(pila_t* pila){
    if(pila_esta_vacia(pila)) return NULL;
    if((pila->cantidad == pila->capacidad / FAC_CARGA) && (pila->capacidad > TAM_INICIO)){
        pila_redimencionar(pila,pila->capacidad / FAC_CARGA);
    }
    pila->cantidad--;
    return pila->datos[pila->cantidad];
}

