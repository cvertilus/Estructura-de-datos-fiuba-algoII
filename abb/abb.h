#ifndef _ABB_H
#define _ABB_H
#include  <stdbool.h>
#include <stdlib.h>

//struct del arbol debe llamarse abb;
typedef struct abb abb_t;

//tipo de funcion de comparacion de cadenas
typedef int (*abb_comparar_clave_t) (const char *, const char *);

// tipo de funcion para destruir dato
typedef void (*abb_destruir_dato_t) (void *);


/**
 * Crea el arbol binario, recibe una funcion para 
 * comparar cadenas, y una funcion para destruir datos o 
 * null.
 * Post: devuelve un arbol binario o null si hubo un 
 *       error.
 */
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

/**
 * Guarda un elemento en el arbol , si la clave ya existe
 * la reemplaza. Devuelve false si no pudo guardarlo.
 * Pre: El arbol fue creado.
 * Post: se almaceno el elemento en el arbol devuelve 
 *       true , en caso contario false.
 */
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

/**
 * Borra un elemento del arbol y devuelve el dato 
 * asociado. Devuelve Null si el elemento no esta.
 * Pre:El arbol fue creado.
 * Post:El elemento fue borrado del arbol y se lo 
 *      devolvio. Si no esta el elemento devuelve 
 *      NULL.
 */
void *abb_borrar(abb_t *arbol, const char *clave);

/**
 * Obtiene el valor de un elemento del arbol,y lo 
 * devuelve , si no esta devuelve NULL.
 * Pre: El arbol fue creado.
 * Post: Devuelve el dato asociado al elemento si no esta
 *       devuelve NULL.]
 */    
void *abb_obtener(const abb_t *arbol, const char *clave);

/**
 * Devuelve true si pertenece el elemento al arbol, false
 * en caso contrario.
 * Pre: EL arbol fue creado.
 * Post: devuelve true si existe , false si no.
 */
bool abb_pertenece(const abb_t *arbol, const char *clave);

/**
 * Devuelve la cantidad de elemento del arbol.
 * Pre: El arbol fue creado.
 * Post: devuelve la cantiad de elemento.
 */
size_t abb_cantidad(const abb_t *arbol);

/**
 * Destruye el arbol libreando la memoria pedida
 * Pre: EL arbol fue creado.
 * Post: El arbol fue destruido.
 */
void abb_destruir(abb_t *arbol);



/**
 * Iterara un arbol , la funcion visitar determinara 
 * cuando cortar la iteracion, la funcion visitar recibe
 * una clave, un dato y un extra de  tipo void*.
 * 
 * Pre: El arbol fue creado, un extra de tipo void* , y 
 *      una funcion vistar.
 * Post: Iterara sobre la estructura.
 */
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);


//struct iter_arbol debe llamarse abb_iter;
typedef struct abb_iter abb_iter_t;

/**
 * Crea un iterardor del arbol.
 * Pre:
 * Post: Devuelve un iterardor o Null si hubo un error.
 */
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

/**
 * Avanza de una posicion el iterador 
 * Pre: El iterador fue creado.
 * Post: Devuelve true si pudo avanzar, false en case
 *       contrario.
 */
bool abb_iter_in_avanzar(abb_iter_t *iter);

/**
 * Devuele el clave actual esa no se puede modificar
 * Pre: El iterador fue creado.
 * Post: Devuelve la clave, si no hay actual devuelve 
 *       NULL.
 */
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

/**
 * Determine si el iterardor esta al final.
 * Pre: El iterador fue creado.
 * Post: devuelve faslse si no esta al final, true 
 *       si esta.
 */
bool abb_iter_in_al_final(const abb_iter_t *iter);

/**
 * Destruye el Iterador
 * Pre: El iterador fue creado.
 * Post: Destruye el iterador.
 */
void abb_iter_in_destruir(abb_iter_t* iter);

#endif