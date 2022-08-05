#include "lista.h"
#include "testing.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MAX_ELEMENTO 10
#define MITAD 2
#define VACIO 0

void destruir_datos(void* dato){
    free(dato);
}

void prueba_crear_lista(void){
    printf("----------PRUEBA LISTA VACIA ----------\n");
    lista_t* lista = lista_crear();
    print_test("PRUEBA LISTA VACIA ->",lista_esta_vacia(lista));
    print_test("PRUEBA LISTA VACIA borrar primero ->",!lista_borrar_primero(lista));
    print_test("PRUEBA LISTA VACIA ver primero ->",!lista_ver_primero(lista));
    print_test("PRUEBA LISTA VACIA ver ultimo ->",!lista_ver_ultimo(lista));
    lista_destruir(lista,NULL);
}

void prueba_insertar_elemento_lista_destruccion_no_NULL(void){
    printf("\n-----------PRUEBA LISTA INSERTAR ----------\n");
    lista_t* lista = lista_crear();
    print_test("PRUEBA LISTA INSERTAR vacia al inico ->",lista_esta_vacia(lista));
    int* elemento = malloc(sizeof(int*));
    print_test("PRUEBA LISTA INSERTAR un elemento ->",lista_insertar_primero(lista,elemento));
    print_test("PRUEBA LISTA INSERTAR ver primero ->",lista_ver_primero(lista) ==elemento);
    print_test("PRUEBA LISTA INSERTAR ver ultimo ->",lista_ver_ultimo(lista) == elemento);
    int* elemento2 = malloc(sizeof(int*));
    print_test("PRUEBA LISTA INSERTAR otro elemento ->",lista_insertar_ultimo(lista,elemento2));
    print_test("PRUEBA LISTA INSERTAR ver primero ->", lista_ver_primero(lista) == elemento);
    print_test("PRUEBA LISTA INSERTAR ver ultimo ->",lista_ver_ultimo(lista) == elemento2);
    lista_destruir(lista,destruir_datos);
}

void prueba_volumen(void){
    printf("\n----------PRUEBA LISTA VOLUMEN -----------\n");
    lista_t* lista = lista_crear();
    print_test("PRUEBA LISTA VOLUMEN vacia al inico ->",lista_esta_vacia(lista));

    int* arr = malloc(sizeof(void*) * MAX_ELEMENTO);
    size_t i;
    if(!arr){
        print_test("PRUEBA LISTA VOLUMEN Erro!!!",false);
    }else{
        for(i = 0; i< MAX_ELEMENTO; i++){
            if (i<MAX_ELEMENTO/MITAD){
                lista_insertar_primero(lista,&arr[i]);
                if (lista_ver_primero(lista) != &arr[i]) {
                    printf("%ld",i);
                    print_test("PRUEBA LISTA VOLUMEN insertar varios elementos al principio  -> ->",lista_ver_primero(lista) == &arr[i]);
                    break;
                }
            }
            if (i == (MAX_ELEMENTO /2)) print_test("PRUEBA LISTA VOLUMEN insertar varios elementos al principio ->",lista_ver_primero(lista) == &arr[i-1]);

            if(i>= MAX_ELEMENTO/MITAD) {
                lista_insertar_ultimo(lista,&arr[i]);
                if (lista_ver_ultimo(lista) != &arr[i]) {
                    printf("%ld",i);
                    print_test("PRUEBA LISTA VOLUMEN insertar varios elementos al final ->",lista_ver_ultimo(lista) == &arr[i]);
                    break;
                }

            }
        }
        if (i == MAX_ELEMENTO) print_test("PRUEBA LISTA VOLUMEN insertar varios elementos al final ->",lista_ver_ultimo(lista) == &arr[MAX_ELEMENTO-1]);

        i = MAX_ELEMENTO/MITAD;
        while (i>VACIO){
            void* dato_eliminado = lista_borrar_primero(lista);
            if(dato_eliminado != &arr[i-1]) {
                print_test("PRUEBA LISTA VOLUMEN borrar varios elementos ->",dato_eliminado == &arr[1-1]);
                break;
            }
            i--;
        }
        i=MAX_ELEMENTO/MITAD;
        while (i<MAX_ELEMENTO){
            void* dato_eliminado = lista_borrar_primero(lista);
            if(dato_eliminado != &arr[i]) {
                print_test("PRUEBA LISTA VOLUMEN borrar varios elementos ->",dato_eliminado == &arr[i]);
                break;
            }
            i++;
        }
        if (lista_esta_vacia(lista)) print_test("PRUEBA LISTA VOLUMEN borrar varios elementos ->",lista_esta_vacia(lista));
        
    }
    destruir_datos(arr);
    lista_destruir(lista,NULL);
}

void prueba_insertar_NULL(void){
    printf("\n------------PRUEBA LISTA INSERTAR EL ELEMENTO NULL ------------\n");
    lista_t* lista = lista_crear();
    print_test("PRUEBA LISTA INSERTAR EL ELEMENTO NULL vacia al inico ->",lista_esta_vacia(lista));
    void* elemento = NULL;
    print_test("PRUEBA LISTA INSERTAR EL ELEMENTO NULL insertar al inicio ->",lista_insertar_primero(lista,elemento));
     print_test("PRUEBA LISTA INSERTAR EL ELEMENTO NULL lista no vacia ->",!lista_esta_vacia(lista));
    print_test("PRUEBA LISTA INSERTAR EL ELEMENTO NULL ver primero->",lista_ver_primero(lista) == elemento);
    print_test("PRUEBA LISTA INSERTAR EL ELEMENTO NULL ver ultimo ->",lista_ver_ultimo(lista) == elemento);
    lista_destruir(lista,NULL);
}

