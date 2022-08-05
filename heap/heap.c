#include "heap.h"
#include <stdlib.h>
#include <stdbool.h>
#define TAM_HEAP 20
#define VACIO 0
#define FAC_REDIMENSIONAR 2
#define FAC_CAPACIDAD 4

struct heap{
    void** dato;
    size_t tam;
    size_t cantitad;
    cmp_func_t cmp;
};

heap_t* heap_crear(__compar_fn_t cmp){
    heap_t* heap = malloc(sizeof(heap_t));
    if(!heap) return NULL;
    void** dato = malloc(sizeof(void*)*TAM_HEAP);
    if(!dato) {
        free(heap);
        return NULL;
    }
    heap->dato = dato;
    heap->cmp = cmp;
    heap->tam = TAM_HEAP;
    heap->cantitad = VACIO;
    return heap;
}

void heap_destruir(heap_t* heap ,void (*destruir_elemento)(void*)){
    if(destruir_elemento){
        for (size_t i = 0; i < heap->cantitad; i++){
            destruir_elemento(heap->dato[i]);
        }
    }
    free(heap->dato);
    free(heap);
}

size_t heap_cantidad(const heap_t* heap){
    return heap->cantitad;
}

bool heap_esta_vacio(const heap_t* heap){
    return heap_cantidad(heap) == 0;
}

void* heap_ver_max(const heap_t* heap){
    if(heap_esta_vacio(heap)) return NULL;
    return heap->dato[0];
}

bool redimensionar(heap_t* heap, size_t nuevo_tam){
    void** aux = realloc(heap->dato,nuevo_tam * sizeof(void*));
    if(!aux) return false;
    heap->dato = aux;
    heap->tam = nuevo_tam;
    return true;
}

void swap(void** dato_a, void** dato_b){
    void* aux = *dato_a;
    *dato_a = *dato_b;
    *dato_b = aux;
}

size_t obtener_pos_padre (size_t pos_hijo){
    return (pos_hijo - 1) / 2;
}

size_t obtener_pos_hijo_izq(size_t pos_padre){
    return pos_padre * 2 + 1;
}

size_t obtener_pos_hijo_der(size_t pos_padre){
    return pos_padre * 2 + 2;
}

void upheap(void** arr,size_t pos_hijo,cmp_func_t cmp){
    if(pos_hijo == VACIO) return ;
    size_t pos_padre = obtener_pos_padre(pos_hijo);
    if(cmp(arr[pos_hijo],arr[pos_padre]) < VACIO) return;
    swap(&arr[pos_hijo],&arr[pos_padre]);
    upheap(arr,pos_padre,cmp);
}

bool heap_encolar(heap_t* heap,void* elem){
    if((heap->cantitad == heap->tam) && (!redimensionar(heap,heap->tam * FAC_REDIMENSIONAR))) return false;
    heap->dato[heap->cantitad] = elem;
    upheap(heap->dato,heap->cantitad,heap->cmp);
    heap->cantitad++;
    return true;
}

size_t obtener_pos_max (void** arr, size_t pos_a, size_t pos_b,cmp_func_t cmp){
    if(cmp(arr[pos_a],arr[pos_b]) > VACIO) return pos_a;
    return pos_b;
}

void downheap(void** arr, size_t tam, size_t pos_padre, cmp_func_t cmp){
    if(pos_padre >= tam) return;
    size_t pos_hijo_izq = obtener_pos_hijo_izq(pos_padre);
    size_t pos_hijo_der = obtener_pos_hijo_der(pos_padre);
    size_t pos_max = pos_padre;
    if(pos_hijo_izq < tam) {
        pos_max = obtener_pos_max(arr,pos_max,pos_hijo_izq,cmp);
    }
    if(pos_hijo_der < tam) {
        pos_max = obtener_pos_max(arr,pos_max,pos_hijo_der,cmp);
    }
    if(pos_max != pos_padre) {
        swap(&arr[pos_padre],&arr[pos_max]);
        downheap(arr,tam,pos_max,cmp);
    }
}

void* heap_desencolar(heap_t* heap){
    if(heap_esta_vacio(heap)) return NULL;
    void* dato = heap_ver_max(heap);
    swap(&heap->dato[0],&heap->dato[heap->cantitad - 1]);
    heap->cantitad --;
    
    if((heap->cantitad == (heap->tam / FAC_CAPACIDAD)) && (heap->tam > TAM_HEAP)) redimensionar(heap,heap->tam / FAC_REDIMENSIONAR);

    downheap(heap->dato,heap->cantitad,0,heap->cmp);
    return dato;
}


void heapify(void** arr, size_t tam, cmp_func_t cmp){
    for(size_t i = tam ; i > 0 ; i--){
        downheap(arr,tam,i-1,cmp);
    }
}

heap_t* heap_crear_arr(void** arr, size_t n, cmp_func_t cmp){
    heap_t* heap = malloc(sizeof(heap_t));
    if (!heap) return NULL;

    void** datos = malloc(sizeof(void*) * n);
    if(!datos) {
        free(heap);
        return NULL;
    }

    for(size_t i = 0 ; i < n; i++){
        datos[i] = arr[i];
    }

    heap->dato = datos;
    heapify(heap->dato,n,cmp);

    heap->tam = n;
    heap->cantitad = n;
    heap->cmp = cmp;
    return heap;
}

void _heap_sort(void** elementos,size_t cant,cmp_func_t cmp){
    if(cant <=1 ) return;
    swap(&elementos[0],&elementos[cant-1]);
    downheap(elementos,cant-1,0,cmp);
    _heap_sort(elementos,cant-1,cmp);
}

void heap_sort(void**elementos, size_t cant, cmp_func_t cmp) {
	heapify(elementos, cant, cmp);
	_heap_sort(elementos,cant,cmp);
}