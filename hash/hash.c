#define _POSIX_C_SOURCE  200809L
#include "lista.h"
#include "hash.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#define HASH_TABLA_CAPACIDAD 10
#define VACIO 0
#define REDIMENSIONAR_SUP 4
#define REDIMENSIONAR_INF 2


struct hash{
    lista_t** hash_tabla;
    size_t hash_cantidad;
    size_t hash_tabla_capacidad;
    hash_destruir_dato_t destruir_dato;
};

struct hash_iter{
    const hash_t* hash;
    lista_iter_t* lista_iter;
    size_t indice;
};

typedef struct caja {
    char* clave;
    void* dato;
}caja_t;


caja_t* crear_caja(const char* clave, void* dato){
    caja_t* caja = malloc(sizeof(caja_t));
    if(!caja) return NULL;
    caja->clave = strdup(clave);
    if (!caja->clave){
        free (caja);
        return NULL;
    }
    caja->dato = dato;
    return caja;
}

void destruir_caja (caja_t* caja, hash_destruir_dato_t destruir_dato){
    if(destruir_dato){
        destruir_dato(caja->dato);
    } 
    free(caja->clave);
    free(caja);
}

lista_t** hash_crear_tabla(size_t tam_hash_tabla){
    lista_t** hash_tabla = malloc(sizeof(lista_t*)* tam_hash_tabla);
    if(!hash_tabla) return NULL;
    for(size_t i = 0; i < tam_hash_tabla; i++){
        lista_t* lista = lista_crear();
        if(!lista) {
            for(size_t j = 0; j<i-1; j++){
                lista_destruir(hash_tabla[j],NULL);
            }
            free(hash_tabla);
            return NULL;
        }
        hash_tabla[i] = lista;
    }
    return hash_tabla;
}

void hash_tabla_destruir(lista_t** hash_tabla, size_t tam_hash_tabla,hash_destruir_dato_t destruir_dato){
    for(size_t i =0 ; i < tam_hash_tabla; i++){
        lista_t* lista = hash_tabla[i];
        while(!lista_esta_vacia(lista)){
            caja_t* caja = lista_borrar_primero(lista);
            destruir_caja(caja,destruir_dato);
        }
        lista_destruir(hash_tabla[i],NULL);

    }
    free(hash_tabla);
}

// extraida del "Kernighan and Ritchie"
size_t func_hashing(const char* clave , size_t hash_tabla_capacidad){
    size_t clave_hash = 0;
    for(size_t i = 0; clave[i] != '\0'; i++){
        clave_hash = 31 * clave_hash + (size_t) clave[i];
    } 
    return clave_hash % hash_tabla_capacidad;
}

bool hash_redimensionar(hash_t* hash , size_t nuevo_tam){
    lista_t** nueva_tabla = hash_crear_tabla(nuevo_tam);
    if(!nueva_tabla) return  false;
    for(size_t i = 0; i < hash->hash_tabla_capacidad; i++){
        while (!lista_esta_vacia(hash->hash_tabla[i])){
            caja_t* caja = lista_borrar_primero(hash->hash_tabla[i]);
            size_t pos_clave = func_hashing(caja->clave,nuevo_tam);
            lista_insertar_ultimo(nueva_tabla[pos_clave],caja);
        }
        lista_destruir(hash->hash_tabla[i],NULL);
    }
    lista_t** vieja = hash->hash_tabla;
    free(vieja);
    hash->hash_tabla = nueva_tabla;
    hash->hash_tabla_capacidad = nuevo_tam;
    return true;
}

hash_t* hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t* hash = malloc(sizeof(hash_t));
    if(!hash) return NULL;
    hash->hash_tabla = hash_crear_tabla(HASH_TABLA_CAPACIDAD);
    if(!hash->hash_tabla){
        free(hash);
        return NULL;
    }
    hash->hash_tabla_capacidad = HASH_TABLA_CAPACIDAD;
    hash->hash_cantidad = VACIO;
    hash->destruir_dato = destruir_dato;
    return hash;
}

size_t hash_cantidad(const hash_t* hash){
    return hash->hash_cantidad;
}

caja_t* hash_buscar_caja_clave (const hash_t* hash , const char* clave){
    size_t pos_clave = func_hashing(clave,hash->hash_tabla_capacidad);
    lista_iter_t* iter_h = lista_iter_crear(hash->hash_tabla[pos_clave]);
    if(!iter_h) return NULL;
    caja_t* caja = lista_iter_ver_actual(iter_h);
    while ((!lista_iter_al_final(iter_h)) && (!(strcmp(caja->clave,clave) == 0))){
        lista_iter_avanzar(iter_h);
        caja = lista_iter_ver_actual(iter_h);
    }
    lista_iter_destruir(iter_h);
    return caja;
}