void pruebas_lista_destruccion_vacia(void (*destruir_dato)(void* dato)){
    printf("\n------------PRUEBA DESTUCCION LISTA VACIA ------------\n");
    if (!destruir_dato) printf("CON NULL \n");
    lista_t* lista = lista_crear();
    print_test("PRUEBA DESTUCCION LISTA VACIA  lista creada ->",lista != NULL);
    print_test("PRUEBA DESTUCCION LISTA VACIA  ver primero ->",!lista_ver_primero(lista));
    print_test("PRUEBA DESTUCCION LISTA VACIA  lista vacia ->",lista_esta_vacia(lista));
    if (destruir_dato) lista_destruir(lista,destruir_datos);
    if (!destruir_dato) lista_destruir(lista,NULL);

    print_test("PRUEBA DESTUCCION LISTA VACIA lista destruida ->",true);
}

void pruebas_lista_no_vacia_no_NULL(void){
    printf("\n------------PRUEBA DE DESTRUCCION LISTA NO VACIA ------------\n"); 
    lista_t* lista = lista_crear();
    size_t arr[MAX_ELEMENTO];
    print_test("PRUEBA DE DESTRUCCION LISTA NO VACIA vacia al inico ->",lista_esta_vacia(lista));
    bool insertar = true;
    for (size_t i = 0 ; i < MAX_ELEMENTO ; i++){
        arr[i] = i;
        insertar  &= lista_insertar_primero(lista,&arr[i]);
        if(!insertar) print_test("PRUEBA DE DESTRUCCION LISTA NO VACIA insertar elementos ->",insertar);

    }
    print_test("PRUEBA DE DESTRUCCION LISTA NO VACIA lista no vacia ->",!lista_esta_vacia(lista));
    lista_destruir(lista,NULL);
    bool no_modificado = true;
    for (size_t i = 0 ; i < MAX_ELEMENTO ; i++){
        no_modificado &= (arr[i] == i);
    }
    print_test("PRUEBA DE DESTRUCCION LISTA NO VACIA lista destruida , los elementos no fueron modificados ->",no_modificado);
}

void prueba_iterador_externo(){
    printf("\n------------PRUEBA LISTA ITERADOR EXTERNO------------\n\n");
    lista_t* lista = lista_crear();
    lista_iter_t* iter = lista_iter_crear(lista);
    char ejemplo[] = "prueba";
    char ejemplo2[] = "prueba2";
    print_test("PRUEBA LISTA ITERADOR EXTERNO insertar un elemento ->",lista_iter_insertar(iter,ejemplo));
    print_test("PRUEBA LISTA ITERADOR EXTERNO ver primero ->",lista_ver_primero(lista) == ejemplo);

    while(!lista_iter_al_final(iter)){
        lista_iter_avanzar(iter);
    }
    print_test("PRUEBA LISTA ITERADOR EXTERNO iter al final ->",lista_iter_insertar(iter,ejemplo2));
    print_test("PRUEBA LISTA ITERADOR EXTERNO lista ver ultimo ->",lista_ver_ultimo(lista) == ejemplo2);
    print_test("PRUEBA LISTA ITERADOR EXTERNO iter borrar ->",lista_iter_borrar(iter) == ejemplo2);
    print_test("PRUEBA LISTA ITERADOR EXTERNO iter ver ultimo ->",lista_ver_ultimo(lista) == ejemplo);
    lista_iter_destruir(iter);
    lista_destruir(lista,NULL);
}

bool calcular_suma(void* dato , void* contador){
    *(int*) contador +=  *(int*) dato;
    return true;
}

bool calcular_suma_mayor_que_10(void* dato , void* contador){
    *(int*) contador +=  *(int*) dato;
    if (*(int*) contador > 10) return false;
    return true;
}

void prueba_iterador_interno(){
    printf("\n-----------PRUEBA ITERADOR INTERNO-----------\n\n");
    
    int sum = 0,
        resultado = 0,
        resultado_mayor = 0,
        resultado_esperado = 19;
        
    lista_t* lista = lista_crear();
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    for (size_t i = 0;i < 10; i++){
        print_test("PRUEBA ITERADOR INTERNO insertar primero ->",lista_insertar_primero(lista,(void*)&arr[i]));
        resultado += arr[i];
    }

    lista_iterar(lista,calcular_suma,&sum);
    print_test("PRUEBA ITERADOR INTERNO sumar elemento de una lista",sum == resultado);
    print_test("PRUEBA ITERADOR INTERNO sin condicion de corte ->",sum == resultado);

    // sumar tres primeros elementos de la lista
    lista_iterar(lista,calcular_suma_mayor_que_10,&resultado_mayor);
    print_test("PRUEBA ITERADOR INTERNO con condicion de corte ->",resultado_mayor == resultado_esperado);

    lista_destruir(lista,NULL);
}

void pruebas_lista_estudiante(void){
    prueba_crear_lista();
    prueba_insertar_elemento_lista_destruccion_no_NULL();
    prueba_volumen();
    prueba_insertar_NULL();
    pruebas_lista_destruccion_vacia(NULL);
    pruebas_lista_destruccion_vacia(destruir_datos);   
    pruebas_lista_no_vacia_no_NULL();
    prueba_iterador_externo();
    prueba_iterador_interno();
}

#ifndef CORRECTOR

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
