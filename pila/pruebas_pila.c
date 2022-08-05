#include "pila.h"
#include "testing.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_ELEMENTO 20 

static void prueba_crear_pila(void){
    printf("PRUEBA PILA RECIEN CREADA\n");
    pila_t* pila = pila_crear();
    print_test("Prueba pila crear pila vacia ->" , pila_esta_vacia(pila) == true);
    print_test("Prueba pila ver tope ->", pila_ver_tope(pila) == NULL);
    print_test("Prueba pila desapilar pila vacia -> " , pila_desapilar(pila)== NULL);
    pila_destruir(pila);

}

static void prueba_apilar(void){
    printf("PRUEBA APLILAR Y DESAPILAR\n");
    /*creamos una pila*/
    pila_t *pila = pila_crear();
    
    /*declaramos. y definamos una variable*/
    int elemento = 0;
    pila_apilar(pila,&elemento);//apilamos el variable
    print_test("Prueba apilar:  pila ver tope ->",pila_ver_tope(pila) == &elemento);
    print_test("Prueba apilar: pila vacia ->",!pila_esta_vacia(pila) == true);
    print_test("Prueba desapilar: elemento desapilado es el elemento esperado ->",pila_desapilar(pila)== &elemento);
    print_test("Prueba desapilar: pila esta_vacia ->",pila_esta_vacia(pila) == true);
    pila_destruir(pila);
}

static void prueba_volumen(void){
    printf("PRUEBA VOLUMEN\n");
    pila_t* pila = pila_crear();

    size_t i; 
    int* arrays = malloc(sizeof(int*) * MAX_ELEMENTO);

    /* pruebas para max_elemento*/
    //1) verificamos si la pila esta vacia al inicio
    print_test("Prueba volumen apilar: la pila esta vacia al inicio-> ",pila_esta_vacia(pila) == true);
    
    //prueba apilar varios elementos
    for (i = 0 ; i < MAX_ELEMENTO; i++){
        pila_apilar(pila,&arrays[i]);
        if(pila_ver_tope(pila)!= &arrays[i]){
            printf("Prueba volumen apilar:  apilando elemento {%ld} -> ",i+1);
            print_test("",pila_ver_tope(pila) == &arrays[i]);
            break;
        }
    }
    if (i == MAX_ELEMENTO){
        print_test("Prueba volumen apilar:  apilar varios elementos ->",pila_ver_tope(pila)== &arrays[i-1]);
    }
    
    //prueba desapilar hasta esta vacia
    i=1;
    while (!pila_esta_vacia(pila)){
        void* elemento = pila_desapilar(pila);
        if (elemento != &arrays[MAX_ELEMENTO -i]){
            print_test("Prueba volumen desapilar: desapilar varios elementos ->",elemento == &arrays[MAX_ELEMENTO-i]);
        }
        i++;
    }
    if (pila_esta_vacia(pila)){
        print_test("Prueba volumen desapilar: desapilar varios elememntos -> ",pila_esta_vacia(pila) == true);
    }
    pila_destruir(pila);
    free(arrays);
}

static void prueba_apilar_null(){
    printf("PRUEBA APILAR EL ELEMENTO NULL\n");
    pila_t* pila = pila_crear();

    int *variable = NULL;
    pila_apilar(pila,variable);
    print_test("Prueba apilar elemento Null: el tope de la pila es NULL -> ",pila_ver_tope(pila) == variable);
    print_test("Prueba apilar elemento Null: pila no vacia ->", pila_esta_vacia(pila) == false);
    pila_destruir(pila);

}

void crear_espacio(void){
    printf("\n");
}

void pruebas_pila_estudiante() {
    prueba_crear_pila();
    crear_espacio();
    prueba_apilar();
    crear_espacio();
    prueba_volumen();
    crear_espacio();
    prueba_apilar_null();
    crear_espacio();
}


#ifndef CORRECTOR  
int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  
}

#endif