bool hash_reemplazar_valor(hash_t* hash , const char* clave, void* dato){
    caja_t* caja = hash_buscar_caja_clave(hash, clave);
    if(!caja) return false;
    if(hash->destruir_dato) hash->destruir_dato(caja->dato);
    caja->dato = dato;
    return true;
}

bool hash_guardar(hash_t* hash, const char* clave, void* dato){
    if((hash->hash_cantidad == hash->hash_tabla_capacidad) && (!hash_redimensionar(hash,hash->hash_tabla_capacidad * REDIMENSIONAR_SUP))) return false;
    
    if (hash_reemplazar_valor(hash,clave, dato)){
        return true;
    }

    caja_t* caja = crear_caja(clave, dato);
    if (!caja) return false;
    size_t pos_clave = func_hashing(clave, hash->hash_tabla_capacidad);
    lista_insertar_primero(hash->hash_tabla[pos_clave], caja);
    hash->hash_cantidad++;
    return true;
}

void* hash_borrar(hash_t* hash, const char* clave){
    size_t pos_clave = func_hashing(clave,hash->hash_tabla_capacidad);
    lista_iter_t* iter = lista_iter_crear(hash->hash_tabla[pos_clave]);
    void* dato = NULL;
    while (!lista_iter_al_final(iter)){
        caja_t* caja = lista_iter_ver_actual(iter);
        if(strcmp(caja->clave,clave) == 0){
            lista_iter_borrar(iter);
            dato = caja->dato;
            free(caja->clave);
            free(caja);
            hash->hash_cantidad--;
            break;
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    if((hash->hash_cantidad == hash->hash_tabla_capacidad / REDIMENSIONAR_SUP) && (hash->hash_tabla_capacidad > HASH_TABLA_CAPACIDAD)){
        hash_redimensionar(hash,hash->hash_tabla_capacidad / REDIMENSIONAR_INF);
    }
    return dato;
}

void* hash_obtener(const hash_t* hash, const char* clave){
    caja_t* caja = hash_buscar_caja_clave(hash, clave);
    if(!caja) return NULL;
    return caja->dato;
}

bool hash_pertenece(const hash_t* hash,const char* clave){
    caja_t* caja = hash_buscar_caja_clave(hash,clave);
    return caja != NULL;
}

void hash_destruir(hash_t* hash){
    hash_tabla_destruir(hash->hash_tabla,hash->hash_tabla_capacidad,hash->destruir_dato);
    free(hash);
}

bool avanzar_hasta_pos_valida(const hash_t* hash, size_t* pos){
    while(*pos != hash->hash_tabla_capacidad){
        if(!lista_esta_vacia(hash->hash_tabla[*pos])){
            return true;
        }
        *pos = *pos +1;
    }
    return false;
}

hash_iter_t* hash_iter_crear(const hash_t* hash){
    hash_iter_t* hash_iter = malloc(sizeof(hash_iter_t));
    if (!hash_iter){
        return NULL;
    } 
    hash_iter->hash = hash;

    size_t pos_actual = 0;
    if(avanzar_hasta_pos_valida(hash,&pos_actual)) {
        hash_iter->lista_iter = lista_iter_crear(hash->hash_tabla[pos_actual]);
        
    }else{
        hash_iter->lista_iter = NULL;
    }
    hash_iter->indice = pos_actual; 
    return hash_iter;
}

bool hash_iter_avanzar(hash_iter_t* iter){
    if (hash_iter_al_final(iter)) return false;

    lista_iter_avanzar(iter->lista_iter);
    if(!lista_iter_al_final(iter->lista_iter)) return true;
    iter->indice++;
    if(avanzar_hasta_pos_valida(iter->hash,&iter->indice)){
        lista_iter_destruir(iter->lista_iter);
        iter->lista_iter = lista_iter_crear(iter->hash->hash_tabla[iter->indice]);
        return true;
    }
    return false;
}

const char* hash_iter_ver_actual(const hash_iter_t* iter){
    if(hash_iter_al_final(iter)) return NULL;
    caja_t* caja = lista_iter_ver_actual(iter->lista_iter);
    return caja->clave;
}

bool hash_iter_al_final(const hash_iter_t* iter){
    return iter->indice == iter->hash->hash_tabla_capacidad;
}

void hash_iter_destruir(hash_iter_t* iter){
    if(iter->lista_iter != NULL) lista_iter_destruir(iter->lista_iter);
    free(iter);
}