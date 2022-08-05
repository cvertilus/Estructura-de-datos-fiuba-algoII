#include "heap.h"
#include "testing.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#define MAX_ELEMENTO 300


int comparar_enteros(const void* elemento_a, const void* elemento_b) {

	if (*(const int*) elemento_a == *(const int*)  elemento_b) {
		return 0;
	}
	if (*(const int*)elemento_a > *(const int*)  elemento_b) {
		return 1;
	}

	return -1;
}

void mezclar_enteros(int datos[], int largo) {
    srand((unsigned int) time(NULL));

    for (int i = (int) largo - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int aux = datos[i];
        datos[i] = datos[j];
        datos[j] = aux;
    }
}

void pruebas_heap_vacio() {
	printf("-------------PRUEBAS CREAR HEAP-------------\n");

	heap_t* heap = heap_crear(comparar_enteros);

	print_test("Prueba: El heap fue creado", heap);
	print_test("Prueba: El heap se encuentra vacio", heap_esta_vacio(heap));
	print_test("Prueba: La cantidad de elementos es la correcta", heap_cantidad(heap) == 0);
	print_test("Prueba: Ver maximo devuelve NULL", heap_ver_max(heap) == NULL);
	print_test("Prueba: Desencolar devuelve NULL", heap_desencolar(heap) == NULL);

	// Destruyo el heap.
	heap_destruir(heap, NULL);
}

void pruebas_heap_vacio_con_destruccion() {
	printf("\n-------------PRUEBAS HEAP VACIO CON DESTRUCCION DE DATOS-------------\n");

	heap_t* heap = heap_crear(comparar_enteros);

	print_test("Prueba: El heap fue creado", heap);
	print_test("Prueba: El heap se encuentra vacio", heap_esta_vacio(heap));
	print_test("Prueba: La cantidad de elementos es la correcta", heap_cantidad(heap) == 0);
	print_test("Prueba: Ver maximo devuelve NULL", heap_ver_max(heap) == NULL);
	print_test("Prueba: Desencolar devuelve NULL", heap_desencolar(heap) == NULL);

	heap_destruir(heap, free);
	print_test("Prueba: El heap fue destruido", true);
}

void pruebas_heap_no_vacio_con_destruccion() {
	printf("\n-------------PRUEBAS: HEAP NO VACIO CON DESTRUCCION DE DATOS-------------\n");

	heap_t* heap = heap_crear(comparar_enteros);
	int* elemento1 = malloc(sizeof(int));
	int* elemento2 = malloc(sizeof(int));
	int* elemento3 = malloc(sizeof(int));
	*elemento1 = 545;
	*elemento2 = 494;
	*elemento3 = 999;

	
	print_test("Prueba p6: El heap fue creado", heap);
	print_test("Prueba p6: El heap se encuentra vacio", heap_esta_vacio(heap));
	print_test("Prueba p6: Encolo elemento 1", heap_encolar(heap, elemento1));
	print_test("Prueba p6: Encolo elemento 2", heap_encolar(heap, elemento2));
	print_test("Prueba p6: Encolo elemento 3", heap_encolar(heap, elemento3));
	print_test("Prueba p6: La cantidad de elementos es la correcta", heap_cantidad(heap) == 3);
	print_test("Prueba p6: El heap no se encuentra vacio", !heap_esta_vacio(heap));

	heap_destruir(heap, free);
	print_test("Prueba p6: El heap fue destruido y los datos liberados", true);
}

void pruebas_heap_no_vacio_sin_destruccion() {
	printf("\n-------------PRUEBAS: HEAP NO VACIO SIN DESTRUCCION DE DATOS-------------\n");

	heap_t* heap = heap_crear(comparar_enteros);
	int tam = 10;
	int datos[10];
	for (int i = 0; i < tam; i++) {
		datos[i] = i;
	}

	bool ok_encolar = true;
	for (int i = 0; i < tam; i++) {
		ok_encolar = heap_encolar(heap, &datos[i]);
		if (!ok_encolar) {
			break;
		}
	}

	print_test("Prueba: Todos los elementos fueron encolados", ok_encolar && heap_cantidad(heap) == (size_t)tam);

	heap_destruir(heap, NULL);
	bool datos_no_modificados = true;
	for (int i = 0; i < tam; i++) {
		datos_no_modificados = datos[i] == i;
		if (!datos_no_modificados) {
			break;
		}
	}
	print_test("Prueba: El heap fue destruido y los datos no fueron modificados", datos_no_modificados);
}

