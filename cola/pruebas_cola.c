#include "cola.h"
#include "testing.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_ELEMENTO 500
#define Mull 2 // multiplicar  un entero por 2

static void prueba_crear_cola(void){
    printf("--------- PRUEBA COLA RECIEN CREADA ----------\n");
    cola_t* cola = cola_crear();
    print_test("PRUEBA COLA CREAR COLA VACIA ->",cola_esta_vacia(cola));
    print_test("PRUEBA COLA VER PRIMERO ->",cola_ver_primero(cola) == NULL);
    print_test("PRUEBA COLA DESENCOLAR COLA VACIA ->",cola_desencolar(cola) == NULL);
    cola_destruir(cola,NULL);

    printf("\n");
}

void destruir_datos(void* dato){
    free(dato);
}

void mul_entero(void* dato){
    *(int*) dato *= Mull;
}

static void prueba_encolar_elemento(void){
    cola_t* cola = cola_crear();
    
    //PRUEBA ENCOLAR UN ELEMENTO
    printf("----------PRUEBA COLA ENCOLAR UN ELEMENTO----------\n");

    int* elemento = malloc(sizeof(int*));
    int* segundo = malloc(sizeof(int*));

    print_test("PRUEBA COLA ENCOLAR ENCOLAR UN ELEMENTO -> ",cola_encolar(cola,elemento));
    print_test("PRUEBA COLA ENCOLAR  COLA NO VACIA->",cola_esta_vacia(cola) == false);
    print_test("PRUEBA COLA ENCOLAR  VER PRIMERO ->",cola_ver_primero(cola) == elemento);
    print_test("PRUEBA COLA ENCOLAR UN SEGUNDO ELEMENTO -> ", cola_encolar(cola,segundo));
    
    cola_destruir(cola,destruir_datos);
    print_test("PRUEBA COLA ENCOLAR DESTRUIR DATOS ->",true);

    printf("\n");
}
 
static void prueba_volumen(void){
    printf("---------- PRUEBA COLA VOLUMEN ----------\n");
    cola_t* cola = cola_crear();
    int *arr = malloc(sizeof(void*)* MAX_ELEMENTO);
    size_t i;
    if (arr == NULL){
        printf("ERROR FALTA MEMORIA!!!!!!");
    }else{
        for(i = 0; i < MAX_ELEMENTO; i++){
           cola_encolar(cola,&arr[i]);
           if (cola_ver_primero(cola) != &arr[0]){
               printf("%ld",i);
               print_test("PRUEBA COLA VOLUMEN  ENCOLAR VARIOS ELEMENTOS ->" ,cola_ver_primero(cola) == &arr[0]);
               break;
           }
        }
        if (i == MAX_ELEMENTO){
            print_test("PRUEBA COLA VOLUMEN ENCOLAR VARIOS ELEMENTOS ->" ,cola_ver_primero(cola) == &arr[0]);

        }
        i =0;
        while(!cola_esta_vacia(cola)){
            void* elemento_des = cola_desencolar(cola);
            if(elemento_des != &arr[i]){
                print_test("PRUEBA COLA VOLUMEN DESENCOLAR VARIOS ELEMENTOS -> ", elemento_des == &arr[i]);
                break;
            }
            i++;
        }
        if (cola_esta_vacia(cola)){
            print_test("PRUEBA COLA VOLUMEN DESENCOLAR VARIOS ELEMENTOS -> ",cola_esta_vacia(cola) );
        }

    }

    destruir_datos(arr);
    cola_destruir(cola,NULL);

    printf("\n");
}

static void prueba_encolar_NULL(void){
    printf("---------- PRUEBA COLA ENCOLAR EL ELEMNTO NULL---------- \n");
    cola_t* cola = cola_crear();
    print_test("PRUEBA COLA ENCOLAR EL ELEMNTO NULL COLA VACIA AL INICIO ->",cola_esta_vacia(cola));
    void* elemento = NULL;
    print_test("PRUEBA COLA ENCOLAR EL ELEMNTO NULL->",cola_encolar(cola ,elemento) );
    print_test("PRUEBA COLA ENCOLAR EL ELEMNTO NULL VER PRIMERO->", cola_ver_primero(cola) == elemento);
    cola_destruir(cola,NULL);

    printf("\n");
   
}

static void prueba_sin_funcion_destruir(void){
    printf("--------PRUEBA COLA SIN FUNCION DE DESTRUIR DATO ----------\n");
    cola_t* cola = cola_crear();

    print_test("PRUEBA COLA SIN FUNCION DE DESTRUIR DATO COLA VACIA ->",cola_esta_vacia(cola));
    int p = MAX_ELEMENTO;// es un numero por la prueba
    int* magico = &p;
    print_test("PRUEBA COLA SIN FUNCION DE DESTRUIR DATO ENCOLAR UN ELEMENTO ->",cola_encolar(cola ,(void*) magico));
    print_test("PRUEBA COLA SIN FUNCION DE DESTRUIR DATO COLA NO VACIA ->",cola_esta_vacia(cola) == false);
    cola_destruir(cola,mul_entero);
    print_test("PRUEBA COLA SIN FUNCION DE DESTRUIR DATO ->",p == (MAX_ELEMENTO)*Mull);

    printf("\n");
}

void pruebas_cola_estudiante(){

    printf("\n");
    prueba_crear_cola();
    prueba_encolar_elemento();
    prueba_volumen();
    prueba_encolar_NULL();
    prueba_sin_funcion_destruir();
    printf("\n");
}

#ifndef CORRECTOR

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif