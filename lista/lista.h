#ifndef LISTA_H
#define LISTA_H
#include <stdbool.h>
#include <stdlib.h>

struct lista;
typedef struct lista lista_t;

/**
 * Crea una lista
 * Post: devuelve una lista o NULL si falla
 */
lista_t *lista_crear(void);


/**
 * Pre: la lista fue creada
 * Post : devuelve true si esta vacia false en caso 
 *        contrario.
 */
bool lista_esta_vacia(const lista_t *lista);


/**
 * Pre: La lista fue creada
 * 
 * Post: devuelve false en caso de un error
 *      ,true en caso de exito ,el dato sera el primero;
 */
bool lista_insertar_primero(lista_t *lista, void *dato);


/** Insertara el dato en la lista , devuele false si 
 * hubo un ERROR!
 * 
 * Pre: la lista fue creada
 * Post: se inserto el dato en lista , y sera el ultimo.
 */
bool lista_insertar_ultimo(lista_t *lista, void *dato);


/**
 * saca el primero 
 * Si la lista esta vacia devuele Null,en caso contrario 
 * devuelve el dato.
 * 
 * Pre: la lista fue creada
 * Post:borra el primero , y devuelve el dato ,reducira 
 *      de un elemento.
 */
void *lista_borrar_primero(lista_t *lista);


/**
 * obtiene el primero  y lo devuelve, si la   lista esta vacia 
 * devuelve null 
 * 
 * Pre: la lista Fue creada
 * Post: devuele el primero si la lista no este vacia/
 */
void *lista_ver_primero(const lista_t *lista);


/**
 * obtiene el ultimo , si la lista esta vacia 
 * devuelve null 
 * 
 * Pre: la lista Fue creada
 * Post: devuele el ultimo si la lista no este vacia/
 */
void *lista_ver_ultimo(const lista_t* lista);


/**
 * obtiene el largo de la lista
 * Pre: la lista fue creada
 * Post: devuelve el largo de la lista
 */ 
size_t lista_largo(const lista_t *lista);


/**
 * Destruye la lista. Si se recibe la función destruir_dato por    
 * parámetro,
 * para cada uno de los elementos de la lista llama a destruir_dato
 *  Pre: la cola fue creada. destruir_dato es una función capaz de 
 * destruir
 * los datos de la lista, o NULL en caso de que no se la utilice.
 *  Post: se eliminaron todos los elementos de la lista.
 */
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));


/********************************************************
 ********************* LISTA ITER EXTERNO ***************
 *******************************************************/


typedef struct lista_iter lista_iter_t;

/**
 * recibe una lista , y crea un iterador  , devuelve 
 * devuele NULLl si hay un error
 * Pre:recibir una lista creada
 * Post: devuele un iterador que apunta al primer
 * elemeto de la lista en caso contrario devuelve NULL
 */
lista_iter_t *lista_iter_crear(lista_t *lista);


/**
 * Avanza  una posicion en la lista , si no puede avanzar
 * devuelve false
 * Pre: el Iterador fue creado 
 * Post: devuele true, y avanza de una posicion en la lista.
 */
bool lista_iter_avanzar(lista_iter_t *iter);


/**
 * si la lista esta al final devuele NULL,
 * obtiene el valor del actual y lo devuelve
 * Pre: el Iterador fue creado 
 * Post: devolvio el actual , si no esta al final
 */
void *lista_iter_ver_actual(const lista_iter_t *iter);


/**
 * devuelve True si la lista esta al final en caso 
 * False
 * Pre: el Iterador fue creado
 * Post: devuele false si no esta al final , o true si
 * esta
 */
bool lista_iter_al_final(const lista_iter_t *iter);


/**
 * destruye el iterador
 * Pre: el Iterador fue creado
 * Post: destuye el Iterador
 */
void lista_iter_destruir(lista_iter_t *iter);


/**
 * insertara la dato recibo en la lista , devuele fasle 
 * si hubo un error
 * Pre: el Iterador fue creado
 * Post: insertara el elemento en la lista , y el actual
 *       del iterador sera el nuevo elemento agregado y 
 *       devuelve true , si hubo un error devolvera false
 */
bool lista_iter_insertar(lista_iter_t *iter, void *dato);


/**
 * eliminara el elemento actual de la lista, y devuelve el elemento 
 * que fue borrado . en caso contrario devuelve NULL
 * Pre: el Iterador fue creado
 * Post: elimina el dato y lo devuele , si no hay elemento devuelve 
 *       NULL
 */
void *lista_iter_borrar(lista_iter_t *iter);


/******************************************************************
 ******************* LISTA ITER INTERNO ***************************
 *****************************************************************/


/**
 * recibe una lista , y una funcion visitar que recibe dos punteros de 
 * tipo void*, el primero es un dato , el segundo un extra; la funcion 
 * lista_iter recibe un extra de tipo void*
 * recorer la lista y aplicara la funcion a los elementos de la lista ;
 * deja de recorer si llega al final o la funcion visitar devuelve 
 * false
 * Pre:la lista fue creada, la funcion visita no puede ser NULL
 * Post: no devuelve nada.
 */


void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);




void pruebas_lista_estudiante(void);
#endif