void pruebas_heap_encolar() {
	printf("\n-------------PRUEBAS ENCOLAR-------------\n");

	// Declaro las variables a utilizar.
	heap_t* heap = heap_crear(comparar_enteros);
	int elemento1 = 50, elemento2 = 25, elemento3 = 33, elemento4 = 100;

	// Pruebo encolar.
	print_test("Prueba: Encolar elemento 1", heap_encolar(heap, &elemento1));
	print_test("Prueba: El heap no se encuentra vacio", !heap_esta_vacio(heap));
	print_test("Prueba: La cantidad de elementos es la correcta", heap_cantidad(heap) == 1);
	print_test("Prueba: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento1);
	print_test("Prueba: Encolar elemento 2", heap_encolar(heap, &elemento2));
	print_test("Prueba: El heap no se encuentra vacio", !heap_esta_vacio(heap));
	print_test("Prueba: La cantidad de elementos es la correcta", heap_cantidad(heap) == 2);
	print_test("Prueba: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento1);
	print_test("Prueba: Encolar elemento 3", heap_encolar(heap, &elemento3));
	print_test("Prueba: La cantidad de elementos es la correcta", heap_cantidad(heap) == 3);
	print_test("Prueba: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento1);
	print_test("Prueba: Encolar elemento 4", heap_encolar(heap, &elemento4));
	print_test("Prueba: La cantidad de elementos es la correcta", heap_cantidad(heap) == 4);
	print_test("Prueba: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento4);
	print_test("Prueba: El heap no se encuentra vacio", !heap_esta_vacio(heap));

	heap_destruir(heap, NULL);
	print_test("Prueba: El heap fue destruido", true);
}

void pruebas_heap_desencolar() {
	printf("\n-------------PRUEBAS DESENCOLAR-------------\n");

	// Declaro las variables a utilizar.
	heap_t* heap = heap_crear(comparar_enteros);
	int elemento1 = 50, elemento2 = 25, elemento3 = 33, elemento4 = 100;

	// Encolo y desencolo.
	print_test("Prueba: El heap se encuentra vacio", heap_esta_vacio(heap));
	print_test("Prueba: Encolar elemento 1", heap_encolar(heap, &elemento1));
	print_test("Prueba: El heap no se encuentra vacio", !heap_esta_vacio(heap));
	print_test("Prueba: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento1);
	print_test("Prueba: Desencolar devuelve el elemento correcto", heap_desencolar(heap) == &elemento1);
	print_test("Prueba: El heap se encuentra vacio", heap_esta_vacio(heap));
	print_test("Prueba: La cantidad de elementos es la correcta", heap_cantidad(heap) == 0);
	print_test("Prueba: Ver maximo devuelve NULL", heap_ver_max(heap) == NULL);
	print_test("Prueba: Desencolar devuelve NULL", heap_desencolar(heap) == NULL);

	print_test("Prueba: Encolar elemento 1", heap_encolar(heap, &elemento1));
	print_test("Prueba: El heap no se encuentra vacio", !heap_esta_vacio(heap));
	print_test("Prueba: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento1);
	print_test("Prueba: Encolar elemento 2", heap_encolar(heap, &elemento2));
	print_test("Prueba: Encolar elemento 3", heap_encolar(heap, &elemento3));
	print_test("Prueba: Encolar elemento 4", heap_encolar(heap, &elemento4));
	print_test("Prueba: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento4);
	print_test("Prueba: La cantidad de elementos es la correcta", heap_cantidad(heap) == 4);
	print_test("Prueba: El heap no se encuentra vacio", !heap_esta_vacio(heap));

	print_test("Prueba: Desencolar devuelve el elemento correcto", heap_desencolar(heap) == &elemento4);
	print_test("Prueba: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento1);
	print_test("Prueba: La cantidad de elementos es la correcta", heap_cantidad(heap) == 3);
	print_test("Prueba: Desencolar devuelve el elemento correcto", heap_desencolar(heap) == &elemento1);
	print_test("Prueba: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento3);
	print_test("Prueba: La cantidad de elementos es la correcta", heap_cantidad(heap) == 2);
	print_test("Prueba: Desencolar devuelve el elemento correcto", heap_desencolar(heap) == &elemento3);
	print_test("Prueba: Ver max devuelve el elemento correcto", heap_ver_max(heap) == &elemento2);
	print_test("Prueba: La cantidad de elementos es la correcta", heap_cantidad(heap) == 1);
	print_test("Prueba: Desencolar devuelve el elemento correcto", heap_desencolar(heap) == &elemento2);
	print_test("Prueba: La cantidad de elementos es la correcta", heap_cantidad(heap) == 0);
	print_test("Prueba: El heap se encuentra vacio", heap_esta_vacio(heap));

	
	heap_destruir(heap, NULL);
}

void pruebas_heap_volumen(int tam) {
	printf("\n-------------PRUEBAS VOLUMEN-------------\n");

	heap_t* heap = heap_crear(comparar_enteros);
	int datos[MAX_ELEMENTO];

	for (int i = 0; i < tam; i++) {
		datos[i] = i;
	}
	int dato_max = datos[tam - 1];
	
	mezclar_enteros(datos, tam);

	
	bool ok_encolar = true;
	for (int i = 0; i < tam; i++) {
		ok_encolar = heap_encolar(heap, &datos[i]);
		if (!ok_encolar) {
			break;
		}
	}

	print_test("Prueba: El heap no se encuentra vacio", !heap_esta_vacio(heap));
	print_test("Prueba: Todos los elementos fueron encolados", ok_encolar && heap_cantidad(heap) == (size_t)tam);
	print_test("Prueba: Ver max devuelve el elemento correcto", *(int*) heap_ver_max(heap) == dato_max);

	// Pruebo desencolar.
	bool ok_desencolar = true;
	while (!heap_esta_vacio(heap)) {
		ok_desencolar = *(int*) heap_desencolar(heap) == dato_max;
		if (!ok_desencolar) {
			break;
		}
		dato_max--;
	}

	print_test("Prueba: Todos los elementos fueron desencolados", ok_desencolar && heap_cantidad(heap) == 0);
	print_test("Prueba: El heap se encuentra vacio", heap_esta_vacio(heap));

	
	heap_destruir(heap, NULL);
}

void pruebas_heap_crear_arr(int tam) {
	printf("\n-------------PRUEBAS: CREAR HEAP DESDE ARRAY-------------\n");


	int datos_aux[MAX_ELEMENTO];
	void* datos[MAX_ELEMENTO];

	for (int i = 0; i < tam; i++) {
		datos_aux[i] = i;
		datos[i] = &datos_aux[i];
	}
	int dato_max = datos_aux[tam - 1];

	mezclar_enteros(datos_aux, tam);

	
	heap_t* heap = heap_crear_arr(datos,(size_t) tam, comparar_enteros);

	
	print_test("Prueba: El heap fue creado ", heap);
	print_test("Prueba: El heap no se encuentra vacio", !heap_esta_vacio(heap));
	print_test("Prueba: La cantidad de elementos es la correcta", heap_cantidad(heap) == (size_t)tam);
	print_test("Prueba: Ver maximo devuelve el elemento correcto", *(int*) heap_ver_max(heap) == tam - 1);

	
	bool ok_desencolar = true;
	while (!heap_esta_vacio(heap)) {
		ok_desencolar = *(int*) heap_desencolar(heap) == dato_max;
		if (!ok_desencolar) {
			break;
		}
		dato_max--;
	}

	print_test("Prueba: Todos los elementos fueron desencolados", ok_desencolar && heap_cantidad(heap) == 0);
	print_test("Prueba: El heap se encuentra vacio", heap_esta_vacio(heap));

	heap_destruir(heap, NULL);
	
}

void pruebas_heap_sort(int tam) {
	printf("\n-------------PRUEBAS: HEAP SORT-------------\n");

	int datos_aux[MAX_ELEMENTO];
	void* datos[MAX_ELEMENTO];
	int i;

	for (i = 0; i < tam; i++) {
		datos_aux[i] = i;
		datos[i] = &datos_aux[i];
	}
	mezclar_enteros(datos_aux, tam);

	
	heap_sort(datos, (size_t)tam, comparar_enteros);

	bool ok_orden = true;
	for (int j = 0; i < tam; i++) {
		ok_orden = *(int*) datos[i] == j;
		if (!ok_orden) {
			break;
		}
	}

	print_test("Prueba: Heap sort ordenó correctamente", ok_orden);
}

void pruebas_heap_estudiante() {

 	pruebas_heap_vacio();
 	pruebas_heap_vacio_con_destruccion();
 	pruebas_heap_no_vacio_con_destruccion();
 	pruebas_heap_no_vacio_sin_destruccion();
 	pruebas_heap_encolar();
 	pruebas_heap_desencolar();
 	pruebas_heap_volumen(MAX_ELEMENTO);
 	pruebas_heap_crear_arr(MAX_ELEMENTO);
 	pruebas_heap_sort(MAX_ELEMENTO);
}


#ifndef CORRECTOR
int main() {

    printf("~~~ PRUEBAS ESTUDIANTE ~~~\n");
    pruebas_heap_estudiante();
    return failure_count() > 0;
}
#endif